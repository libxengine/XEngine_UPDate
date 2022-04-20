#pragma once
/********************************************************************
//	Created:	2014/7/18  14:46
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_Define.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser
//	File Base:	FileParser_Define
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	更新组件，文件解析器导出定义
//	History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                导出的数据结构
//////////////////////////////////////////////////////////////////////////
typedef struct tag_FileParser_VersionInfo
{
    CHAR tszModulePath[MAX_PATH];                                         //模块路径,新增加的必须拥有此值
    CHAR tszModuleName[MAX_PATH];                                         //模块名称
    CHAR tszModuleDownload[MAX_PATH];                                     //模块下载地址
    CHAR tszModuleCode[MAX_PATH];                                         //远程模块标识符
    __int64x nModuleVersion;                                               //文件版本号
    BOOL bIsRun;                                                          //安装完成是否运行
    struct
    {
        __int64x nModuleVersion;
        CHAR tszMoudelPath[MAX_PATH];
        CHAR tszMoudelName[MAX_PATH];
        CHAR tszMoudelCode[MAX_PATH];
    }st_LocalVersion;
}FILEPARSER_VERSIONINFO,*LPFILEPARSER_VERSIONINFO;
//////////////////////////////////////////////////////////////////////////
//                导出的函数
//////////////////////////////////////////////////////////////////////////
extern "C" DWORD UPFileParser_GetLastError(int *pInt_SysError = NULL);
/************************************************************************/
/*                文件解析器导出函数                                    */
/************************************************************************/
/********************************************************************
函数名称：FileParser_ReadVer_GetRemote
函数功能：获取更新内容
 参数.一：lpszJsonMsg
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：通过获取到的新版本JSON信息来获取更新内容
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入JSON缓冲区大小
 参数.三：pppSt_FileList
  In/Out：Out
  类型：三级指针
  可空：N
  意思：导出获取到的文件列表
 参数.四：pInt_Count
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出获取到的列表个数
 参数.五：pInt_Version
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出新版本值
 参数.六：pStrDes
  In/Out：Out
  类型：string类
  可空：Y
  意思：输出获取到的更新描述
返回值
  类型：逻辑型
  意思：是否获取成功
备注：
*********************************************************************/
extern "C" BOOL FileParser_ReadVer_GetRemote(LPCTSTR lpszJsonMsg, int nMsgLen, FILEPARSER_VERSIONINFO*** pppSt_FileList, int* pInt_Count, __int64x* pInt_Version = NULL, string* pStrDes = NULL);
/********************************************************************
函数名称：FileParser_ReadVer_GetLocal
函数功能：获取本地内容
 参数.一：lpszFileList
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：本地列表地址
 参数.二：pppSt_FileList
  In/Out：Out
  类型：三级指针
  可空：N
  意思：导出获取到的文件列表
 参数.三：pInt_Count
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出获取到的列表个数
 参数.四：pInt_Version
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：输出版本值
返回值
  类型：逻辑型
  意思：是否获取成功
备注：
*********************************************************************/
extern "C" BOOL FileParser_ReadVer_GetLocal(LPCTSTR lpszFileList, FILEPARSER_VERSIONINFO*** pppSt_FileList, int* pInt_Count, __int64x* pInt_Version = NULL);
/************************************************************************/
/*                文件匹配器导出函数                                    */
/************************************************************************/
/********************************************************************
函数名称：FileParser_Match_Start
函数功能：开始匹配新版本
 参数.一：pppSt_ListRemote
  In/Out：In
  类型：三级指针
  可空：N
  意思：远程更新文件列表信息
 参数.二：nRemoteCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入远程文件个数
 参数.三：pppSt_ListLocal
  In/Out：In
  类型：三级指针
  可空：N
  意思：输入本地文件列表信息
 参数.四：nLocalCount
  In/Out：In
  类型：整数型
  可空：N
  意思：输入本地列表文件信息
 参数.五：pStl_ListUPDate
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：输出要更新的文件列表信息
返回值
  类型：逻辑型
  意思：是否有新版本
备注：
*********************************************************************/
extern "C" BOOL FileParser_Match_Start(FILEPARSER_VERSIONINFO * **pppSt_ListRemote, int nRemoteCount, FILEPARSER_VERSIONINFO * **pppSt_ListLocal, int nLocalCount, list<FILEPARSER_VERSIONINFO>*pStl_ListUPDate);
