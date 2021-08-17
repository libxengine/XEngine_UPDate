#include "UPDater_Hdr.h"

BOOL UPDater_Parament(int argc, char **argv)
{
	LPCTSTR lpszFile = _T("./XEngine_Config/XEngine_Config.ini");
	if (!Config_Ini_File(lpszFile, &st_ServiceConfig))
	{
		printf("���������ļ�ʧ��,Config_Ini_File:%lX\n", Config_GetLastError());
		return FALSE;
	}

	for (int i = 0;i < argc;i++)
	{
		if ((0 == _tcscmp("-h", argv[i])) || (0 == _tcscmp("-H", argv[i])))
		{
			UPDater_ParamentHelp();
			return FALSE;
		}
		if ((0 == _tcscmp("-v", argv[i])) || (0 == _tcscmp("-V", argv[i])))
		{
			printf("Version��V1.1.0\n");
			return FALSE;
		}
		else if (0 == _tcscmp("-p", argv[i]))
		{
			memset(st_ServiceConfig.tszDownPath, '\0', sizeof(st_ServiceConfig.tszDownPath));
			_tcscpy_s(st_ServiceConfig.tszDownPath, MAX_PATH, argv[i + 1]);
		}
		else if (0 == _tcscmp("-m", argv[i]))
		{
			st_ServiceConfig.bIsMake = TRUE;
			memset(st_ServiceConfig.st_Maker.tszMakePath, '\0', sizeof(st_ServiceConfig.st_Maker.tszMakePath));
			_tcscpy_s(st_ServiceConfig.st_Maker.tszMakePath, MAX_PATH, argv[i + 1]);
		}
		else if (0 == _tcscmp("-l", argv[i]))
		{
			st_ServiceConfig.st_XLog.nLogLeave = _ttoi(argv[i + 1]);
		}
		else if (0 == _tcscmp("-d", argv[i]))
		{
			st_ServiceConfig.bIsDown = _ttoi(argv[i + 1]);
		}
	}

	return TRUE;
}

void UPDater_ParamentHelp()
{
	printf(_T("--------------------------��������������ʼ--------------------------\n"));
	printf(_T("���·����������������� ���� ����ֵ�����������ִ�Сд��\n"));
	printf(_T("-h or -H����������������ʾ��Ϣ\n"));
	printf(_T("-v or -V���鿴ϵͳ�汾\n"));
	printf(_T("-p�����ø����ļ����ص�Ŀ¼,Ĭ��:./UPFile/\n"));
	printf(_T("-m���������ذ汾�����б���Ҫ��������Ҫ��������汾��Ŀ¼,Ŀ¼Ĭ����Ҫ���/����.\n"));
	printf(_T("-l�����ñ�����־��¼��Ϣ����\n"));
	printf(_T("-d���������°汾�Ƿ������ļ�,Ĭ��0������,1λ����\n"));
	printf(_T("--------------------------����������������--------------------------\n"));
}