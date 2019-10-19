#include <iostream>
#include <random>
#include <vector>
#include "tree.h"
int main()
{
	NIL = new Node;
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	std::vector<int> v;
	std::cout << "만들 갯수 입력:"; int menuNum = 0; std::cin >> menuNum;
	for (int i = 0; i < menuNum; i++) v.push_back(uid(dre));
	for (int i = 0; i < v.size(); i++) std::cout << v[i] << '\t';
	for (int i = 0; i < v.size(); i++)
	{
		Insert(ROOT, v[i]);
		PrintTree(ROOT);
	}
}