//A���μ��� 
#include <stdio.h>
#include <tchar.h>	
#include <Windows.h>

int main()
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);

	TCHAR command[] = _T("KernerlObjProb2.exe");
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	CloseHandle(pi.hProcess);
	printf("closehandle ȣ��Ϸ�!\n");



}