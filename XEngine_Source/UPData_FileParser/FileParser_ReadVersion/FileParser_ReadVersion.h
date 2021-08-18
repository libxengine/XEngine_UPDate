#pragma once
/********************************************************************
//	Created:	2014/7/17  16:41
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_ReadVersion\FileParser_ReadVersion.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_ReadVersion
//	File Base:	FileParser_ReadVersion
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	读取版本类
//	History:
*********************************************************************/
class CFileParser_ReadVersion
{
public:
    CFileParser_ReadVersion();
    ~CFileParser_ReadVersion();
public:
    BOOL FileParser_ReadVer_GetRemote(LPCTSTR lpszJsonMsg, int nMsgLen, FILEPARSER_VERSIONINFO*** pppSt_FileList, int* pInt_Count, __int64x* pInt_Version = NULL, string* pStrDes = NULL);
	BOOL FileParser_ReadVer_GetLocal(LPCTSTR lpszFileList, FILEPARSER_VERSIONINFO*** pppSt_FileList, int* pInt_Count, __int64x* pInt_Version = NULL);
protected:
private:
};
