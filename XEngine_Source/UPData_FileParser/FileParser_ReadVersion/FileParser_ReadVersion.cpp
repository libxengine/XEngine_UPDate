#include "pch.h"
#include "FileParser_ReadVersion.h"
/********************************************************************
//	Created:	2014/7/17  16:43
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_ReadVersion\FileParser_ReadVersion.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_ReadVersion
//	File Base:	FileParser_ReadVersion
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	文件版本读取实现
//	History:
*********************************************************************/
CFileParser_ReadVersion::CFileParser_ReadVersion()
{

}
CFileParser_ReadVersion::~CFileParser_ReadVersion()
{

}
//////////////////////////////////////////////////////////////////////////
//                     公有函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：FileParser_ReadVer_GetUPVersion
函数功能：获取新版本信息
 参数.一：lpszWebHost
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：网页主机名称
 参数.二：ptszUPMsg
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出获取到的最新更新信息
 参数.三：pInt_Len
  In/Out：In
  类型：整数型指针
  可空：Y
  意思：输入缓冲区大小,输出获取到的大小
返回值
  类型：逻辑型
  意思：返回真表示有新版本，否则返回假并且重置错误码
备注：APIHelp_HttpRequest_Get错误会存在
*********************************************************************/
BOOL CFileParser_ReadVersion::FileParser_ReadVer_GetUPVersion(LPCTSTR lpszWebHost, TCHAR *ptszUPMsg,int *pInt_Len)
{
    FileParser_IsErrorOccur = FALSE;

    if ((NULL == lpszWebHost) || (NULL == ptszUPMsg) || (NULL == pInt_Len))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_READVER_ISUPVER_PARAMENT;
        return FALSE;
    }
    //获取网页源文件
    int nBLen = 0;
    TCHAR* ptszMsgBody = NULL;
    if (!APIHelp_HttpRequest_Get(lpszWebHost, &ptszMsgBody, &nBLen))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = APIHelp_GetLastError();
        return FALSE;
    }
    *pInt_Len = nBLen;
    memcpy(ptszUPMsg, ptszMsgBody, nBLen);
    BaseLib_OperatorMemory_FreeCStyle((XPPMEM)&ptszMsgBody);
    return TRUE;
}
/********************************************************************
函数名称：FileParser_ReadVer_GetDescription
函数功能：获取更新内容描述
 参数.一：lpszJsonMsg
  In/Out：In
  类型：常量字符指针
  可空：Y
  意思：通过获取到的新版本JSON信息来获取更新内容
 参数.二：nMsgLen
  In/Out：In
  类型：整数型
  可空：N
  意思：输入JSON缓冲区大小
 参数.三：ptszUPDes
  In/Out：Out
  类型：字符指针
  可空：N
  意思：导出获取到的更新描述
 参数.四：pInt_Len
  In/Out：In/Out
  类型：整数型指针
  可空：N
  意思：输入，缓冲区大小，输出获取到的内容缓冲区大小
返回值
  类型：逻辑型
  意思：是否获取成功
备注：错误为ERROR_XENGINE_UPDATA_FILEPARSER_READVER_GETDES_LEN最后一个参数将设置为需要的大小
*********************************************************************/
BOOL CFileParser_ReadVersion::FileParser_ReadVer_GetDescription(LPCTSTR lpszJsonMsg, int nMsgLen, TCHAR* ptszUPDes, int* pInt_Len)
{
    FileParser_IsErrorOccur = FALSE;

    if ((NULL == ptszUPDes) || (NULL == pInt_Len) || (NULL == lpszJsonMsg))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_READVER_GETDES_PARAMENT;
        return FALSE;
    }
    Json::Value st_JsonRoot;
    Json::CharReaderBuilder st_JsonBuild;
    Json::CharReader* pSt_JsonReader(st_JsonBuild.newCharReader());

    JSONCPP_STRING st_JsonError;

    if (!pSt_JsonReader->parse(lpszJsonMsg, lpszJsonMsg + nMsgLen, &st_JsonRoot, &st_JsonError))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_READVER_GETDES_JSON;
        return FALSE;
    }
    delete pSt_JsonReader;
    pSt_JsonReader = NULL;

    int nLen = st_JsonRoot["MainDescription"].asString().length();
    if ((*pInt_Len) < nLen)
    {
        *pInt_Len = nLen;
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_READVER_GETDES_LEN;
        return FALSE;
    }
    _tcscpy(ptszUPDes, st_JsonRoot["MainDescription"].asCString());
    *pInt_Len = nLen;
    return TRUE;
}
