﻿// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

#ifdef _WINDOWS
// 添加要在此处预编译的标头
#include "framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <json/json.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifdef _CENTOS
#include <json/json.h>
#else
#include <jsoncpp/json/json.h>
#endif
#endif
#endif //PCH_H
#include <list>
using namespace std;
#include "../../XEngine_CommHdr.h"
#include "../../XEngine_Types.h"
#include "../../XEngine_Lib/XEngine_BaseLib/BaseLib_Define.h"
#include "../../XEngine_Lib/XEngine_BaseLib/BaseLib_Error.h"
#include "../../XEngine_SystemSdk/XEngine_ProcSdk/ProcFile_Define.h"
#include "../../XEngine_SystemSdk/XEngine_SystemApi/SystemApi_Define.h"
#include "../../XEngine_SystemSdk/XEngine_SystemApi/SystemApi_Error.h"
#include "../UPData_FileParser/FileParser_Define.h"
#include "../UPData_FileParser/FileParser_Error.h"
#include "HelpModule_Define.h"
#include "HelpModule_Error.h"
/********************************************************************
//    Created:     2021/04/08  13:44:34
//    File Name:   H:\XEngine\XEngine_SourceCode\XEngine_UPData\UPData_HelpModule\pch.h
//    File Path:   H:\XEngine\XEngine_SourceCode\XEngine_UPData\UPData_HelpModule
//    File Base:   pch
//    File Ext:    h
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     公共头文件
//    History:
*********************************************************************/
extern BOOL HelpModule_IsErrorOccur;
extern DWORD HelpModule_dwErrorCode;

#ifdef _WINDOWS
#ifdef _DEBUG
#pragma comment(lib,"../../Debug/UPData_FileParser.lib")
#pragma comment(lib,"../../Debug/XEngine_SystemApi.lib")
#pragma comment(lib,"../../Debug/XEngine_BaseLib.lib")
#else
#ifdef _WIN64
#pragma comment(lib,"../../x64/Release/UPData_FileParser.lib")
#pragma comment(lib,"../../x64/Release/XEngine_SystemApi.lib")
#pragma comment(lib,"../../x64/Release/XEngine_BaseLib.lib")
#else
#pragma comment(lib,"../../Release/UPData_FileParser.lib")
#pragma comment(lib,"../../Release/XEngine_SystemApi.lib")
#pragma comment(lib,"../../Release/XEngine_BaseLib.lib")
#endif // _WIN64
#endif
#pragma comment(lib,"lib_json.lib")
#else

#endif