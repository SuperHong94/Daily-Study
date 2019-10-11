#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#define BLACK 0
#define RED 1



struct Node
{
	Node* parent = NULL;
	Node* left = NULL;
	Node* right = NULL;
	int data;
	int color = BLACK;
};
Node* ROOT;
Node* NIL;
void Evaluate(Node* node);
void PrintTree(Node*);
void InsertNode(Node*&	 node, int data);
void PrintColor(int a);
void RotateRighit(Node* node);
void RotateLeft(Node* node);
int main()
{
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);
	Node* root = NULL;
	NIL = new Node;
	int num = 0;
	std::cout << "갯수 입력";
	std::cin >> num;
	std::vector<int> v;
	for (int i = 0; i < num; i++)
		v.push_back(uid(dre));
	for (int i = 0; i < v.size(); i++) std::cout << v[i] << '\n';
	InsertNode(root, v[0]);
	ROOT = root;
	root->color = BLACK;

	for (int i = 1; i < v.size(); i++) {
		InsertNode(ROOT, v[i]);
		
		PrintTree(ROOT);
		std::cout << '\n';
		std::cout << "---------------\n\n";
	}
}

void InsertNode(Node*& node, int data)
{
	if (node == NIL||node==NULL) {
		node = new Node;
		node->left = NIL;
		node->right = NIL;
		node->color = RED;
		node->data = data;
		
		return;
	}
	else
	{
		if (node->data >= data) {
			InsertNode(node->left, data);
			node->left->parent = node;
			Evaluate(node->left);
		}
		else {
			
			InsertNode(node->right, data);
			node->right->parent = node;
			Evaluate(node->right);
		}
	}
}
void PrintColor(int a)
{
	switch (a)
	{
	case BLACK:
		std::cout << " 검정";
		break;
	case RED:
		std::cout << " 빨강";
		break;
	default:
		break;
	}
}
void PrintTree(Node* root)
{
	if (root == NIL) 
		return;
	else {
		std::cout << "자기주소" << root << "부모주소" << root->parent << " 값" << root->data; PrintColor(root->color); std::cout << '\n';
		PrintTree(root->left);
		PrintTree(root->right);
	}
}

void Evaluate(Node* node)
{
	if (node==NIL||NULL)
		return;
	if (node->parent == NULL)
		return;
	if (node->parent->parent == NULL)
		return;
	Node* Parent = node->parent;
	Node* GParnet = Parent->parent; //할아버지node;
	if (Parent->color == BLACK)
		return;
	else {//부모가 레드일때
		std::cout << "평가함수 실험----------\n";
		std::cout << GParnet << std::endl;
		std::cout << "-----------------------\n";

		if (GParnet->right->color = BLACK) {
			if (Parent->right == node) {
				RotateLeft(Parent);
				std::cout << Parent << "기준으로 왼쪽회전!\n";
				RotateRighit(GParnet);
				std::cout << GParnet << "기준으로 오른쪽회전!\n";
				Parent->color = BLACK;
				GParnet->color = RED;
			}
			else if (Parent->left == node) {
				RotateRighit(GParnet);
				std::cout << GParnet << "기준으로 오른쪽회전!\n";
				Parent->color = BLACK;
				GParnet->color = RED;
			}
		}
		else if (GParnet->left->color = BLACK) {
			if (Parent->left == node) {
				RotateRighit(Parent);
				std::cout << Parent << "기준으로 오른쪽회전!\n";
				RotateLeft(GParnet);
				std::cout << GParnet << "기준으로 왼쪽회전!\n";
				Parent->color = BLACK;
				GParnet->color = RED;
			}
			else if (Parent->right == node) {
				RotateLeft(GParnet);
				std::cout << GParnet << "기준으로 왼쪽회전!\n";
				Parent->color = BLACK;
				GParnet->color = RED;
			}
		}
		if (GParnet->left->color == RED) {//삼촌노드 색깔보기
			Parent->color = BLACK;
			GParnet->left->color = BLACK;
			GParnet->color = RED;
			if (GParnet == ROOT) {
				GParnet->color = BLACK;
				return;
			}
			Evaluate(GParnet);
		}
		else if (GParnet->right->color == RED) {
			Parent->color = BLACK;
			GParnet->right->color = BLACK;
			GParnet->color = RED;
			if (GParnet == ROOT) {
				GParnet->color = BLACK;
				return;
			}
			Evaluate(GParnet);
		}
	}
	
}

void RotateRighit(Node* node)
{
	Node* Left = node->left;
	Node* Right = node->right;
	if (Left->right != NULL) {
		Left->right->parent = node;
		node->left = Left->right;
	}
	if (node->parent != NULL) {
		if (node == node->parent->right) {
			node->parent->right = Left;
		}
		else
			node->parent->left = Left;
	}
	else
		ROOT = Left;
	Left->parent = node->parent;
	Left->right = node;
	node->parent = Left;

}
void RotateLeft(Node* node)
{
	Node* Left = node->left;
	Node* Right = node->right;
	if (Right->left != NULL) {
		Right->left->parent = node;
		node->right = Right->left;
	}
	if (node->parent != NULL) {
		if (node == node->parent->left) {
			node->parent->left = Right;
		}
		else
			node->parent->right = Right;
	}
	else
		ROOT = Right;
	Right->parent = node->parent;
	Right->left = node;
	node->parent = Right;

}