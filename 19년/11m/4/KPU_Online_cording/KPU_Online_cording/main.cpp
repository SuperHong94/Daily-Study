//Yahtzee Small Straight

#include <iostream>
#include <cmath>
#define COUNT 5
int main()
{
	int A[COUNT];


	for (int i = 0; i < COUNT; ++i) {
		std::cin >> A[i];
	}
	int trueCount = 0;
	int falseCount = 0;
	for (int i = 0; i < COUNT; i++) {
		if (falseCount == 2)
			break;

		if (pow(A[i] - A[i + 1], 2) == 1 || pow(A[i] - A[i + 1], 2) == 0) {
			trueCount++;
		}
		else
			falseCount++;

	}
	if (pow(A[4] - A[0], 2) == 1 || pow(A[4] - A[0], 2) == 0)
		trueCount++;



	if (trueCount >= 3)
		std::cout << "YES" << std::endl;
	else if (trueCount < 3)
		std::cout << "NO" << std::endl;
}