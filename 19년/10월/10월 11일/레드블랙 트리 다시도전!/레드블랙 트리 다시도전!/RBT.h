#pragma once
enum color_t { BLACK, RED };

struct Node {
	Node* parent;
	Node* left;
	Node* right;
	enum color_t color;
	int key;
};
static void MakeNode(Node*& node, int key);
Node* GetParent(Node* n);
Node* GetGrandParent(Node* n);
Node* GetSibling(Node* n);
Node* GetUncle(Node* n);
void RotateLeft(Node* n);
void RotateRight(Node* n);
Node* Insert(Node* root, Node* n);
void InsertRecurse(Node* root, Node* n);
void InsertRepairTree(Node* n);
void InsertCase1(Node* n);
void InsertCase2(Node* n);
void InsertCase3(Node* n);
void InsertCase4(Node* n);
void InsertCase4Step2(Node* n);