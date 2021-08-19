#include "UPDater_Hdr.h"

BOOL bIsRun = FALSE;
XLOG xhLog = NULL;
XENGINE_SERVERCONFIG st_ServiceConfig;

void Signale_Handler(int sig)
{
	if (bIsRun)
	{
		bIsRun = FALSE;
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("按任意键,服务器退出"));

		UPData_DlParser_Close();
		HelpComponents_XLog_Destroy(xhLog);
	}
#ifdef _WINDOWS
	WSACleanup();
#endif
	exit(0);
}

int main(int argc, char** argv)
{
#ifdef _WINDOWS
	WSADATA st_WSAData;
	WSAStartup(MAKEWORD(2, 2), &st_WSAData);
#endif
#if (XENGINE_VERSION_KERNEL < 7) && (XENGINE_VERSION_MAIN < 19)
	printf("XEngine版本过低,无法继续\n");
#endif
	bIsRun = TRUE;
	int nUPLen = 1024000;
	int nListLocal = 0;
	int nListRemote = 0;
	__int64x nRemoteVer = 0;
	__int64x nLocalVer = 0;
	string m_StrUPDes;

	TCHAR* ptszJsonMsg = NULL;
	FILEPARSER_VERSIONINFO** ppSt_ListLocal;
	FILEPARSER_VERSIONINFO** ppSt_ListRemote;
	list<FILEPARSER_VERSIONINFO> stl_ListUPDate;
	HELPCOMPONENTS_XLOG_CONFIGURE st_XLogConfig;

	ptszJsonMsg = (TCHAR*)malloc(nUPLen);
	if (NULL == ptszJsonMsg)
	{
		printf("申请内存失败，无法继续！\n");
		return 0;
	}
	memset(ptszJsonMsg, '\0', nUPLen);
	memset(&st_XLogConfig, '\0', sizeof(HELPCOMPONENTS_XLOG_CONFIGURE));
	memset(&st_ServiceConfig, '\0', sizeof(XENGINE_SERVERCONFIG));

	if (!UPDater_Parament(argc, argv))
	{
		printf("参数解析失败,无法继续\n");
		return FALSE;
	}
	st_XLogConfig.XLog_MaxBackupFile = st_ServiceConfig.st_XLog.nMaxCount;
	st_XLogConfig.XLog_MaxSize = st_ServiceConfig.st_XLog.nMaxSize;
	_tcscpy(st_XLogConfig.tszFileName, st_ServiceConfig.st_XLog.tszLogFile);

	xhLog = HelpComponents_XLog_Init(HELPCOMPONENTS_XLOG_OUTTYPE_FILE | HELPCOMPONENTS_XLOG_OUTTYPE_STD, &st_XLogConfig);
	if (NULL == xhLog)
	{
		printf("初始化日志服务失败,无法继续!\n");
		goto NETSERVICE_APPEXIT;
	}
	HelpComponents_XLog_SetLogPriority(xhLog, st_ServiceConfig.st_XLog.nLogLeave);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中，初始化日志系统成功"));

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("启动服务中，初始化配置成功,配置URL:%s,配置本地列表:%s,下载路径:%s,文件下载选项:%d"), st_ServiceConfig.tszUPUrl, st_ServiceConfig.tszLocalList, st_ServiceConfig.tszDownPath, st_ServiceConfig.bIsDown);
	signal(SIGINT, Signale_Handler);
	signal(SIGTERM, Signale_Handler);
	signal(SIGABRT, Signale_Handler);

	if (st_ServiceConfig.bIsMake)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("开始构建版本列表"));
		if (!HelpModule_Api_BuildVer(st_ServiceConfig.st_Maker.tszMakePath, st_ServiceConfig.tszLocalList, 0, TRUE, st_ServiceConfig.st_Maker.tszUPFile, st_ServiceConfig.st_Maker.tszUPUrl))
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("构建标准版本列表失败！错误：%lX"), UPHelpModule_GetLastError());
			goto NETSERVICE_APPEXIT;
		}
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("构建本地版本列表成功！本地自定义列表名：%s，更新列表名：%s"), st_ServiceConfig.tszLocalList, "XEngine_Release.txt");
		goto NETSERVICE_APPEXIT;
	}

	if (!APIHelp_HttpRequest_Get(st_ServiceConfig.tszUPUrl, &ptszJsonMsg, &nUPLen))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("获取更新失败,获取新版本信息失败,错误:%lX!"), UPFileParser_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("获取网络引擎服务更新信息成功,开始获取是否存在新版本..."));
	
	if (!FileParser_ReadVer_GetRemote(ptszJsonMsg, nUPLen, &ppSt_ListRemote, &nListRemote, &nRemoteVer, &m_StrUPDes))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("获取更新,获取远程服务更新信息失败,错误:%lX"), UPFileParser_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("获取更新,远程版本:%lld,最新内容:%s"), nRemoteVer, m_StrUPDes.c_str());
	if (!FileParser_ReadVer_GetLocal(st_ServiceConfig.tszLocalList, &ppSt_ListLocal, &nListLocal, &nLocalVer))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("获取更新,获取本地文件信息失败,错误:%lX"), UPFileParser_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("获取更新,当前版本:%lld"), nLocalVer);

	if (nLocalVer >= nRemoteVer)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("获取更新失败,没有新版本可以使用!"));
		goto NETSERVICE_APPEXIT;
	}

	if (!FileParser_Match_Start(&ppSt_ListRemote, nListRemote, &ppSt_ListLocal, nListLocal, &stl_ListUPDate))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("匹配更新列表失败,错误:%lX!"), UPFileParser_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("匹配更新列表成功,需要更新的文件个数:%d..."), stl_ListUPDate.size());

	{
		if (stl_ListUPDate.empty())
		{
			XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("有更新,但是更新列表为空,无法继续"));
			goto NETSERVICE_APPEXIT;
		}
		list<FILEPARSER_VERSIONINFO>::const_iterator stl_ListIterator = stl_ListUPDate.begin();
		for (; stl_ListIterator != stl_ListUPDate.end(); stl_ListIterator++)
		{
			if (0 == stl_ListIterator->st_LocalVersion.nModuleVersion)
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("增加一个模块，模块名称：%s，老模块版本:%lld,新模块版本:%lld"), stl_ListIterator->tszModuleName, stl_ListIterator->st_LocalVersion.nModuleVersion, stl_ListIterator->nModuleVersion);
			}
			else
			{
				XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("更新一个模块，模块名称：%s，老模块版本:%lld,新模块版本:%lld"), stl_ListIterator->tszModuleName, stl_ListIterator->st_LocalVersion.nModuleVersion, stl_ListIterator->nModuleVersion);
			}
		}
	}

	if (!st_ServiceConfig.bIsDown)
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_WARN, _T("获取更新成功,但是配置为不下载更新,请手动检测下载更新并且修改本地配置版本,将自动退出"));
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("开始进行下载更新..."));

	SystemApi_File_DeleteMutilFolder(st_ServiceConfig.tszDownPath, FALSE);
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("清理临时文件成功！"));

	UPData_DlParser_CBQuery(UPDater_Callback_Download);
	if (!UPData_DlParser_Init(st_ServiceConfig.tszDownPath, &stl_ListUPDate, FALSE))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("更新失败,初始化更新器失败,错误:%lX"), UPDataDown_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("开始进行文件下载..."));

	while (bIsRun)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("开始安装更新文件..."));
	UPData_DlParser_Close();
	if (!HelpModule_Api_Install(st_ServiceConfig.tszLocalList, ptszJsonMsg, nUPLen, &stl_ListUPDate, st_ServiceConfig.tszDownPath))
	{
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_ERROR, _T("更新失败,安装文件失败,错误:%lX"), UPHelpModule_GetLastError());
		goto NETSERVICE_APPEXIT;
	}
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("更新成功,退出更新服务!"));

	BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_ListLocal, nListLocal);
	BaseLib_OperatorMemory_Free((XPPPMEM)&ppSt_ListRemote, nListRemote);

NETSERVICE_APPEXIT:

	if (bIsRun)
	{
		bIsRun = FALSE;
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("按任意键,服务器退出"));

		if (NULL != ptszJsonMsg)
		{
			BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszJsonMsg);
		}

		UPData_DlParser_Close();
		HelpComponents_XLog_Destroy(xhLog);
		getchar();
	}
#ifdef _WINDOWS
	WSACleanup();
#endif
	return 0;
}