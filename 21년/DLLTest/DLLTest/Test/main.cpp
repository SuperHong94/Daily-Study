#include <iostream>
#include <Windows.h>



int (*FUNDLL)(int a, int b);
int Add(int a, int b)
{
	return a + b;
}

int main()
{
	HMODULE hdll = LoadLibraryA("DLLTest.dll");

	//FUNDLL s = (FUNDLL)GetProcAddress(hdll, "ADD");
	FUNDLL = (int(*)(int ,int ))GetProcAddress(hdll, "ADD");

	int c = FUNDLL(100, 200);

	
	std::cout << c << std::endl;

}