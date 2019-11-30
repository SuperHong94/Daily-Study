#pragma once
#include <iostream>
#include <random>
#define SIZE 5
#define BLACK 0
#define RED 1
struct Node {
	Node* parents = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	int data;
	int color = BLACK;
};

void NewNode(Node*& node, int data);
void PrintAll(Node* ROOT);
Node* Insert(Node* node, int data);

