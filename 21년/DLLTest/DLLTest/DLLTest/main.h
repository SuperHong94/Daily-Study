#pragma once

#define DLLTEST __declspec(dllexport)




extern "C"
{
	DLLTEST int ADD(int a, int b);

}