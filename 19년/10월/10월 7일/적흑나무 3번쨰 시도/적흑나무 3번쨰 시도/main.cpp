#include <iostream>
#include <random>
#include <vector>
#define BLACK 0
#define RED 1

struct Node
{
	int data;
	int color = BLACK;
	Node* left;
	Node* right;
	Node* parent = NULL;
};

Node* ROOT;
Node* NIL;
void makeNode(Node*&, int);
void PrintNode(Node*);
void Insert(Node*&, int);
void PrintColor(int);
void LeftTurn(Node*);
void RightTurn(Node* node);
void evaluate(Node* node);
int main()
{
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	std::vector<int> v;

	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = NIL->right = NULL;
	int manunum = 0;

	std::cout << "얼마나 만들거야?:"; std::cin >> manunum;
	for (int i = 0; i < manunum; i++)v.push_back(uid(dre));
	for (int i = 0; i < v.size(); i++)std::cout << v[i] << '\n';
	ROOT = new Node;
	ROOT->left = ROOT->right = NIL;
	std::cout << ROOT->left << '\n';
	ROOT->data = v[0];
	ROOT->color = BLACK;
	for (int i = 1; i < v.size(); i++) {
		Insert(ROOT, v[i]);
		std::cout << "---------\n";
		PrintNode(ROOT);
		std::cout << "---------\n";
	}
	std::cout << ROOT << ' ' << NIL << '\n';
	std::cout << ROOT->left << '\n';
}
void makeNode(Node*& node, int data)
{
	Node* newNode = new Node;
	node = newNode;
	node->left = NIL; node->right = NIL;
	node->data = data;
	node->color = RED;
}
void Insert(Node*& node, int data)
{
	if (node == NIL) {
		makeNode(node, data);
	}
	else {
		if (node->data >= data) {

			Insert(node->left, data);
			node->left->parent = node;
			evaluate(node->left);
		}
		else {

			Insert(node->right, data);
			node->right->parent = node;
			evaluate(node->right);
		}
	}
}
void PrintNode(Node* root)
{
	if (root == NIL || root == NULL)
		return;
	else {
		std::cout << "자기주소" << root << "부모주소" << root->parent << " 값" << root->data; PrintColor(root->color); std::cout << '\n';
		PrintNode(root->left);
		PrintNode(root->right);
	}
}
void PrintColor(int color)
{
	if (color == RED)
		std::cout << " 색깔:" << "빨강";
	else
		std::cout << " 색깔:" << "검정";
}
void LeftTurn(Node* node)
{
	std::cout << node << "기준으로 왼쪽 회전\n";
	Node*Right = node->right;
	if (Right->left != NIL) {
		Right->left->parent = node;
		node->right = Right->left;
	}
	else
		node->right = NIL;
	if (node != ROOT) {
		if (node == node->parent->left) {
			node->parent->left = Right;
		}
		else {
			node->parent->right = Right;
		}
	}
	else
		ROOT = Right;
	Right->parent = node->parent;
	node->parent = Right;
	Right->left = node;
}
void RightTurn(Node* node)
{

	std::cout << node << "기준으로 오른쪽 회전\n";
	Node*Left = node->left;
	if (Left->right != NIL) {
		Left->right->parent = node;
		node->left = Left->right;
	}
	else
		node->left = NIL;
	if (node != ROOT) {
		if (node->parent != NULL) {
			if (node == node->parent->right) {
				node->parent->right = Left;
			}
			else {
				node->parent->left = Left;
			}
		}

	}
	else {
		ROOT = Left;
		std::cout << "루트 바꿈";
	}
	Left->parent = node->parent;
	node->parent = Left;

	Left->right = node;
}

void evaluate(Node* node)
{
	Node*eNode = node;

	if (node->parent == NULL)
		return;
	if (node->parent->parent == NULL)
		return;
	if (node->parent->color == BLACK)
		return;
	else {
		if (node->parent->parent->right->color == BLACK) {  //오른쪽이 블랙
			if (node == node->parent->right) {
				LeftTurn(node->parent);
				node->parent;
				RightTurn(node->parent);
				node->parent;
				node->color = BLACK;
				node->right->color = RED;
			}
			else {
				RightTurn(node->parent);
				node->color = BLACK;
				node->right->color = RED;
			}
			return;
		}
		else if (node->parent->parent->right->color == RED) {

			node->parent->color = BLACK;
			node->parent->parent->right->color = BLACK;
			node->parent->parent->color = RED;
			if (node->parent->parent == ROOT) {
				node->parent->parent->color = BLACK;
				return;
			}
			evaluate(node->parent->parent);
		}



		if (node->parent->parent->left->color == BLACK) {  //왼쪽이 블랙
			if (node == node->parent->left) {
				RightTurn(node->parent);
				LeftTurn(node->parent);
				node->color = BLACK;
				node->left->color = RED;
			}
			else {
				LeftTurn(node->parent);
				node->color = BLACK;
				node->left->color = RED;
			}
			return;
		}
		else if (node->parent->parent->left->color == RED) {
			node->parent->color = BLACK;
			node->parent->parent->left->color = BLACK;
			node->parent->parent->color = RED;
			if (node->parent->parent == ROOT) {
				node->parent->parent->color = BLACK;
				return;
			}
			evaluate(node->parent->parent);
		}
	}
}