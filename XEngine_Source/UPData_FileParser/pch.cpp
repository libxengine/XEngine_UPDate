#include "pch.h"
#include "FileParser_Match/FileParser_Match.h"
#include "FileParser_ReadVersion/FileParser_ReadVersion.h"
/********************************************************************
//	Created:	2014/7/18  14:47
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\UPData_FileParser.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser
//	File Base:	UPData_FileParser
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	文件解析器导出实现
//	History:
*********************************************************************/
BOOL FileParser_IsErrorOccur = FALSE;
DWORD FileParser_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CFileParser_Match m_FileMatch;
CFileParser_ReadVersion m_FileRead;
//////////////////////////////////////////////////////////////////////////
//                导出的函数实现
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD UPFileParser_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return FileParser_dwErrorCode;
}
/************************************************************************/
/*                文件解析器导出函数                                    */
/************************************************************************/
extern "C" BOOL FileParser_ReadVer_GetUPVersion(LPCTSTR lpszWebHost, TCHAR * ptszUPMsg, int* pInt_Len)
{
	return m_FileRead.FileParser_ReadVer_GetUPVersion(lpszWebHost, ptszUPMsg, pInt_Len);
}
extern "C" BOOL FileParser_ReadVer_GetDescription(LPCTSTR lpszJsonMsg, int nMsgLen, TCHAR * ptszUPDes, int* pInt_Len)
{
	return m_FileRead.FileParser_ReadVer_GetDescription(lpszJsonMsg, nMsgLen, ptszUPDes, pInt_Len);
}
/************************************************************************/
/*                文件匹配器导出函数                                    */
/************************************************************************/
extern "C" BOOL FileParser_Match_Start(LPCTSTR lpszFileName, LPCTSTR lpszJsonMsg, int nMsgLen, FILEPARSER_VERSIONINFO * **pppSt_ListUPDataVer, int* pInt_ListCount, __int64x* pInt_LocalVer, __int64x* pInt_NewVer)
{
	return m_FileMatch.FileParser_Match_Start(lpszFileName, lpszJsonMsg, nMsgLen, pppSt_ListUPDataVer, pInt_ListCount, pInt_LocalVer, pInt_NewVer);
}
