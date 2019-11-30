#include "tree.h"


std::default_random_engine dre;
std::uniform_int_distribution<int> uid(0, 100);


int main()
{
	int arr[SIZE];
	for (int& d : arr) d = uid(dre);
	for (int d : arr)std::cout << d << ' ';
	std::cout << std::endl;

	Node* ROOT = nullptr;
	for (int i = 0; i < SIZE; i++)
		ROOT = Insert(ROOT, arr[i]);

	PrintAll(ROOT);
}