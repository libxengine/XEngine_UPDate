#include "UPDater_Hdr.h"

LPCTSTR lpszDlStatus[] = { "δ֪", "������", "��ͣ", "ֹͣ", "���", "����" };
void __stdcall UPDater_Callback_Download(LPCTSTR lpszFileName, double nDownSize, double nFileSize, int nRate, int nAllRate, ENUM_DOWNENGINE_STATUS enDlStatus, LPVOID lParam)
{
	XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("���ص��ļ�:%s,���ش�С:%lf,�ļ���С:%lf,����:%d,�ܽ���:%d,״̬:%s"), lpszFileName, nDownSize, nFileSize, nRate, nAllRate, lpszDlStatus[enDlStatus]);

	if (100 == nAllRate)
	{
		bIsRun = FALSE;
		XLOG_PRINT(xhLog, XENGINE_HELPCOMPONENTS_XLOG_IN_LOGLEVEL_INFO, _T("�ļ��������"));
	}
}