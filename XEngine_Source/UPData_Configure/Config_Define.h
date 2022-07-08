#pragma once
/********************************************************************
//    Created:     2021/08/17  14:49:08
//    File Name:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Config_Define.h
//    File Path:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure
//    File Base:   Config_Define
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出的定义
//    History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                        导出的数据结构
//////////////////////////////////////////////////////////////////////////
typedef struct tag_XEngine_ServerConfig
{
	TCHAR tszUPUrl[MAX_PATH];
	TCHAR tszLocalList[MAX_PATH];
	TCHAR tszDownPath[MAX_PATH];
	BOOL bIsDown;
	int nDlCount;
	struct  
	{
		BOOL bIsMake;
		TCHAR tszMakePath[MAX_PATH];
		TCHAR tszUPUrl[MAX_PATH];
	}st_Maker;
    struct
    {
		TCHAR tszLogFile[MAX_PATH];
        int nMaxSize;
        int nMaxCount;
        int nLogLeave;
    }st_XLog;
	struct  
	{
		list<string>* pStl_ListVer;
	}st_XVer;
}XENGINE_SERVERCONFIG;
//////////////////////////////////////////////////////////////////////////
//                        导出函数定义
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD Configure_GetLastError(int *pInt_ErrorCode = NULL);
/************************************************************************/
/*                        文件配置读取                                  */
/************************************************************************/
extern "C" BOOL Configure_File_Json(LPCTSTR lpszConfigFile, XENGINE_SERVERCONFIG * pSt_ServerConfig);
