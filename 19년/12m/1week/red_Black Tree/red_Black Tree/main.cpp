#include "tree.h"


std::default_random_engine dre;
std::uniform_int_distribution<int> uid(0, 100);
Node* ROOT = nullptr;

int main()
{
	int arr[SIZE];
	for (int& d : arr) d = uid(dre);
	for (int d : arr)std::cout << d << ' ';
	std::cout << std::endl;


	Node* node = nullptr;
	ROOT = Insert(ROOT,arr[0]);
	ROOT->color = BLACK;

	for (int i = 1; i < SIZE; i++) {
		std::cout << "----------------\n";
		node = Insert(ROOT, arr[i]);
		PrintAll(ROOT);
	}

	
}