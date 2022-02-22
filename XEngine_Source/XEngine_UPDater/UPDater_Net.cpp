#include "UPDater_Hdr.h"

LPCTSTR lpszDlStatus[] = { "未知", "下载中", "暂停", "停止", "完成", "错误" };
void __stdcall UPDater_Callback_Download(LPCTSTR lpszFileName, double nDownSize, double nFileSize, int nRate, int nAllRate, ENUM_DOWNENGINE_STATUS enDlStatus, LPVOID lParam)
{
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("下载的文件:%s,下载大小:%lf,文件大小:%lf,进度:%d,总进度:%d,状态:%s"), lpszFileName, nDownSize, nFileSize, nRate, nAllRate, lpszDlStatus[enDlStatus]);

	if (100 == nAllRate)
	{
		bIsRun = FALSE;
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("文件下载完成"));
	}
}