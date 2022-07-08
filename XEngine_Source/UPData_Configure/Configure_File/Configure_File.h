#pragma once
/********************************************************************
//    Created:     2022/07/08  13:44:38
//    File Name:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Configure_File\Configure_File.h
//    File Path:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Configure_File
//    File Base:   Configure_File
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     文件配置信息操作
//    History:
*********************************************************************/

class CConfigure_File
{
public:
    CConfigure_File();
    ~CConfigure_File();
public:
    BOOL Configure_File_Json(LPCTSTR lpszConfigFile, XENGINE_SERVERCONFIG* pSt_ServerConfig);
};
