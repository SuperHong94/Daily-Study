
//KruskalMST(G) 알고리즘
//#include <iostream>
//#define V 6
//struct Node {
//	int p1, p2;
//	int value;
//	void printNode();
//};
//struct Tree {
//	Tree* parent=nullptr;
//	int id;
//	bool include = false;
//};
//void Node::printNode() {
//	std::cout <<p1<<","<<p2<<"의 간선"<< value << ' ';
//}
//void KruskalMST(int G[][V]);
//
//bool findId(Tree* a, int id) {
//	if (a == nullptr)
//		return false;
//	else if (a->id == id)
//		return true;
//	else
//		findId(a->parent, id);
//}
//int main()
//{
//	int graph[][V] = {
//	{0,8,2,0,4,0},
//	{8,0,4,1,0,2},
//	{2,4,0,0,3,7},
//	{0,1,0,0,0,1},
//	{4,0,3,0,0,9},
//	{0,2,7,1,9,0}
//	};
//	KruskalMST(graph);
//}
//
//
//void nodeSwap(Node& a, Node& b) {
//	Node temp = a;
//	a = b;
//	b = temp;
//}
//
//void MyQsort(Node* L,int left,int right) {
//	int p = right;
//	int i = left;
//	int j = left;
//
//	if (left < right) {
//		while (j < right) {
//			if (L[j].value < L[p].value) {
//				nodeSwap(L[i], L[j]);
//				i++;
//				j++;
//			}
//			else
//				j++;
//				
//		}
//		nodeSwap(L[i], L[p]);
//		p = i;
//
//		MyQsort(L, left, p - 1);
//		MyQsort(L, p+1 , right);
//	}
//}
//void KruskalMST(int G[][V])
//{
//	Node L[10];
//	int k = 0;
//	for (int i = 0; i < V; ++i) {
//		for (int j = 0; j < V; ++j)
//		{
//			if (G[i][j] != 0) {
//				L[k].p1 = i;
//				L[k].p2 = j;
//				L[k].value = G[i][j];
//				G[j][i] = 0;
//				k++;
//			}
//		}
//	}
//	MyQsort(L, 0, 9);
//	for (int i = 0; i < 10; i++) {
//		L[i].printNode();
//		std::cout << '\n';
//	}
//	std::cout << '\n';
//
//	Tree t[V];
//	for (int i = 0; i < V; i++) {
//		t[i].id = i;
//	}
//
//
//	int count = 0;
//	int min = 0;
//	while (count < V - 1) {
//		int p1 = L[min].p1;
//		int p2 = L[min].p2;
//		int value = L[min].value;
//		if (!t[p1].include) {
//			if (!findId(t[p2].parent, p1)&&!findId(t[p1].parent,p2)) {
//				t[p2].include = true;
//				t[p2].parent = &t[p1];
//				count++;
//				std::cout << "간선:" << value << "점" << L[min].p1 << ',' << L[min].p2 << '\n';
//			}
//		}
//		else if (!t[p2].include) {
//			if (!findId(t[p2].parent, p1) && !findId(t[p1].parent, p2)) {
//				t[p2].include = true;
//				t[p2].parent = &t[p1];
//				count++;
//				std::cout << "간선:" << value << "점" << L[min].p1 << ',' << L[min].p2 << '\n';
//			}
//		}
//		min++;
//	}
//}


//PrimMST(G) 알고리즘

#include <iostream>
#define V 6
#define MAX 9999
void PrimMST(int(*G)[V], int);
int main()
{
	int graph[][V] = {
			{0,8,2,0,4,0},
			{8,0,4,1,0,2},
			{2,4,0,0,3,7},
			{0,1,0,0,0,1},
			{4,0,3,0,0,9},
			{0,2,7,1,9,0}
	};
}
int min(int G[][V], int p) {
	int min = MAX;
	for (int i = 0; i < V; i++) {
		if (i != p) {
			if (G[p][i] < min)
				min = G[p][i];
		}
	}
	for (int i = 0; i < V; i++) {
		if (min == G[p][i])
			return i;
	}
}

bool find(int* T, int w) {
	for (int i = 0; i < V; i++) {
		if (T[i] == w)
			return true;
	}
	return false;
}
void PrimMST(int(*G)[V], int p)
{
	int D[V];
	D[p] = 0;
	for (int i = 0; i < V; i++) {
		if (i != p) {
			if (G[p][i] != 0)
				D[i] = G[p][i];
			else
				D[i] = MAX;
		}
	}
	int count = 0;
	int T[V];
	for (int i = 0; i < V; i++)T[i] = -1;

	T[count] = p;
	count++;
	while (count < V)
	{
		std::cout << T[count] << ',' << min(G, p) << "의 가중치:" << G[T[count]][p] << '\n';

		T[count++] = min(G, p);
		for (int w = 0; w < V; w++) {
			if (!find(T, w)) {
				if (G[T[count-1]][w] < D[w]) {
					D[w] = G[T[count-1]][w];
				}
			}
		}
	}

}