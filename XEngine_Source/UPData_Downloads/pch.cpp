#include "pch.h"
#include "UPData_DlParser/UPData_DlParser.h"
/********************************************************************
//	Created:	2014/7/21  16:38
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_Downloads\UPData_Downloads.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_Downloads
//	File Base:	UPData_Downloads
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	导出函数实现
//	History:
*********************************************************************/
BOOL UPData_IsErrorOccur = FALSE;
DWORD UPData_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CUPData_DlParser m_UPDataParser;
//////////////////////////////////////////////////////////////////////////
//                     更新下载器导出函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD UPDataDown_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return UPData_dwErrorCode;
}
/************************************************************************/
/*                     下载器导出函数                                   */
/************************************************************************/
extern "C" BOOL UPData_DlParser_Init(LPCTSTR lpszDownloadPath, FILEPARSER_VERSIONINFO * **pppSt_ListUPDataVer, int nListCount, BOOL bIsAll)
{
	return m_UPDataParser.UPData_DlParser_Init(lpszDownloadPath, pppSt_ListUPDataVer, nListCount, bIsAll);
}
extern "C" BOOL UPData_DlParser_CBQuery(CALLBACK_XENGINE_UPDATA_DOWNLOAD_PARSER_PROGRESS fpCall_DownloadProgress, LPVOID lParam)
{
	return m_UPDataParser.UPData_DlParser_CBQuery(fpCall_DownloadProgress, lParam);
}
extern "C" BOOL UPData_DlParser_Close()
{
	return m_UPDataParser.UPData_DlParser_Close();
}
