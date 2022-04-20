#include <stdio.h>
#include <tchar.h>	
#include <Windows.h>

int main()
{
	DWORD n = 0;
	while (n < 100)
	{
		for (int i = 0; i < 10000; i++)
			for (int j = 0; j < 10000; ++j);

		fprintf(stdout, "호출된프로세스 %d\n", n);
		n++;
	}

}