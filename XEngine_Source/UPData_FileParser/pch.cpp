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
extern "C" BOOL FileParser_ReadVer_GetRemote(LPCTSTR lpszJsonMsg, int nMsgLen, FILEPARSER_VERSIONINFO * **pppSt_FileList, int* pInt_Count, __int64x * pInt_Version, string * pStrDes)
{
	return m_FileRead.FileParser_ReadVer_GetRemote(lpszJsonMsg, nMsgLen, pppSt_FileList, pInt_Count, pInt_Version, pStrDes);
}
extern "C" BOOL FileParser_ReadVer_GetLocal(LPCTSTR lpszFileList, FILEPARSER_VERSIONINFO * **pppSt_FileList, int* pInt_Count, __int64x * pInt_Version)
{
	return m_FileRead.FileParser_ReadVer_GetLocal(lpszFileList, pppSt_FileList, pInt_Count, pInt_Version);
}
/************************************************************************/
/*                文件匹配器导出函数                                    */
/************************************************************************/
extern "C" BOOL FileParser_Match_Start(FILEPARSER_VERSIONINFO * **pppSt_ListRemote, int nRemoteCount, FILEPARSER_VERSIONINFO * **pppSt_ListLocal, int nLocalCount, list<FILEPARSER_VERSIONINFO>*pStl_ListUPDate)
{
	return m_FileMatch.FileParser_Match_Start(pppSt_ListRemote, nRemoteCount, pppSt_ListLocal, nLocalCount, pStl_ListUPDate);
}
