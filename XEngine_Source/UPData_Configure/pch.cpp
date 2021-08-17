#include "pch.h"
#include "Config_ini/Config_ini.h"
/********************************************************************
//    Created:     2021/08/17  14:49:40
//    File Name:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\pch.cpp
//    File Path:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure
//    File Base:   pch
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     导出实现
//    History:
*********************************************************************/
BOOL Config_IsErrorOccur = FALSE;
DWORD Config_dwErrorCode = 0;
//////////////////////////////////////////////////////////////////////////
CConfig_Ini m_Config;
//////////////////////////////////////////////////////////////////////////
//                      导出函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD Config_GetLastError(int* pInt_SysError)
{
	if (NULL != pInt_SysError)
	{
		*pInt_SysError = errno;
	}
	return Config_dwErrorCode;
}
/************************************************************************/
/*                              配置文件导出函数                        */
/************************************************************************/
extern "C" BOOL Config_Ini_File(LPCTSTR lpszConfigFile, XENGINE_SERVERCONFIG * pSt_ServerConfig)
{
	return m_Config.Config_Ini_File(lpszConfigFile, pSt_ServerConfig);
}