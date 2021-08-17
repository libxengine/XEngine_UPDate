#include "pch.h"
#include "Config_Ini.h"
/********************************************************************
//    Created:     2021/08/17  13:57:45
//    File Name:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Config_ini\Config_ini.cpp
//    File Path:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Config_ini
//    File Base:   Config_ini
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     文件配置信息操作
//    History:
*********************************************************************/
CConfig_Ini::CConfig_Ini()
{

}
CConfig_Ini::~CConfig_Ini()
{

}
//////////////////////////////////////////////////////////////////////////
//                        公用函数
//////////////////////////////////////////////////////////////////////////
BOOL CConfig_Ini::Config_Ini_File(LPCTSTR lpszConfigFile, XENGINE_SERVERCONFIG* pSt_FileConfig)
{
    Config_IsErrorOccur = FALSE;

    if ((NULL == lpszConfigFile) || (NULL == pSt_FileConfig))
    {
        Config_IsErrorOccur = TRUE;
        Config_dwErrorCode = ERROR_UPDATE_MODULE_CONFIG_INI_PARAMENT;
        return FALSE;
    }
	pSt_FileConfig->bIsDown = GetPrivateProfileInt(_T("ServiceConfig"), _T("bIsDown"), 0, lpszConfigFile);
	pSt_FileConfig->bIsMake = GetPrivateProfileInt(_T("ServiceConfig"), _T("ThreadPool"), 0, lpszConfigFile);
	GetPrivateProfileString(_T("ServiceConfig"), _T("tszUPUrl"), NULL, pSt_FileConfig->tszUPUrl, MAX_PATH, lpszConfigFile);
	GetPrivateProfileString(_T("ServiceConfig"), _T("tszLocalList"), NULL, pSt_FileConfig->tszLocalList, MAX_PATH, lpszConfigFile);
	GetPrivateProfileString(_T("ServiceConfig"), _T("tszDownPath"), NULL, pSt_FileConfig->tszDownPath, MAX_PATH, lpszConfigFile);

	pSt_FileConfig->st_XLog.nLogLeave = GetPrivateProfileInt(_T("ServiceXLog"), _T("nLogLeave"), 0, lpszConfigFile);
	pSt_FileConfig->st_XLog.nMaxCount = GetPrivateProfileInt(_T("ServiceXLog"), _T("nMaxCount"), 0, lpszConfigFile);
	pSt_FileConfig->st_XLog.nMaxSize = GetPrivateProfileInt(_T("ServiceXLog"), _T("nMaxSize"), 0, lpszConfigFile);
	GetPrivateProfileString(_T("ServiceXLog"), _T("tszLogFile"), NULL, pSt_FileConfig->st_XLog.tszLogFile, MAX_PATH, lpszConfigFile);
    return TRUE;
}
