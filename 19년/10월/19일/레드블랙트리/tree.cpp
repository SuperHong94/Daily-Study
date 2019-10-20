#include <iostream>
#include "tree.h"
Node* NIL;
Node* ROOT;
void Insert(Node*& node, int data)
{

	if (node == nullptr || node == NIL)
	{


		Node* newNode = new Node;
		newNode->left = newNode->right = NIL;
		newNode->color = RED;
		newNode->data = data;
		//newNode->parents = node->parents;
		node = newNode;
		//어떻게하면 여기서 node의 parents를 넣을수 있을까?;
		TreeRepair(node);
	}
	else {
		if (node->data < data) {
			if (node->right != nullptr)
				node->right->parents = node;
			Insert(node->right, data);


		}
		else
		{
			if (node->left != nullptr)
				node->left->parents = node;
			Insert(node->left, data);


		}
	}
}
void PrintTree(Node* node) {
	if (node == nullptr || node == NIL)
		return;
	else {
		std::cout << "자기주소: " << node << "부모주소: " << node->parents << "데이터: " << node->data;
		if (node->color == BLACK) std::cout << " 블랙 \n";
		else std::cout << " 빨강 \n";

		PrintTree(node->left);
		PrintTree(node->right);
	}
}
Node* GetParents(Node* node)
{
	return node == nullptr ? nullptr : node->parents;
}

Node* GetGrandparents(Node* node)
{
	return GetParents(GetParents(node));
}
Node* GetUncle(Node* node)
{
	Node* g = GetGrandparents(node);
	Node* p = GetParents(node);
	return GetSibling(p);

}
Node* GetSibling(Node* node)
{
	Node* p = GetParents(node);
	if (p == nullptr)
		return nullptr;
	if (node == p->left)return p->left;
	else p->right;
}



void InsertCase1(Node* node)
{
	//std::cout << "node's parents" << node->parents << '\n';
	if (node->parents == nullptr)
		node->color = BLACK;
}
void InsertCase2(Node* node)
{
	return;
}

void InsertCase3(Node* node)
{
	GetParents(node)->color = BLACK;
	GetUncle(node)->color = BLACK;
	GetGrandparents(node)->color = RED;
	TreeRepair(GetGrandparents(node));
}

void InsertCase4(Node* node)
{
	Node*p = GetParents(node);
	Node*g = GetGrandparents(node);
	if (node == p->right&&p == g->left)
	{
		LeftRotate(p);
		node = node->left;
	}
	else if (node == p->left&&p == g->right) {
		RightRotate(p);
		node = node->right;
	}
	InsertCase4_2(node);
}






void TreeRepair(Node* node)
{
	if (GetParents(node) == nullptr)
		InsertCase1(node);
	else if (GetParents(node)->color == BLACK)
		InsertCase2(node);
	else if (GetUncle(node) != nullptr && GetUncle(node)->color == RED)
		InsertCase3(node);
	else if (GetUncle(node) != nullptr && GetUncle(node)->color == BLACK)
		InsertCase4(node);
}

void LeftRotate(Node* node)
{

	std::cout << "왼쪽회전" << std::endl;//대칭
	Node*p = GetParents(node);
	Node* Right = node->right;
	node->right = Right->left;
	Right->left = node;
	node->parents = Right;
	if (node->right != nullptr && node->right != NIL)
		node->right->parents = node;
	if (p != nullptr) {
		if (node == p->left) {
			p->left = Right;
		}
		else if (node == p->right) {
			p->right = Right;
		}
	}
	else
		ROOT = Right;
	Right->parents = p;
}

void RightRotate(Node* node)
{
	std::cout << "오른쪽회전" << std::endl;//대칭
	Node*p = GetParents(node); //Node*p = GetParents(node);
	Node* Left = node->left;  //Node* Right = node->right;
	node->left = Left->right;  //node->right = Right->left;
	Left->right = node;  //Right->left = node;
	node->parents = Left;

	if (node->right != nullptr && node->right != NIL)
		node->left->parents = node; //Right->left->parents = node;
	if (p != nullptr) {
		if (node == p->left)
			p->left == Left;
		else if (node == p->right)
			p->right = Left;  //p->left = Right;
	}
	else
		ROOT = Left;

	Left->parents = p; // 	Right->parents = p;

}

void InsertCase4_2(Node* node)
{
	Node* p = GetParents(node);
	Node* g = GetGrandparents(node);
	if (node == p->left)
		RightRotate(g);
	else
		LeftRotate(g);
	p->color = BLACK;
	g->color = RED;

}