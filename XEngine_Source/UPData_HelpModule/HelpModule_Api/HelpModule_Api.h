#pragma once
/********************************************************************
//	Created:	2014/7/25  17:54
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule\HelpModule_Api\HelpModule_Api.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule\HelpModule_Api
//	File Base:	HelpModule_Api
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	帮助模块API函数
//	History:
*********************************************************************/

typedef struct tag_HelpModule_FileList
{
    TCHAR tszFilePath[MAX_PATH];
    TCHAR tszFileName[MAX_PATH];
}HELPMODULE_FILELIST,*LPHELPMODULE_FILELIST;

class CHelpModule_Api
{
public:
    CHelpModule_Api();
    ~CHelpModule_Api();
public:
    BOOL HelpModule_Api_Copy(list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate, LPCTSTR lpszDlPath = NULL, BOOL bDelFile = TRUE);
	BOOL HelpModule_Api_SetVersion(LPCTSTR lpszLocalFile, LPCTSTR lpszMsgBuffer, int nMsgLen);
	BOOL HelpModule_Api_RunExec(list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate);
	BOOL HelpModule_Api_Clear(LPCTSTR lpszRemoteJson, int nMsgLen);
    BOOL HelpModule_Api_BuildVer(LPCTSTR lpszPath, LPCTSTR lpszLocalFile, __int64x nFileVer = 0, BOOL bSubDir = TRUE, LPCTSTR lpszUPFile = NULL, LPCTSTR lpszDlUrl = NULL,LPCTSTR lpszCfgPath = NULL);
protected:

protected:
    static BOOL CALLBACK HelpModule_Api_EnumFile(LPCSTR lpFileOrPath, BOOL bFindPath, LPVOID lParam);
private:
};
