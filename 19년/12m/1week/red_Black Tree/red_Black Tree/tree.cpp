#include "tree.h"


void NewNode(Node*& node, int data)
{
	node = new Node;
	node->data = data;
	node->left = node->right = nullptr;
	node->color = RED;
}
Node* Insert(Node* node, int data)
{
	if (node == nullptr) {// 트리의 마지막
		NewNode(node, data);
		return node;
	}
	else {
		if (data < node->data) {
			Node* parent = node;
			Node* newNode = nullptr;
			newNode=Insert(node->left, data);
			node->left= newNode;
			node->left->parents = parent;
		}
		else {
			Node* parent = node;
			Node* newNode = nullptr;
			newNode = Insert(node->right, data);
			node->right = newNode;
			node->right->parents = parent;
		}
	}
}

void PrintAll(Node* ROOT)
{
	if (ROOT == nullptr)
		return; 
	else {
		std::cout << "본인주소" << ROOT << " 부모주소:" << ROOT->parents << " 본인 data:" << ROOT->data << " 색깔" << ROOT->color << std::endl;
		PrintAll(ROOT->left);
		PrintAll(ROOT->right);
	}
}