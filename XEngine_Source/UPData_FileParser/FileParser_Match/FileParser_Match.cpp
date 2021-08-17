#include "pch.h"
#include "FileParser_Match.h"
/********************************************************************
//	Created:	2014/7/17  15:18
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_Match\FileParser_Match.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_Match
//	File Base:	FileParser_Match
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	文件匹配器实现
//	History:
*********************************************************************/
CFileParser_Match::CFileParser_Match()
{
}
CFileParser_Match::~CFileParser_Match()
{

}
//////////////////////////////////////////////////////////////////////////
//                          公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：FileParser_Match_Start
函数功能：开始匹配新版本
 参数.一：lpszFileName
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：本地文件版本信息路径
 参数.二：lpszJsonMsg
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：要解析的JSON内存缓冲区
 参数.三：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入JSON缓冲区大小
 参数.四：pppSt_ListUPDataVer
  In/Out：Out
  类型：三级指针
  可空：N
  意思：导出要更新的文件信息结构
 参数.五：pInt_ListCount
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：文件列表个数
 参数.六：pInt_LocalVer
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：导出获取到的本地版本号
 参数.七：pInt_NewVer
  In/Out：Out
  类型：整数型指针
  可空：Y
  意思：导出获取到的最新版本号
返回值
  类型：逻辑型
  意思：是否有新版本
备注：参数pppSt_ListUPDataVer必须调用基础库的BaseLib_OperatorMemory_Free函数进行内存释放
*********************************************************************/
BOOL CFileParser_Match::FileParser_Match_Start(LPCTSTR lpszFileName, LPCTSTR lpszJsonMsg, int nMsgLen, FILEPARSER_VERSIONINFO*** pppSt_ListUPDataVer, int* pInt_ListCount, __int64x* pInt_LocalVer /* = NULL */, __int64x* pInt_NewVer /* = NULL */)
{
    FileParser_IsErrorOccur = FALSE;

    if ((NULL == lpszFileName) && (NULL == lpszJsonMsg))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_PARAMENT;
        return FALSE;
    }
    Json::Value st_JsonRoot;
    Json::Value st_JsonArray;
    Json::CharReaderBuilder st_JsonBuild;
    Json::CharReader* pSt_JsonReader(st_JsonBuild.newCharReader());

    JSONCPP_STRING st_JsonError;
    //先解析JSON是否正确
    if (!pSt_JsonReader->parse(lpszJsonMsg, lpszJsonMsg + nMsgLen, &st_JsonRoot, &st_JsonError))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_JSON;
        return FALSE;
    }
    delete pSt_JsonReader;
    pSt_JsonReader = NULL;
    //在获取文件内容
    int nCount = 0;
    TCHAR *ptszJsonFile = new TCHAR[1024 * 1024 * 10];
    if (NULL == ptszJsonFile)
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_MALLOC;
        return FALSE;
    }
    memset(ptszJsonFile, '\0', 1024 * 1024 * 10);
    FILE *pSt_File = _tfopen(lpszFileName, _T("rb"));
    if (NULL == pSt_File)
    {
        delete[]ptszJsonFile;
        ptszJsonFile = NULL;
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_OPENFILE;
        return FALSE;
    }
    while (TRUE)
    {
        TCHAR tszJsonMsg[2048];
        memset(tszJsonMsg, '\0', sizeof(tszJsonMsg));
        int nRet = fread(tszJsonMsg, sizeof(TCHAR), 2048, pSt_File);
        if (nRet <= 0)
        {
            break;
        }
        memcpy(ptszJsonFile + nCount, tszJsonMsg, nRet);
        nCount += nRet;
    }
    fclose(pSt_File);

    __int64x nLocalVersion = 0;
    __int64x nNewVersion = st_JsonRoot["MainVersion"].asInt64();
    if (NULL != pInt_NewVer)
    {
        *pInt_NewVer = nNewVersion;
    }
    list<FILEPARSER_VERSIONINFO> stl_ListUPDataVer;
    list<FILEPARSER_VERSIONINFO> stl_ListCurrentVer;
    if (!FileParser_Match_InitFile(ptszJsonFile, nCount,&nLocalVersion,&stl_ListCurrentVer))
    {
        delete[]ptszJsonFile;
        ptszJsonFile = NULL;
        return FALSE;
    }
    if (NULL != pInt_LocalVer)
    {
        *pInt_LocalVer = nLocalVersion;
    }
    //判断版本是否有新的
    if (nNewVersion <= nLocalVersion)
    {
        delete[]ptszJsonFile;
        ptszJsonFile = NULL;
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_NOTNEWVER;
        return FALSE;
    }

    st_JsonArray = st_JsonRoot["UPList"];
    for (unsigned int i = 0;i < st_JsonArray.size();i++)
    {
        FILEPARSER_VERSIONINFO st_VersionInfo;
        memset(&st_VersionInfo, '\0', sizeof(FILEPARSER_VERSIONINFO));
        //开始读取文件列表内容
        st_VersionInfo.bIsRun = st_JsonArray[i]["ModuleRun"].asInt();
        st_VersionInfo.nModuleVersion = st_JsonArray[i]["ModuleVersion"].asInt64();
        _tcscpy(st_VersionInfo.tszModuleCode, st_JsonArray[i]["ModuleCode"].asCString());
        if (!st_JsonArray[i]["ModulePath"].isNull())
        {
            _tcscpy(st_VersionInfo.tszModulePath, st_JsonArray[i]["ModulePath"].asCString());
        }
        _tcscpy(st_VersionInfo.tszModuleName, st_JsonArray[i]["ModuleName"].asCString());
        _tcscpy(st_VersionInfo.tszModuleDownload, st_JsonArray[i]["ModuleDownload"].asCString());
        //版本比较
        if (FileParser_Match_FileVersion(&st_VersionInfo,&stl_ListCurrentVer))
        {
            stl_ListUPDataVer.push_back(st_VersionInfo);
        }
    }
    delete[]ptszJsonFile;
    ptszJsonFile = NULL;
    //判断是否有新的文件存在
    if (stl_ListUPDataVer.empty())
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_NONEWVER;
        return FALSE;
    }
    CBaseLib_OperatorMemory<FILEPARSER_VERSIONINFO> m_MemoryVersion;
    m_MemoryVersion.BaseLib_OperatorMemory_Malloc(pppSt_ListUPDataVer, stl_ListUPDataVer.size(), sizeof(FILEPARSER_VERSIONINFO));

    list<FILEPARSER_VERSIONINFO>::const_iterator stl_ListIterator = stl_ListUPDataVer.begin();
    for (int i = 0; stl_ListIterator != stl_ListUPDataVer.end(); stl_ListIterator++, i++)
    {
        *(*pppSt_ListUPDataVer)[i] = *stl_ListIterator;
    }
    *pInt_ListCount = stl_ListUPDataVer.size();
    stl_ListUPDataVer.clear();
    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//                            保护函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：FileParser_Match_Init
函数功能：初始化文件匹配器
 参数.一：lpszMsgBuffer
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：文件版本缓冲区
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入缓冲区大小
 参数.三：pInt_LocalVersion
  In/Out：Out
  类型：整数型指针
  可空：N
  意思：导出本地主版本号
 参数.四：pStl_ListCurrentVer
  In/Out：Out
  类型：LIST容器指针
  可空：N
  意思：导出获取到的本地文件列表信息
返回值
  类型：逻辑型
  意思：是否初始化成功
备注：
*********************************************************************/
BOOL CFileParser_Match::FileParser_Match_InitFile(LPCTSTR lpszMsgBuffer, int nMsgLen, __int64x* pInt_LocalVersion, list<FILEPARSER_VERSIONINFO>* pStl_ListCurrentVer)
{
    FileParser_IsErrorOccur = FALSE;

    if (NULL == lpszMsgBuffer || (NULL == pInt_LocalVersion))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_INIT_PARAMENT;
        return FALSE;
    }
    Json::Value st_JsonRoot;
    Json::Value st_JsonArray;
    Json::CharReaderBuilder st_JsonBuild;
    Json::CharReader* pSt_JsonReader(st_JsonBuild.newCharReader());

    JSONCPP_STRING st_JsonError;

    if (!pSt_JsonReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRoot, &st_JsonError))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_INIT_JSON;
        return FALSE;
    }
    delete pSt_JsonReader;
    pSt_JsonReader = NULL;

    *pInt_LocalVersion = st_JsonRoot["MainVersion"].asInt64();
    st_JsonArray = st_JsonRoot["FileList"];
    for (unsigned int i = 0;i < st_JsonArray.size();i++)
    {
        FILEPARSER_VERSIONINFO st_VersionInfo;
        memset(&st_VersionInfo, '\0', sizeof(FILEPARSER_VERSIONINFO));

        st_VersionInfo.st_LocalVersion.nModuleVersion = st_JsonArray[i]["ModuleVersion"].asInt64();
        _tcscpy(st_VersionInfo.st_LocalVersion.tszMoudelCode, st_JsonArray[i]["ModuleCode"].asCString());
        _tcscpy(st_VersionInfo.st_LocalVersion.tszMoudelName, st_JsonArray[i]["ModuleName"].asCString());
        _tcscpy(st_VersionInfo.st_LocalVersion.tszMoudelPath, st_JsonArray[i]["ModulePath"].asCString());

        pStl_ListCurrentVer->push_back(st_VersionInfo);
    }
    return TRUE;
}
/********************************************************************
函数名称：FileParser_Match_FileVersion
函数功能：文件版本匹配
 参数.一：pSt_VersionInfo
  In/Out：In
  类型：数据结构指针
  可空：N
  意思：新版本文件属性
 参数.二：pStl_ListCurrentVer
  In/Out：In
  类型：LIST容器指针
  可空：N
  意思：要匹配的本地版本列表
返回值
  类型：逻辑型
  意思：反正真表示有新版本，否则返回假
备注：
*********************************************************************/
BOOL CFileParser_Match::FileParser_Match_FileVersion(FILEPARSER_VERSIONINFO *pSt_VersionInfo, list<FILEPARSER_VERSIONINFO> *pStl_ListCurrentVer)
{
    FileParser_IsErrorOccur = FALSE;

    list<FILEPARSER_VERSIONINFO>::const_iterator stl_ListIterator = pStl_ListCurrentVer->begin();
    for (; stl_ListIterator != pStl_ListCurrentVer->end(); stl_ListIterator++)
    {
        if (0 == _tcsncmp(stl_ListIterator->st_LocalVersion.tszMoudelCode,pSt_VersionInfo->tszModuleCode,_tcslen(pSt_VersionInfo->tszModuleCode)))
        {
            if (pSt_VersionInfo->nModuleVersion > stl_ListIterator->st_LocalVersion.nModuleVersion)
            {
                memcpy(&pSt_VersionInfo->st_LocalVersion,&stl_ListIterator->st_LocalVersion,sizeof(pSt_VersionInfo->st_LocalVersion));
                break;
            }
            else
            {
                return FALSE;       //无需错误码 表明这个版本不是新版本
            }
        }
    }
    //没有找到的文件表示要新添加的文件
    return TRUE;
}
