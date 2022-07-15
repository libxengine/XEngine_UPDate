#include "pch.h"
#include "Configure_File.h"
/********************************************************************
//    Created:     2022/07/08  13:45:05
//    File Name:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Configure_File\Configure_File.cpp
//    File Path:   D:\XEngine_UPDate\XEngine_Source\UPData_Configure\Configure_File
//    File Base:   Configure_File
//    File Ext:    cpp
//    Project:     XEngine(网络通信引擎)
//    Author:      qyt
//    Purpose:     文件配置信息操作
//    History:
*********************************************************************/
CConfigure_File::CConfigure_File()
{

}
CConfigure_File::~CConfigure_File()
{

}
//////////////////////////////////////////////////////////////////////////
//                        公用函数
//////////////////////////////////////////////////////////////////////////
/********************************************************************
函数名称：Configure_File_Json
函数功能：文件JSON配置解析
 参数.一：lpszConfigFile
  In/Out：In
  类型：常量字符指针
  可空：N
  意思：输入要解析的文件
 参数.二：pSt_ServerConfig
  In/Out：Out
  类型：数据结构指针
  可空：N
  意思：输出配置信息
返回值
  类型：逻辑型
  意思：是否成功
备注：
*********************************************************************/
BOOL CConfigure_File::Configure_File_Json(LPCTSTR lpszConfigFile, XENGINE_SERVERCONFIG* pSt_ServerConfig)
{
	Config_IsErrorOccur = FALSE;

	if ((NULL == lpszConfigFile) || (NULL == pSt_ServerConfig))
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_UPDATE_MODULE_CONFIG_PARAMENT;
		return FALSE;
	}
	Json::Value st_JsonRoot;
	JSONCPP_STRING st_JsonError;
	Json::CharReaderBuilder st_JsonBuilder;
	//读取配置文件所有内容到缓冲区
	FILE* pSt_File = _tfopen(lpszConfigFile, _T("rb"));
	if (NULL == pSt_File)
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_UPDATE_MODULE_CONFIG_OPENFILE;
		return FALSE;
	}
	size_t nCount = 0;
	TCHAR tszMsgBuffer[4096];
	while (1)
	{
		size_t nRet = fread(tszMsgBuffer + nCount, 1, 2048, pSt_File);
		if (nRet <= 0)
		{
			break;
		}
		nCount += nRet;
	}
	fclose(pSt_File);
	//开始解析配置文件
	std::unique_ptr<Json::CharReader> const pSt_JsonReader(st_JsonBuilder.newCharReader());
	if (!pSt_JsonReader->parse(tszMsgBuffer, tszMsgBuffer + nCount, &st_JsonRoot, &st_JsonError))
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_UPDATE_MODULE_CONFIG_PARSE;
		return FALSE;
	}
	_tcscpy(pSt_ServerConfig->tszUPUrl, st_JsonRoot["tszUPUrl"].asCString());
	_tcscpy(pSt_ServerConfig->tszLocalList, st_JsonRoot["tszLocalList"].asCString());
	_tcscpy(pSt_ServerConfig->tszDownPath, st_JsonRoot["tszDownPath"].asCString());
	pSt_ServerConfig->bIsDown = st_JsonRoot["bIsDown"].asBool();
	pSt_ServerConfig->nDlCount = st_JsonRoot["nDlCount"].asInt();
	pSt_ServerConfig->nTimeout = st_JsonRoot["nTimeout"].asInt();
	//日志配置
	if (st_JsonRoot["XLog"].empty() || (4 != st_JsonRoot["XLog"].size()))
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_UPDATE_MODULE_CONFIG_XLOG;
		return FALSE;
	}
	Json::Value st_JsonXLog = st_JsonRoot["XLog"];
	pSt_ServerConfig->st_XLog.nMaxSize = st_JsonXLog["nMaxSize"].asInt();
	pSt_ServerConfig->st_XLog.nMaxCount = st_JsonXLog["nMaxCount"].asInt();
	pSt_ServerConfig->st_XLog.nLogLeave = st_JsonXLog["nLogLeave"].asInt();
	_tcscpy(pSt_ServerConfig->st_XLog.tszLogFile, st_JsonXLog["tszLogFile"].asCString());
	//版本列表
	Json::Value st_JsonXVer = st_JsonRoot["XVer"];
	pSt_ServerConfig->st_XVer.pStl_ListVer = new list<string>;
	if (NULL == pSt_ServerConfig->st_XVer.pStl_ListVer)
	{
		Config_IsErrorOccur = TRUE;
		Config_dwErrorCode = ERROR_UPDATE_MODULE_CONFIG_MALLOC;
		return FALSE;
	}
	for (unsigned int i = 0; i < st_JsonXVer.size(); i++)
	{
		pSt_ServerConfig->st_XVer.pStl_ListVer->push_back(st_JsonXVer[i].asCString());
	}
	return TRUE;
}
