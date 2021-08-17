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
    BOOL FileParser_ReadVer_GetUPVersion(LPCTSTR lpszWebHost,TCHAR *ptszUPMsg, int *pInt_Len);
    BOOL FileParser_ReadVer_GetDescription(LPCTSTR lpszJsonMsg, int nMsgLen, TCHAR *ptszUPDes, int *pInt_Len);
protected:
private:
};
