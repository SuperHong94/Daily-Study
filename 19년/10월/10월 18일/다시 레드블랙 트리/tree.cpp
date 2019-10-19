#include <iostream>
#include "tree.h"
Node* NIL;
Node* ROOT;
void Insert(Node*& node, int data)
{
	if (node == NULL || node == NIL) {
		node = new Node;
		node->left = node->right = NIL;
		node->color = RED;
		node->data = data;
	}
	else {
		if (node->data < data) {
			node->right->parents = node;
			Insert(node->right,data);
			return;
		}
		else
		{
			node->left->parents = node;
			Insert(node->left, data);
			return;
		}
	}
}
void PrintTree(Node* node) {
	if (node == NULL || node == NIL)
		return;
	else {
		std::cout << "�ڱ��ּ�: " << node << "�θ��ּ�: " << node->parents << "������: " << node->data;
		if (node->color == BLACK) std::cout << " �� \n";
		else std::cout << " ���� \n";
		PrintTree(node->left);
		PrintTree(node->right);

	}
}