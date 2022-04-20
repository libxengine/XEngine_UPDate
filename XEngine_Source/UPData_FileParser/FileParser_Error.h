#pragma once
/********************************************************************
//	Created:	2014/7/17  15:53
//	File Name: 	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser\FileParser_Error.h
//	File Path:	F:\NetEngine_Windows\NetEngine_SourceCode\NetEngine_UPData\UPData_FileParser
//	File Base:	FileParser_Error
//	File Ext:	h
//  Project:    XyRySoft_NetEngine(网络通信引擎)
//	Author:		qyt 486179@qq.com
//	Purpose:	更新文件分析器导出错误码
//	History:
*********************************************************************/
//////////////////////////////////////////////////////////////////////////
//                      文件版本列表解析错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_UPDATA_FILEPARSER_MATCH_START_PARAMENT 0xA1001000   //参数错误
//////////////////////////////////////////////////////////////////////////
//                      文件版本读取错误
//////////////////////////////////////////////////////////////////////////
#define ERROR_XENGINE_UPDATA_FILEPARSER_READ_GET_PARAMENT 0xA1002000      //参数错误
#define ERROR_XENGINE_UPDATA_FILEPARSER_READ_GET_JSON 0xA1002001          //JSON错误
#define ERROR_XENGINE_UPDATA_FILEPARSER_READ_GET_NOFILE 0xA1002002        //什么都没取到
#define ERROR_XENGINE_UPDATA_FILEPARSER_READ_GET_MALLOC 0xA1002003        //申请内存失败
#define ERROR_XENGINE_UPDATA_FILEPARSER_READ_GET_OPENFILE 0xA1002004      //打开文件失败