#include <iostream>
#include <random>
struct List {
	List* next = nullptr;
	int key;
};

List* MakeList(int key) {
	List* nList = new List;
	nList->key = key;
	return nList;
}
void PrintAll(List* root)
{
	if (root->next == nullptr)
		return;
	std::cout << root->key << '\n';
	std::cout << root->next;
	PrintAll(root->next);
}
int main()
{
	List* root = new List;
	root->key = 100;
	std::vector<int> v;
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	std::cout << "숫자입력:"; int Num = 0; std::cin >> Num;
	for (int i = 0; i < Num; i++)v.push_back(uid(dre));
	for (int i = 1; i < v.size(); i++) {
		if (i == 1) {
			root->next = MakeList(v[i - 1]);
			MakeList(v[i - 1])->next = MakeList(v[i]);
		}
		else
			MakeList(v[i - 1])->next = MakeList(v[i]);
		std::cout << MakeList(v[i - 1])->next << "dddd'\n";
		//if (i == (v.size() - 1))
			//std::cout<<root->next;
	}
	std::cout << root->next->next;
	PrintAll(root);

}