#pragma once
/********************************************************************
//	Created:	2014/7/17  15:15
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_Match\FileParser_Match.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_Match
//	File Base:	FileParser_Match
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	更新组件，文件分析器，匹配方式
//	History:
*********************************************************************/

class CFileParser_Match
{
public:
    CFileParser_Match();
    ~CFileParser_Match();
public:
    BOOL FileParser_Match_Start(LPCTSTR lpszFileName, LPCTSTR lpszJsonMsg, int nMsgLen, FILEPARSER_VERSIONINFO*** pppSt_ListUPDataVer, int* pInt_ListCount,__int64x *pInt_LocalVer = NULL,__int64x *pInt_NewVer = NULL);
protected:
    BOOL FileParser_Match_InitFile(LPCTSTR lpszMsgBuffer, int nMsgLen, __int64x *pInt_LocalVersion, list<FILEPARSER_VERSIONINFO> *pStl_ListCurrentVer);
    BOOL FileParser_Match_FileVersion(FILEPARSER_VERSIONINFO *pSt_VersionInfo, list<FILEPARSER_VERSIONINFO> *pStl_ListCurrentVer);
private:
};
