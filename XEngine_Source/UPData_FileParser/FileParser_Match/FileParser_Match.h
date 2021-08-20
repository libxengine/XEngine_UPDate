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
    BOOL FileParser_Match_Start(FILEPARSER_VERSIONINFO*** pppSt_ListRemote, int nRemoteCount, FILEPARSER_VERSIONINFO*** pppSt_ListLocal, int nLocalCount, list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate);
};
