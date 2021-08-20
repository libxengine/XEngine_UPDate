#include "pch.h"
#include "UPData_DlParser.h"
/********************************************************************
//	Created:	2014/7/20  14:28
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_Downloads\UPData_DlParser\UPData_DlParser.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_Downloads\UPData_DlParser
//	File Base:	UPData_DlParser
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	下载解析器实现
//	History:
*********************************************************************/
CUPData_DlParser::CUPData_DlParser()
{
    m_bRun = FALSE;
    m_nDlCount = 0;
    m_nDlNumber = 0;
    m_nDlNow = 0;

    stl_ListVersion.clear();
    stl_MapVersion.clear();

    memset(tszDlPath,'\0',sizeof(tszDlPath));
}
CUPData_DlParser::~CUPData_DlParser()
{

}
//////////////////////////////////////////////////////////////////////////
//                            公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：UPData_DlParser_Init
函数功能：更新下载器初始化并且开始下载
 参数.一：lpszDownloadPath
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要下载到的目录
 参数.二：pStl_ListUPDate
  In/Out：In
  类型：STL容器指针
  可空：N
  意思：更新文件列表
 参数.三：nCount
  In/Out：In
  类型：整数型
  可空：Y
  意思：允许多少个下载任务同时存在，默认一个
返回值
  类型：逻辑型
  意思：是否初始化成功
备注：
*********************************************************************/
BOOL CUPData_DlParser::UPData_DlParser_Init(LPCTSTR lpszDownloadPath, list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate, int nCount /* = 1 */)
{
    UPData_IsErrorOccur = FALSE;

    if (NULL == lpszDownloadPath || NULL == pStl_ListUPDate)
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_INIT_PARAMENT;
        return FALSE;
    }
    if (m_bRun)
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_INIT_RUNNING;
        return FALSE;
    }
    m_nDlNumber = nCount;
    m_nDlCount = pStl_ListUPDate->size();
    //把要下载的信息压入到LIST容器中
    stl_ListVersion = *pStl_ListUPDate;
    _tcscpy(tszDlPath, lpszDownloadPath);
    m_bRun = TRUE;
    pSTDThread_Down = make_shared<std::thread>(UPData_DlParser_ThreadDown, this);
    if (!pSTDThread_Down->joinable())
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_INIT_THREADDOWN;
        return FALSE;
    }
    pSTDThread_Event = make_shared<std::thread>(UPData_DlParser_ThreadEvent, this);
    if (!pSTDThread_Event->joinable())
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_INIT_THREADEVENT;
        return FALSE;
    }

    return TRUE;
}
/********************************************************************
函数名称：UPData_DlParser_CBQuery
函数功能：设置查询回调函数
 参数.一：fpCall_DownloadProgress
  In/Out：In/Out
  类型：回调函数
  可空：N
  意思：回调函数地址，返回下载进度
 参数.二：lParam
  In/Out：In/Out
  类型：无类型指针
  可空：Y
  意思：回调函数参数
返回值
  类型：逻辑型
  意思：是否设置成功
备注：
*********************************************************************/
BOOL CUPData_DlParser::UPData_DlParser_CBQuery(CALLBACK_XENGINE_UPDATA_DOWNLOAD_PARSER_PROGRESS fpCall_DownloadProgress,LPVOID lParam)
{
    UPData_IsErrorOccur = FALSE;

    if (NULL == fpCall_DownloadProgress)
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_CBQUERT_PARAMENT;
        return FALSE;
    }
    lpCall_DownloadProgress = fpCall_DownloadProgress;
    m_lParam = lParam;
    return TRUE;
}
/********************************************************************
函数名称：UPData_DlParser_Close
函数功能：关闭更新，在更新完成后，需要关闭并且释放资源
返回值
  类型：逻辑型
  意思：是否关闭成功
备注：
*********************************************************************/
BOOL CUPData_DlParser::UPData_DlParser_Close()
{
    UPData_IsErrorOccur = FALSE;

    m_bRun = FALSE;
    //结束事件线程
    if (pSTDThread_Event->joinable())
    {
        pSTDThread_Event->join();
    }
    //结束下载线程
    if (pSTDThread_Down->joinable())
    {
        pSTDThread_Down->join();
    }
    //判断是否是全部同时下载，如果是，需要关闭句柄指针
    unordered_map<XNETHANDLE, FILEVERSION_LIST>::const_iterator stl_MapIterator = stl_MapVersion.begin();
    for (;stl_MapIterator != stl_MapVersion.end();stl_MapIterator++)
    {
        DownLoad_Http_Delete(stl_MapIterator->first);
    }
    memset(tszDlPath,'\0',sizeof(tszDlPath));

    stl_ListVersion.clear();
    stl_MapVersion.clear();
    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                            保护函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：UPData_DlParser_GetRate
函数功能：计算下载和总百分比
 参数.一：nDownCount
  In/Out： In
  类型：整数型
  可空：N
  意思：下载了多少个文件了
 参数.二：nDownSize
  In/Out：In
  类型：整数型
  可空：N
  意思：下载的大小
 参数.三：nAllSize
  In/Out：In
  类型：整数型
  可空：N
  意思：下载的总大小
 参数.四：pInt_DownRate
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：导出下载百分比
 参数.五：pInt_AllRate
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：导出总共百分比
返回值
  类型：逻辑型
  意思：是否获取成功
备注：
*********************************************************************/
BOOL CUPData_DlParser::UPData_DlParser_GetRate(int nDownCount,int nDownSize,int nAllSize,int *pInt_DownRate,int *pInt_AllRate)
{
    UPData_IsErrorOccur = FALSE;

    if ((NULL == pInt_DownRate) || (NULL == pInt_AllRate))
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_GETRATE_PARAMENT;
        return FALSE;
    }
    if (0 == nDownSize)
    {
        UPData_IsErrorOccur = TRUE;
        UPData_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_GETRATE_ZEROPARA;
        return FALSE;
    }
    if (0 == nDownCount)
    {
        *pInt_AllRate = 0;
    }
    else
    {
        *pInt_AllRate = int(double(double(nDownCount) / double(m_nDlCount)) * 100);    //获得总下载百分比
    }
    *pInt_DownRate = int(double(double(nDownSize) / double(nAllSize)) * 100);     //获得当前下载百分比
    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                            线程函数
//////////////////////////////////////////////////////////////////////////
//               下载器管理
XHTHREAD CUPData_DlParser::UPData_DlParser_ThreadDown(LPVOID lParam)
{
    CUPData_DlParser *pClass_This = (CUPData_DlParser *)lParam;
    
    list<FILEPARSER_VERSIONINFO>::const_iterator stl_ListIterator = pClass_This->stl_ListVersion.begin();
    while (pClass_This->m_bRun)
    {
		//判断下载个数是否超过指定个数
		if (pClass_This->m_nDlNumber > pClass_This->m_nDlNow)
		{
            if (stl_ListIterator == pClass_This->stl_ListVersion.end())
            {
                break;
            }
			TCHAR tszPathFile[1024];
			FILEVERSION_LIST st_FileList;

			memset(tszPathFile, '\0', sizeof(tszPathFile));
			memset(&st_FileList, '\0', sizeof(FILEVERSION_LIST));

			st_FileList.st_FileVer = *stl_ListIterator;
			_stprintf_s(tszPathFile, _T("%s%s"), pClass_This->tszDlPath, st_FileList.st_FileVer.tszModuleName);

			XNETHANDLE xhDown;
			_tremove(tszPathFile);
			//没有达到下载个数请求,开始创建下载任务
			DownLoad_Http_Create(&xhDown, st_FileList.st_FileVer.tszModuleDownload, tszPathFile);
			pClass_This->m_nDlNow++;
			pClass_This->stl_MapVersion.insert(make_pair(xhDown, st_FileList));
            stl_ListIterator++;
		}
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
//////////////////////////////////////////////////////////////////////////
//   查询下载进度和设置下载事件
XHTHREAD CUPData_DlParser::UPData_DlParser_ThreadEvent(LPVOID lParam)
{
    CUPData_DlParser *pClass_This = (CUPData_DlParser *)lParam;
    
    int nDownCount = 0;
    while (pClass_This->m_bRun)
    {
        unordered_map<XNETHANDLE, FILEVERSION_LIST>::iterator stl_MapIterator = pClass_This->stl_MapVersion.begin();
        for (;stl_MapIterator != pClass_This->stl_MapVersion.end();stl_MapIterator++)
        {
            NETDOWNLOAD_TASKINFO st_TaskInfo;
            memset(&st_TaskInfo, '\0', sizeof(NETDOWNLOAD_TASKINFO));
            if (!DownLoad_Http_Query(stl_MapIterator->first, &st_TaskInfo))
            {
                continue;
            }
            int nDownRate = 0;
            int nAllRate = 0;
            //获取下载百分比
            pClass_This->UPData_DlParser_GetRate(nDownCount, int(st_TaskInfo.dlNow), int(st_TaskInfo.dlTotal), &nDownRate, &nAllRate);
            if (ENUM_XENGINE_DOWNLOAD_STATUS_DOWNLOADDING == st_TaskInfo.en_DownStatus)
            {
                pClass_This->lpCall_DownloadProgress(stl_MapIterator->second.st_FileVer.tszModuleName, st_TaskInfo.dlNow, st_TaskInfo.dlTotal, nDownRate, nAllRate, st_TaskInfo.en_DownStatus, pClass_This->m_lParam);
            }
            else
            {
				if (!stl_MapIterator->second.bComplate)
				{
					nDownCount++;
					pClass_This->m_nDlNow--;
					stl_MapIterator->second.bComplate = TRUE;
                    //是否全部下载完毕
					if (nDownCount == pClass_This->m_nDlCount)
					{
						pClass_This->m_bRun = FALSE;
						pClass_This->lpCall_DownloadProgress(stl_MapIterator->second.st_FileVer.tszModuleName, st_TaskInfo.dlNow, st_TaskInfo.dlTotal, 100, 100, st_TaskInfo.en_DownStatus, pClass_This->m_lParam);
						break;
					}
					else
					{

						pClass_This->lpCall_DownloadProgress(stl_MapIterator->second.st_FileVer.tszModuleName, st_TaskInfo.dlNow, st_TaskInfo.dlTotal, 100, nAllRate, st_TaskInfo.en_DownStatus, pClass_This->m_lParam);
					}
				}
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}
