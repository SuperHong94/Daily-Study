#include <iostream>
#include <random>
#include <vector>
#include "tree.h"
int main()
{
	NIL = new Node;
	NIL->left = nullptr;
	NIL->right = nullptr;
	
	
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	std::vector<int> v;
	std::cout << "만들 갯수 입력:"; int menuNum = 0; std::cin >> menuNum;
	for (int i = 0; i < menuNum; i++)
		v.push_back(uid(dre));
	//----------------------
	//루트만들기
	ROOT = new Node;
	ROOT->data = v[0];
	ROOT->left = ROOT->right = nullptr;
	ROOT->parents = nullptr;
	//------------------
	for (int i = 0; i < v.size(); i++) std::cout << v[i] << '\t';
	printf("'\n");
	for (int i = 1; i < v.size(); i++)
	{
		std::cout << "---------------\n";
		Insert(ROOT, v[i]);
		PrintTree(ROOT);
	}
}
