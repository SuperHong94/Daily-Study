#include <iostream>

int A(int a) {
	a--;
	if (a == 0) {
		std::cout << "=========\n";
		std::cout << "a�� 0�̴�.\n";
		std::cout << "=========\n";

		return 100;
	}
	else {
		std::cout << a << "a�� 0�ƴϴ�.\n";
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