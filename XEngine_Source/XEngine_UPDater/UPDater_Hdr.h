#pragma once
#ifdef _WINDOWS
#include <Windows.h>
#include <tchar.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <XEngine_Include/XEngine_CommHdr.h>
#include <XEngine_Include/XEngine_Types.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Define.h>
#include <XEngine_Include/XEngine_BaseLib/BaseLib_Error.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Define.h>
#include <XEngine_Include/XEngine_HelpComponents/XLog_Error.h>
#include "../UPData_FileParser/FileParser_Define.h"
#include "../UPData_FileParser/FileParser_Error.h"
#include "../UPData_Downloads/UPDataDl_Define.h"
#include "../UPData_Downloads/UPDataDl_Error.h"
#include "../UPData_HelpModule/HelpModule_Define.h"
#include "../UPData_HelpModule/HelpModule_Error.h"
#include "../UPData_Configure/Config_Define.h"
#include "../UPData_Configure/Config_Error.h"
/********************************************************************
//    Created:     2021/08/17  14:58:12
//    File Name:   D:\XEngine_UPDate\XEngine_Source\XEngine_UPDater\UPDater_Hdr.h
//    File Path:   D:\XEngine_UPDate\XEngine_Source\XEngine_UPDater
//    File Base:   UPDater_Hdr
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公用头文件
//    History:
*********************************************************************/
extern BOOL bIsRun;
extern XLOG xhLog;
extern XENGINE_SERVERCONFIG st_ServiceConfig;

#include "UPDater_Config.h"
#include "UPDater_Net.h"

#ifdef _WINDOWS
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"x86/XEngine_BaseLib/XEngine_BaseLib.lib")
#pragma comment(lib,"x86/XEngine_HelpComponents/HelpComponents_XLog.lib")
#pragma comment(lib,"../Debug/UPData_FileParser.lib")
#pragma comment(lib,"../Debug/UPData_Downloads.lib")
#pragma comment(lib,"../Debug/UPData_HelpModule.lib")
#pragma comment(lib,"../Debug/UPData_Configure.lib")
#else
#endif