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
