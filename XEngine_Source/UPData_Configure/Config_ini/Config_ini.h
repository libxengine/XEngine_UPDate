#pragma once
/********************************************************************
//    Created:     2021/08/17  13:57:38
//    File Name:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Config_ini\Config_ini.h
//    File Path:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Config_ini
//    File Base:   Config_ini
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     文件配置信息操作
//    History:
*********************************************************************/

class CConfig_Ini
{
public:
    CConfig_Ini();
    ~CConfig_Ini();
public:
    BOOL Config_Ini_File(LPCTSTR lpszConfigFile,XENGINE_SERVERCONFIG *pSt_ServerConfig);
};
