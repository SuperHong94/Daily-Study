#include <iostream>
#include <random>
#define SIZE 20
void Merge(int*, int* myArray, int left, int right);
void MergeSort(int* myArray, int left, int right)
{
	int copy[SIZE];
	for (int i = 0; i < SIZE; i++) {
		copy[i] = myArray[i];
	}
	int p = (left + right) / 2;
	if (left < right) {
		MergeSort(myArray, left, p);
		MergeSort(myArray, p + 1, right);
		Merge(copy, myArray, left, right);
	}

}



int main()
{
	std::default_random_engine dre;
	std::uniform_int_distribution<int> uid(0, 100);

	int myArray[SIZE];
	for (int& d : myArray) d = uid(dre);
	std::cout << "정렬전 \n";
	for (int d : myArray) std::cout << d << ' ';
	std::cout << '\n';
	MergeSort(myArray, 0, SIZE - 1);
	std::cout << "정렬후 \n";
	for (int d : myArray) std::cout << d << ' ';

}
void Merge(int* copy, int* myArray, int left, int right)
{

	int k = ((left + right) / 2) + 1;
	int mid = k - 1;
	int j = left;  //데이터복사해서 넣을자리
	int i = left;//데이터 복사할자리

	while (i <= mid && k <= right) {
		if (myArray[i] > myArray[k]) {
			copy[j++] = myArray[k++];
		}
		else {
			copy[j++] = myArray[i++];
		}
	}
	while (i <= mid)
		copy[j++] = myArray[i++];
	while (k <= right)
		copy[j++] = myArray[k++];

	for (int i = 0; i < SIZE; i++) {
		myArray[i] = copy[i];
	}

}