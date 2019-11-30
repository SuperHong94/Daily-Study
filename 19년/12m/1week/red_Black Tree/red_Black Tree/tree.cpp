#include "tree.h"


Node* NewNode(int data)
{
	Node* node = new Node;
	node->data = data;
	node->left = node->right = nullptr;
	node->color = RED;
	return node;
}
void printColor(int d) {
	if (d == BLACK)
		std::cout << "����";
	else
		std::cout << "����";
}
Node* Insert(Node* node, int data)
{
	if (node == nullptr) {// Ʈ���� ������
		node=NewNode(data);
		return node;
	}
	else {
		if (data < node->data) {
			Node* parent = node;
			Node* newNode = nullptr;
			newNode = Insert(node->left, data);
			node->left = newNode;
			node->left->parents = parent;
			if (node->left->left == nullptr&&node->left->right == nullptr)  //������϶� üũ�Ѵ�.
				CheckTree(node->left);
		}
		else {
			Node* parent = node;
			Node* newNode = nullptr;
			newNode = Insert(node->right, data);
			node->right = newNode;
			node->right->parents = parent;
			if (node->right->left == nullptr&&node->right->right == nullptr)  //������϶� üũ�Ѵ�.
				CheckTree(node->right);
		}
	}
}

void PrintAll(Node* ROOT)
{
	if (ROOT == nullptr)
		return;
	else {
		std::cout << "�����ּ�" << ROOT << " �θ��ּ�:" << ROOT->parents << " ���� data:" << ROOT->data << " ����:";
		printColor(ROOT->color);
		std::cout << std::endl;
		PrintAll(ROOT->left);
		PrintAll(ROOT->right);
	}
}
void CheckTree(Node* node)
{
	if (node->parents == nullptr) { //node�� ��Ʈ�ΰ����
		if (node->color == RED) {
			node->color = BLACK;
			return;
		}
		return;
	}
	if (node->parents->color == BLACK)
		return;
	else {  //�θ� ����
		Node* uncle = GetSibling(node->parents);

		if (uncle == nullptr || uncle->color == BLACK) {
			case2_1(node);
		}
		else if (uncle->color == RED) {
			node->parents->color = BLACK;
			uncle->color = BLACK;
			CheckTree(node->parents);
		}

	}
}

Node* GetSibling(Node* node)
{
	if (node->parents == nullptr)  //�θ𰡾����� ������ ����.
		return nullptr;
	else {
		if (node->parents->left != node) {
			return node->parents->left;
		}
		else
			return node->parents->right;
	}
}
