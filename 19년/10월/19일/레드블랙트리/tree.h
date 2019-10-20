#pragma once
#define BLACK 0
#define RED 1
struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parents;
	int color=BLACK;
};

extern Node* NIL;

extern Node* ROOT;

void Insert(Node*& node,int data);
void PrintTree(Node*);
Node* GetParents(Node* node);
Node* GetGrandparents(Node* node);
Node* GetUncle(Node*);
Node* GetSibling(Node*);
void InsertCase1(Node*);
void InsertCase2(Node*);
void InsertCase3(Node*);
void InsertCase4(Node* node);
void InsertCase4_2(Node* node);
void TreeRepair(Node*);
void RightRotate(Node*);
void LeftRotate(Node*);