#include <iostream>

int A(int a) {
	a--;
	if (a == 0) {
		std::cout << "=========\n";
		std::cout << "a는 0이다.\n";
		std::cout << "=========\n";

		return 100;
	}
	else {
		std::cout << a << "a는 0아니다.\n";
		A(a);
	}

	std::cout << a << std::endl;
	return 10;
}

int main()
{
	int b = A(9);
	std::cout << "==========\n";
	std::cout << b << std::endl;
}