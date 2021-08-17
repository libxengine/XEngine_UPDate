#include "UPDater_Hdr.h"

BOOL UPDater_Parament(int argc, char **argv)
{
	LPCTSTR lpszFile = _T("./XEngine_Config/XEngine_Config.ini");
	if (!Config_Ini_File(lpszFile, &st_ServiceConfig))
	{
		printf("解析配置文件失败,Config_Ini_File:%lX\n", Config_GetLastError());
		return FALSE;
	}

	for (int i = 0;i < argc;i++)
	{
		if ((0 == _tcscmp("-h", argv[i])) || (0 == _tcscmp("-H", argv[i])))
		{
			UPDater_ParamentHelp();
			return FALSE;
		}
		if ((0 == _tcscmp("-v", argv[i])) || (0 == _tcscmp("-V", argv[i])))
		{
			printf("Version：V1.1.0\n");
			return FALSE;
		}
		else if (0 == _tcscmp("-p", argv[i]))
		{
			memset(st_ServiceConfig.tszDownPath, '\0', sizeof(st_ServiceConfig.tszDownPath));
			_tcscpy_s(st_ServiceConfig.tszDownPath, MAX_PATH, argv[i + 1]);
		}
		else if (0 == _tcscmp("-m", argv[i]))
		{
			st_ServiceConfig.bIsMake = TRUE;
			memset(st_ServiceConfig.st_Maker.tszMakePath, '\0', sizeof(st_ServiceConfig.st_Maker.tszMakePath));
			_tcscpy_s(st_ServiceConfig.st_Maker.tszMakePath, MAX_PATH, argv[i + 1]);
		}
		else if (0 == _tcscmp("-l", argv[i]))
		{
			st_ServiceConfig.st_XLog.nLogLeave = _ttoi(argv[i + 1]);
		}
		else if (0 == _tcscmp("-d", argv[i]))
		{
			st_ServiceConfig.bIsDown = _ttoi(argv[i + 1]);
		}
	}

	return TRUE;
}

void UPDater_ParamentHelp()
{
	printf(_T("--------------------------启动参数帮助开始--------------------------\n"));
	printf(_T("更新服务启动参数：程序 参数 参数值，参数是区分大小写的\n"));
	printf(_T("-h or -H：启动参数帮助提示信息\n"));
	printf(_T("-v or -V：查看系统版本\n"));
	printf(_T("-p：设置更新文件下载的目录,默认:./UPFile/\n"));
	printf(_T("-m：构建本地版本更新列表，需要参数设置要构建软件版本的目录,目录默认需要添加/符号.\n"));
	printf(_T("-l：设置本地日志记录信息级别\n"));
	printf(_T("-d：设置有新版本是否下载文件,默认0不下载,1位下载\n"));
	printf(_T("--------------------------启动参数帮助结束--------------------------\n"));
}