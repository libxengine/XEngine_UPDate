#pragma once
/********************************************************************
//	Created:	2014/7/25  17:53
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule\HelpModule_Define.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule
//	File Base:	HelpModule_Define
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	更新帮助模块导出函数
//	History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                           导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD UPHelpModule_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                           帮助函数导出                               */
/************************************************************************/
/********************************************************************
函数名称：HelpModule_Api_Copy
函数功能：拷贝新文件到指定目录
 参数.一：pStl_ListUPDate
  In/Out：In
  类型：容器指针
  可空：N
  意思：更新的文件列表信息
 参数.二：lpszDlPath
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：下载的路径
 参数.三：bDelFile
  In/Out：In
  类型：逻辑型
  可空：Y
  意思：是否删除原始文件
返回值
  类型：逻辑型
  意思：是否拷贝成功
备注：
*********************************************************************/
extern "C" BOOL HelpModule_Api_Copy(list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate, LPCTSTR lpszDlPath = NULL, BOOL bDelFile = TRUE);
/********************************************************************
函数名称：HelpModule_Api_SetVersion
函数功能：设置文件版本
 参数.一：lpszLocalListFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：本地文件列表名称
 参数.二：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：更新文件列表的信息结构
 参数.三：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：缓冲区大小
返回值
  类型：逻辑型
  意思：是否设置成功
备注：
*********************************************************************/
extern "C" BOOL HelpModule_Api_SetVersion(LPCTSTR lpszLocalFile, LPCTSTR lpszMsgBuffer, int nMsgLen);
/********************************************************************
函数名称：HelpModule_Api_RunExec
函数功能：运行一个程序
 参数.一：pStl_ListUPDate
  In/Out：In
  类型：容器指针
  可空：N
  意思：文件更新运行列表
返回值
  类型：逻辑型
  意思：是否执行成功
备注：
*********************************************************************/
extern "C" BOOL HelpModule_Api_RunExec(list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate);
/********************************************************************
函数名称：HelpModule_Api_Clear
函数功能：清理工作执行
 参数.一：lpszRemoteJson
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：清理列表
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
extern "C" BOOL HelpModule_Api_Clear(LPCTSTR lpszRemoteJson, int nMsgLen);
/********************************************************************
函数名称：HelpModule_Api_BuildVer
函数功能：构建应用更新文件
 参数.一：lpszPath
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：要构建哪个目录中的所有文件列表
 参数.二：lpszLocalFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：构建好的更新数据结构保存到哪个地方
 参数.三：nFileVer
  In/Out：In
  类型：整数型
  可空：Y
  意思：构建的当前版本号，如果为0，那么会采用当前年月日为版本
 参数.四：bSubDir
  In/Out：In
  类型：逻辑型
  可空：Y
  意思：是否包含子目录，是否把子目录下的所有文件都构建成更新包
 参数.五：lpszUPFile
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：构建要更新的数据结构列表，可以不使用，自己编写更新的JSON
 参数.六：lpszDlUrl
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：第五个参数有值，这个参数必须有值，这个将设置更新的下载地址，使用
           http://www.xxx.com/UPFile/ 表示，我们会自动填充后面的文件名和路径
 参数.七：lpszCfgPath
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：如果不为NULL,指定所有模块配置文件目录
返回值
  类型：逻辑型
  意思：是否构建成功
备注：次函数可以帮助你快速构建一个可更新的文件列表，方便你快速使用我们的更新SDK
*********************************************************************/
extern "C" BOOL HelpModule_Api_BuildVer(LPCSTR lpszPath, LPCSTR lpszLocalFile, __int64x nFileVer = 0, BOOL bSubDir = TRUE, LPCSTR lpszUPFile = NULL, LPCSTR lpszDlUrl = NULL,LPCSTR lpszCfgPath = NULL);
