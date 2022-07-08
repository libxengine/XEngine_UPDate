#include "pch.h"
#include "Configure_File/Configure_File.h"
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
CConfigure_File m_Config;
//////////////////////////////////////////////////////////////////////////
//                      导出函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD Configure_GetLastError(int* pInt_SysError)
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
extern "C" BOOL Configure_File_Json(LPCTSTR lpszConfigFile, XENGINE_SERVERCONFIG * pSt_ServerConfig)
{
	return m_Config.Configure_File_Json(lpszConfigFile, pSt_ServerConfig);
}