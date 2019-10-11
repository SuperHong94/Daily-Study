#include <iostream>
#include <random>
#include <ctime>
#define SIZE 20
void MergeSort(int*, int, int);
void Merge(int*, int, int);

int main() {
	srand(time(NULL));
	int A[SIZE];
	for (int& d : A) d = rand() % 100;
	std::cout << "������ \n";
	for (int d : A)std::cout << d << ' ';
	printf("\n");
	std::cout << "������ \n";
	MergeSort(A, 0, SIZE-1);
	for (int d : A)std::cout << d << ' ';
	
	printf("\n");
}

void MergeSort(int* A, int left, int right)
{
	int p = (left + right) / 2;
	if (left < right) {
		MergeSort(A, left, p);
		MergeSort(A, p + 1, right);
		Merge(A, left, right);
	}
}
void Merge(int* A, int left, int right)
{
	int i = left; //�����ҳ༮ ��ġ
	int j = left; //�����ؼ� ���� ��ġ  copy�� ��
	int k = ((left + right) / 2) + 1;
	int mid = k - 1;
	int copy[SIZE];
	while (i <= mid && k <= right) {
		if (A[i] > A[k])copy[j++] = A[k++];
		else copy[j++] = A[i++];
	}

	while (i <= mid) copy[j++] = A[i++];  //���ʳ������
	while (k <= right)copy[j++] = A[k++];  //������ �������

	for (int i = left; i < right+1; i++)
		A[i] = copy[i];
}