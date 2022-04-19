#include "pch.h"
#include "HelpModule_Api.h"
/********************************************************************
//	Created:	2014/7/25  17:55
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule\HelpModule_Api\HelpModule_Api.cpp
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_HelpModule\HelpModule_Api
//	File Base:	HelpModule_Api
//	File Ext:	cpp
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	帮助模块API函数实现
//	History:
*********************************************************************/
CHelpModule_Api::CHelpModule_Api()
{

}
CHelpModule_Api::~CHelpModule_Api()
{

}
//////////////////////////////////////////////////////////////////////////
//                           公有函数
//////////////////////////////////////////////////////////////////////////
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
BOOL CHelpModule_Api::HelpModule_Api_Copy(list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate, LPCTSTR lpszDlPath /* = NULL */, BOOL bDelFile /* = TRUE */)
{
    HelpModule_IsErrorOccur = FALSE;

    TCHAR tszDlPath[1024];
    TCHAR tszCpPath[1024];
    if ((NULL == pStl_ListUPDate))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_COPY_PARAMENT;
        return FALSE;
    }
    list<FILEPARSER_VERSIONINFO>::const_iterator stl_ListIterator = pStl_ListUPDate->begin();
    for (; stl_ListIterator != pStl_ListUPDate->end(); stl_ListIterator++)
    {
        memset(tszDlPath, '\0', sizeof(tszDlPath));
        memset(tszCpPath, '\0', sizeof(tszCpPath));
        //获取下载的文件路径和名称 组合成可以拷贝的路径地址
        if (NULL != lpszDlPath)
        {
            _stprintf_s(tszDlPath, _T("%s%s"), lpszDlPath, stl_ListIterator->tszModuleName);
        }
        else
        {
            _tcscpy(tszDlPath, stl_ListIterator->tszModuleName);
        }
        if (0 == stl_ListIterator->st_LocalVersion.nModuleVersion)
        {
            _stprintf_s(tszCpPath, _T("%s%s"), stl_ListIterator->tszModulePath, stl_ListIterator->tszModuleName);
        }
        else
        {
            _stprintf_s(tszCpPath, _T("%s%s"), stl_ListIterator->st_LocalVersion.tszMoudelPath, stl_ListIterator->st_LocalVersion.tszMoudelName);
        }
        if (!SystemApi_File_CreateMutilFolder(stl_ListIterator->st_LocalVersion.tszMoudelPath))
        {
            HelpModule_IsErrorOccur = TRUE;
            HelpModule_dwErrorCode = SystemApi_GetLastError();
            return FALSE;
        }
        if (!SystemApi_File_CopyFile(tszDlPath, tszCpPath, FALSE))
        {
            HelpModule_IsErrorOccur = TRUE;
            HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_COPY_ISFAILED;
            return FALSE;
        }
        if (bDelFile)
        {
			//删除原始下载的文件
			if (0 != _tremove(tszDlPath))
			{
				HelpModule_IsErrorOccur = TRUE;
				HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_COPY_DELFILE;
				return FALSE;
			}
        }
    }
    return TRUE;
}
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
BOOL CHelpModule_Api::HelpModule_Api_SetVersion(LPCTSTR lpszLocalFile, LPCTSTR lpszMsgBuffer, int nMsgLen)
{
    HelpModule_IsErrorOccur = FALSE;

    if ((NULL == lpszLocalFile) || (NULL == lpszMsgBuffer))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_PARAMENT;
        return FALSE;
    }
    //文件JSON
    Json::Value st_JsonRoot;
    Json::Value st_JsonArray;
    //以前的JSON
    Json::Value st_JsonLocalRoot;
    Json::Value st_JsonLocalArray;
    Json::CharReaderBuilder st_JsonLocalBuild;
    Json::CharReader* pSt_JsonLocalReader(st_JsonLocalBuild.newCharReader());
    //新的JSON
    Json::Value st_JsonRemoteRoot;
    Json::Value st_JsonRemoteArray;
    Json::CharReaderBuilder st_JsonRemoteBuild;
    Json::CharReader* pSt_JsonRemoteReader(st_JsonRemoteBuild.newCharReader());

    JSONCPP_STRING st_JsonError;

    if (!pSt_JsonRemoteReader->parse(lpszMsgBuffer, lpszMsgBuffer + nMsgLen, &st_JsonRemoteRoot, &st_JsonError))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_PARSENEWJSON;
        return FALSE;
    }
    delete pSt_JsonRemoteReader;
    pSt_JsonRemoteReader = NULL;

    int nCount = 0;
    TCHAR* ptszJsonFile = new TCHAR[1024 * 1024 * 10];
    if (NULL == ptszJsonFile)
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_MALLOC;
        return FALSE;
    }
    memset(ptszJsonFile, '\0', 1024 * 1024 * 10);
    FILE* pSt_File = _tfopen(lpszLocalFile, _T("rb"));
    if (NULL == pSt_File)
    {
        delete[]ptszJsonFile;
        ptszJsonFile = NULL;
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_OPENFILE;
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

    if (!pSt_JsonLocalReader->parse(ptszJsonFile, ptszJsonFile + nCount, &st_JsonLocalRoot, &st_JsonError))
    {
        delete[]ptszJsonFile;
        ptszJsonFile = NULL;
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_PARSELOCALJSON;
        return FALSE;
    }
    delete pSt_JsonLocalReader;
    delete[]ptszJsonFile;
    ptszJsonFile = NULL;
    pSt_JsonLocalReader = NULL;

    st_JsonLocalArray = st_JsonLocalRoot["FileList"];
    for (unsigned int i = 0; i < st_JsonLocalArray.size(); i++)
    {
        BOOL bIsFound = FALSE;
        Json::Value st_JsonRemoteArray = st_JsonRemoteRoot["UPList"];
        for (unsigned int j = 0; j < st_JsonRemoteArray.size(); j++)
        {
            if (0 == _tcscmp(st_JsonLocalArray[i]["ModuleCode"].asCString(), st_JsonRemoteArray[j]["ModuleCode"].asCString()))
            {
                Json::Value st_JsonObject;
                st_JsonObject["ModuleVersion"] = st_JsonRemoteArray[j]["ModuleVersion"].asUInt64();
                st_JsonObject["ModuleCode"] = st_JsonLocalArray[i]["ModuleCode"].asCString();
                st_JsonObject["ModuleName"] = st_JsonLocalArray[i]["ModuleName"].asCString();
                st_JsonObject["ModulePath"] = st_JsonLocalArray[i]["ModulePath"].asCString();
                st_JsonArray.append(st_JsonObject);
                bIsFound = TRUE;
                break;
            }
        }
        if (!bIsFound)
        {
            //没有找到更新的文件
            BOOL bIsDelFound = FALSE;
            Json::Value st_JsonDelArray;
            st_JsonDelArray = st_JsonRemoteRoot["DelList"];
            //查找是否有删除的文件内容
            for (unsigned int k = 0; k < st_JsonDelArray.size(); k++)
            {
                if (0 == _tcscmp(st_JsonLocalArray[i]["ModuleName"].asCString(), st_JsonDelArray[k]["ModuleName"].asCString()))
                {
                    bIsDelFound = TRUE;
                    break;
                }
            }
            //如果没有删除的,那么这个JSON需要加到集合里面,如果有,那么这个JSON就不需要了
            if (!bIsDelFound)
            {
                Json::Value st_JsonObject;
                st_JsonObject["ModuleVersion"] = st_JsonLocalArray[i]["ModuleVersion"].asUInt64();
                st_JsonObject["ModuleCode"] = st_JsonLocalArray[i]["ModuleCode"].asCString();
                st_JsonObject["ModuleName"] = st_JsonLocalArray[i]["ModuleName"].asCString();
                st_JsonObject["ModulePath"] = st_JsonLocalArray[i]["ModulePath"].asCString();
                st_JsonArray.append(st_JsonObject);
            }
        }
    }
    //添加新增加的JSON
    st_JsonRemoteArray = st_JsonRemoteRoot["UPList"];
    for (unsigned int i = 0; i < st_JsonRemoteArray.size(); i++)
    {
        BOOL bIsFound = FALSE;
        Json::Value st_JsonLocalArray = st_JsonLocalRoot["FileList"];
        //查找远程元素是否在本地存在
        for (unsigned int j = 0; j < st_JsonLocalArray.size(); j++)
        {
            if (0 == _tcscmp(st_JsonRemoteArray[i]["ModuleCode"].asCString(), st_JsonLocalArray[j]["ModuleCode"].asCString()))
            {
                bIsFound = TRUE;
                break;
            }
        }
        //如果不存在,就添加
        if (!bIsFound)
        {
            Json::Value st_JsonObject;
            st_JsonObject["ModuleVersion"] = st_JsonRemoteArray[i]["ModuleVersion"].asInt64();
            st_JsonObject["ModuleCode"] = st_JsonRemoteArray[i]["ModuleCode"].asCString();
            st_JsonObject["ModuleName"] = st_JsonRemoteArray[i]["ModuleName"].asCString();
            st_JsonObject["ModulePath"] = st_JsonRemoteArray[i]["ModulePath"].asCString();
            st_JsonArray.append(st_JsonObject);
        }
    }
    st_JsonRoot["MainVersion"] = st_JsonRemoteRoot["MainVersion"].asInt64();
    st_JsonRoot["FileList"] = st_JsonArray;

    if (0 != _tremove(lpszLocalFile))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_DELETELOCALJSON;
        return FALSE;
    }
    if (!SystemApi_File_SaveBuffToFile(NULL, lpszLocalFile, st_JsonRoot.toStyledString().c_str(), st_JsonRoot.toStyledString().length()))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_SETVER_WRITENEWJSON;
        return FALSE;
    }

    return TRUE;
}
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
BOOL CHelpModule_Api::HelpModule_Api_RunExec(list<FILEPARSER_VERSIONINFO>* pStl_ListUPDate)
{
    HelpModule_IsErrorOccur = FALSE;

    if ((NULL == pStl_ListUPDate))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_RUN_PARAMENT;
        return FALSE;
    }
    list<FILEPARSER_VERSIONINFO>::const_iterator stl_ListIterator = pStl_ListUPDate->begin();
    for (; stl_ListIterator != pStl_ListUPDate->end(); stl_ListIterator++)
    {
        //判断要执行的文件
        if (stl_ListIterator->bIsRun)
        {
            DWORD dwProcessID = 0;
            TCHAR tszPath[1024];
            memset(tszPath, '\0', sizeof(tszPath));
            //判断目录时候需要改变
            _stprintf_s(tszPath, _T("%s%s"), stl_ListIterator->st_LocalVersion.tszMoudelPath, stl_ListIterator->st_LocalVersion.tszMoudelName);
            if (!SystemApi_Process_CreateProcess(&dwProcessID, tszPath))
            {
                HelpModule_IsErrorOccur = TRUE;
                HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_UPDATADL_DLPARSER_RUN_ISFAILED;
                return FALSE;
            }
        }
    }
    return TRUE;
}
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
BOOL CHelpModule_Api::HelpModule_Api_Clear(LPCTSTR lpszRemoteJson, int nMsgLen)
{
    HelpModule_IsErrorOccur = FALSE;

    if (NULL == lpszRemoteJson)
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_HELPMODULE_API_CLEAR_PARAMENT;
        return FALSE;
    }
    Json::Value st_JsonRoot;
    Json::Value st_JsonArray;
    Json::CharReaderBuilder st_JsonBuild;
    Json::CharReader* pSt_JsonReader(st_JsonBuild.newCharReader());

    JSONCPP_STRING st_JsonError;

    if (!pSt_JsonReader->parse(lpszRemoteJson, lpszRemoteJson + nMsgLen, &st_JsonRoot, &st_JsonError))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_HELPMODULE_API_CLEAR_PARSE;
        return FALSE;
    }
    delete pSt_JsonReader;
    pSt_JsonReader = NULL;

    st_JsonArray = st_JsonRoot["DelList"];
    for (unsigned int i = 0; i < st_JsonArray.size(); i++)
    {
        if (0 != _tremove(st_JsonArray[i].asCString()))
        {
            HelpModule_IsErrorOccur = TRUE;
            HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_HELPMODULE_API_CLEAR_DELFILE;
            return FALSE;
        }
    }
    return TRUE;
}
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
BOOL CHelpModule_Api::HelpModule_Api_BuildVer(LPCTSTR lpszPath,LPCTSTR lpszLocalFile, __int64x nFileVer /* = 0 */,BOOL bSubDir /* = TRUE */, LPCTSTR lpszUPFile /* = NULL */, LPCTSTR lpszDlUrl /* = NULL */,LPCTSTR lpszCfgPath /* = NULL*/)
{
    HelpModule_IsErrorOccur = FALSE;

    if ((NULL == lpszPath) || (NULL == lpszLocalFile))
    {
        HelpModule_IsErrorOccur = TRUE;
        HelpModule_dwErrorCode = ERROR_XENGINE_UPDATA_HELPMODULE_API_BUILDVER_PARAMENT;
        return FALSE;
    }
    int nListCount;
    CHAR** ppszListDir;
    list<HELPMODULE_FILELIST> stl_ListFile;
    //枚举文件
    if (!SystemApi_File_EnumFile(lpszPath, &ppszListDir, &nListCount, NULL, NULL, bSubDir, 1))
    {
        HelpModule_IsErrorOccur = FALSE;
        HelpModule_dwErrorCode = SystemApi_GetLastError();
        return FALSE;
    }
    for (int i = 0; i < nListCount; i++)
    {
		HELPMODULE_FILELIST st_FileList;
		memset(&st_FileList, '\0', sizeof(HELPMODULE_FILELIST));

		if (!BaseLib_OperatorString_GetFileAndPath(ppszListDir[i], st_FileList.tszFilePath, st_FileList.tszFileName))
		{
			HelpModule_IsErrorOccur = TRUE;
			HelpModule_dwErrorCode = BaseLib_GetLastError();
			return FALSE;
		}
        stl_ListFile.push_back(st_FileList);
    }
    BaseLib_OperatorMemory_Free((XPPPMEM)&ppszListDir, nListCount);

    Json::Value st_JsonLocalRoot;
    Json::Value st_JsonLocalArray;
    Json::Value st_JsonLocalObject;

    Json::Value st_JsonRemoteRoot;
    Json::Value st_JsonRemoteArray;
    Json::Value st_JsonRemoteObject;
    Json::Value st_JsonRemoteOPtion;
    Json::StreamWriterBuilder st_JsonBuilder;
    //判断是否是自定义版本
    __int64x m_nFileVer = 0;
    if (0 == nFileVer)
    {
        TCHAR tszTimer[64];
        XENGINE_LIBTIMER st_Timer;

        memset(tszTimer,'\0',sizeof(tszTimer));
        memset(&st_Timer,'\0',sizeof(XENGINE_LIBTIMER));

        if (!BaseLib_OperatorTime_GetSysTime(&st_Timer))
        {
            HelpModule_IsErrorOccur = FALSE;
            HelpModule_dwErrorCode = BaseLib_GetLastError();
            return FALSE;
        }
        _stprintf_s(tszTimer, _T("%04d%02d%02d%02d%02d%02d"), st_Timer.wYear, st_Timer.wMonth, st_Timer.wDay, st_Timer.wHour, st_Timer.wMinute, st_Timer.wSecond);
        m_nFileVer = _ttoi64(tszTimer);
    }
    else
    {
        m_nFileVer = nFileVer;
    }
    st_JsonLocalRoot["MainVersion"] = (Json::Int64)m_nFileVer;
    if (NULL != lpszUPFile)
    {
        st_JsonRemoteOPtion["st_JsonRemoteOPtion"] = 0;

        st_JsonRemoteRoot["MainVersion"] = (Json::Int64)m_nFileVer;
        st_JsonRemoteRoot["MainDescription"] = _T("File UPData Des!");
        st_JsonRemoteRoot["FileVerOPtion"] = st_JsonRemoteOPtion;
    }
    //开始构架JSON文件列表
    list<HELPMODULE_FILELIST>::const_iterator stl_ListIterator = stl_ListFile.begin();
    for (unsigned int i = 1; stl_ListIterator != stl_ListFile.end(); stl_ListIterator++, i++)
    {
        TCHAR tszFileCode[64];
        memset(tszFileCode, '\0', sizeof(tszFileCode));

        _stprintf_s(tszFileCode, _T("XYRYUPVERCODE%d"), i);

        st_JsonLocalObject["ModuleVersion"] = (Json::Int64)m_nFileVer;
        st_JsonLocalObject["ModuleCode"] = tszFileCode;
        st_JsonLocalObject["ModuleName"] = stl_ListIterator->tszFileName;
        if (NULL == lpszCfgPath)
        {
            st_JsonLocalObject["ModulePath"] = stl_ListIterator->tszFilePath;
        }
        else
        {
            st_JsonLocalObject["ModulePath"] = lpszCfgPath;
        }
        if (NULL != lpszUPFile)
        {
            TCHAR tszDlPath[1024];
            TCHAR tszDelPath[MAX_PATH];

            memset(tszDlPath,'\0',sizeof(tszDlPath));
            memset(tszDelPath,'\0',MAX_PATH);

            _tcscpy(tszDelPath,stl_ListIterator->tszFilePath);
            //删除指定字符串
            if (!BaseLib_OperatorString_DelSub(tszDelPath, lpszPath))
            {
                HelpModule_IsErrorOccur = FALSE;
                HelpModule_dwErrorCode = BaseLib_GetLastError();
                return FALSE;
            }
            if (isalpha(lpszPath[0]))
            {
                BaseLib_OperatorString_FixPath(tszDelPath, 2);
            }
            if (lpszPath[_tcslen(lpszPath)] != '\\' && lpszPath[_tcslen(lpszPath)] != '/')
            {
                //没有结尾，需要修正
                _stprintf_s(tszDlPath,_T("%s%s%s"), lpszDlUrl, tszDelPath + 1,stl_ListIterator->tszFileName);
            }
            else
            {
                _stprintf_s(tszDlPath,_T("%s%s%s"), lpszDlUrl, tszDelPath,stl_ListIterator->tszFileName);
            }
            st_JsonRemoteObject["ModuleRun"] = 0;
            st_JsonRemoteObject["ModuleVersion"] = (Json::Int64)m_nFileVer;
            st_JsonRemoteObject["ModuleCode"] = tszFileCode;
            st_JsonRemoteObject["ModuleName"] = stl_ListIterator->tszFileName;
            st_JsonRemoteObject["ModuleDownload"] = tszDlPath;
            st_JsonRemoteArray.append(st_JsonRemoteObject);
        }
        st_JsonLocalArray.append(st_JsonLocalObject);
    }
    st_JsonLocalRoot["FileList"] = st_JsonLocalArray;

    if (NULL != lpszUPFile)
    {
        Json::Value st_JsonRemoteDel;

        st_JsonRemoteRoot["UPList"] = st_JsonRemoteArray;
        st_JsonRemoteRoot["DelList"] = st_JsonRemoteDel;
    }
    st_JsonBuilder["emitUTF8"] = true;
    //写到JSON文件
    if (!SystemApi_File_SaveBuffToFile(NULL, lpszLocalFile, Json::writeString(st_JsonBuilder, st_JsonLocalRoot).c_str(), Json::writeString(st_JsonBuilder, st_JsonLocalRoot).length()))
    {
        HelpModule_IsErrorOccur = FALSE;
        HelpModule_dwErrorCode = SystemApi_GetLastError();
        return FALSE;
    }
    if (NULL != lpszUPFile)
    {
        if (!SystemApi_File_SaveBuffToFile(NULL, lpszUPFile, Json::writeString(st_JsonBuilder, st_JsonRemoteRoot).c_str(), Json::writeString(st_JsonBuilder, st_JsonRemoteRoot).length()))
        {
            HelpModule_IsErrorOccur = FALSE;
            HelpModule_dwErrorCode = SystemApi_GetLastError();
            return FALSE;
        }
    }
    return TRUE;
}
