#include "pch.h"
#include "HelpModule_Api/HelpModule_Api.h"
/********************************************************************
//	Created:	2014/8/15  16:21
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule\UPData_HelpModule.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule
//	File Base:	UPData_HelpModule
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	更新帮助模块导出函数实现
//	History:
*********************************************************************/
BOOL HelpModule_IsErrorOccur = FALSE;
DWORD HelpModule_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CHelpModule_Api m_HelpApi;
//////////////////////////////////////////////////////////////////////////
//                           导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD UPHelpModule_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return HelpModule_dwErrorCode;
}
/************************************************************************/
/*                           帮助函数导出                               */
/************************************************************************/
extern "C" BOOL HelpModule_Api_Install(LPCTSTR lpszLocalFile, LPCTSTR lpszRemoteJson, int nMsgLen, FILEPARSER_VERSIONINFO * **pppSt_ListUPDataVer, int nListCount, LPCTSTR lpszDlPath)
{
	return m_HelpApi.HelpModule_Api_Install(lpszLocalFile, lpszRemoteJson, nMsgLen, pppSt_ListUPDataVer, nListCount, lpszDlPath);
}
extern "C" BOOL HelpModule_Api_BuildVer(LPCTSTR lpszPath, LPCTSTR lpszLocalFile, __int64x nFileVer, BOOL bSubDir, LPCTSTR lpszUPFile, LPCTSTR lpszDlUrl, LPCTSTR lpszCfgPath)
{
	return m_HelpApi.HelpModule_Api_BuildVer(lpszPath, lpszLocalFile, nFileVer, bSubDir, lpszUPFile, lpszDlUrl, lpszCfgPath);
}
