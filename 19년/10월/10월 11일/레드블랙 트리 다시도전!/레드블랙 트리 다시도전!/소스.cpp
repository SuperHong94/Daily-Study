#include <iostream>
#include <random>
#include <vector>
#include "RBT.h"
int main()
{
	Node* root=new Node;
	root->left = root->right = nullptr;
	root->color = BLACK;
	root->parent = nullptr;
	std::vector<int> v;
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	std::cout << "숫자입력:"; int Num = 0; std::cin >> Num;
	for (int i = 0; i < Num; i++)v.push_back(uid(dre));
	for (int i = 0; i < v.size(); i++) {

	}
}