#pragma once
/********************************************************************
//	Created:	2014/7/17  15:12
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_Downloads\UPData_DlParser\UPData_DlParser.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_Downloads\UPData_DlParser
//	File Base:	UPData_DlParser
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	更新器下载分析模块
//	History:
*********************************************************************/
typedef struct
{
    BOOL bComplate;
    FILEPARSER_VERSIONINFO st_FileVer;
}FILEVERSION_LIST;

class CUPData_DlParser
{
public:
    CUPData_DlParser();
    ~CUPData_DlParser();
public:
    BOOL UPData_DlParser_Init(LPCTSTR lpszDownloadPath,FILEPARSER_VERSIONINFO*** pppSt_ListUPDataVer, int nListCount,BOOL bIsAll = FALSE);
    BOOL UPData_DlParser_CBQuery(CALLBACK_XENGINE_UPDATA_DOWNLOAD_PARSER_PROGRESS fpCall_DownloadProgress,LPVOID lParam = NULL);
    BOOL UPData_DlParser_Close();
protected:
    BOOL UPData_DlParser_GetRate(int nDownCount,int nDownSize,int nAllSize,int *pInt_DownRate,int *pInt_AllRate);
protected:
    static XHTHREAD UPData_DlParser_ThreadDown(LPVOID lParam);
    static XHTHREAD UPData_DlParser_ThreadEvent(LPVOID lParam);
private:
    TCHAR tszDlPath[MAX_PATH];
    int m_nDlCount;
    BOOL m_bRun;
    BOOL m_bAll;
private:
    shared_ptr<std::thread> pSTDThread_Down;
    shared_ptr<std::thread> pSTDThread_Event;
private:
    LPVOID m_lParam;
    CALLBACK_XENGINE_UPDATA_DOWNLOAD_PARSER_PROGRESS lpCall_DownloadProgress;
private:
    list<FILEPARSER_VERSIONINFO> stl_ListVersion;
    unordered_map<XNETHANDLE,FILEVERSION_LIST> stl_MapVersion;
};
