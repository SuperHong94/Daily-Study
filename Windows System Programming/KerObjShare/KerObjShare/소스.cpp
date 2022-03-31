#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;
	si.cb = sizeof(pi);

	TCHAR command[] = _T("Operation2.exe");
	CreateProcess(NULL, command, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	DWORD timing = 0;
	while (1)
	{
		for (int i = 0; i < 10000; i++)
			for (int j = 0; j < 10000; j++);//Busy Waiting

		_fputts(_T("Parent \n"), stdout);

		timing += 1;
		if (timing == 2)
			SetPriorityClass(pi.hProcess, NORMAL_PRIORITY_CLASS);
	}
	return 0;
}