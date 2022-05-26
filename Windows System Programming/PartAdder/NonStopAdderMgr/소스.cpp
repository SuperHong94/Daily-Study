#include <stdio.h>
#include <tchar.h>
#include <Windows.h>


int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	si1.cb = sizeof(si1);
	si2.cb = sizeof(si2);

	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = L"PartAdder.exe 6 10";

	int sum = 0;
	PROCESS_INFORMATION p1;
	PROCESS_INFORMATION p2;
	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &p1);
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &p2);

}