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
BOOL CFileParser_Match::FileParser_Match_Start(FILEPARSER_VERSIONINFO*** pppSt_ListRemote, int nRemoteCount, FILEPARSER_VERSIONINFO*** pppSt_ListLocal, int nLocalCount, list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate)
{
    FileParser_IsErrorOccur = FALSE;

    if ((NULL == pppSt_ListRemote) || (NULL == pppSt_ListLocal) || (NULL == pStl_ListUPDate))
    {
        FileParser_IsErrorOccur = TRUE;
        FileParser_dwErrorCode = ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_PARAMENT;
        return FALSE;
    }

    for (int i = 0;i < nRemoteCount;i++)
    {
        //版本比较
		for (int j = 0; j < nLocalCount; j++)
		{
			if (0 == _tcsncmp((*pppSt_ListLocal)[j]->st_LocalVersion.tszMoudelCode, (*pppSt_ListRemote)[i]->tszModuleCode, _tcslen((*pppSt_ListRemote)[i]->tszModuleCode)))
			{
				if ((*pppSt_ListRemote)[i]->nModuleVersion > (*pppSt_ListLocal)[j]->st_LocalVersion.nModuleVersion)
				{
					(*pppSt_ListRemote)[i]->st_LocalVersion = (*pppSt_ListLocal)[j]->st_LocalVersion;
					pStl_ListUPDate->push_back(*(*pppSt_ListRemote)[i]);
					break;
				}
				else
				{
					break;
				}
			}
		}
    }
    return TRUE;
}