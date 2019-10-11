#include <iostream>
#include <vector>

//실습문제 1,2,3,4,11번

void MySwap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void MyQsort(std::vector<int >& v, int left, int right) {
	int mid = (left + right) / 2;
	int p = right;
	int i = left, j = left;
	if (left < right)
	{
		while (j < right) {
			if (v[j] > v[p])
				j++;
			else {
				MySwap(v[i], v[j]);
				i++;
				j++;
			}
		}
		MySwap(v[i], v[p]);
		p = i;
		MyQsort(v, left, p-1);
		MyQsort(v, p + 1, right);
	}
}

int main()
{
	int x, y;
	std::vector<int> v;
	while (std::cin >> x && std::cin >> y) {
		std::cout << "x: " << x << " y: " << y << '\n';
		if (x > y) {
			std::cout << "큰 수는 x:" << x << " 작은 수는 y:" << y << '\n';
		}
		else if (y > x) {
			std::cout << "큰 수는 y:" << y << " 작은 수는 x:" << x << '\n';
		}
		else std::cout << " 두 수는 같다.\n";
		v.push_back(x);
		v.push_back(y);
	}

	MyQsort(v, 0, v.size() - 1);
	std::cout << "ddkdk" << std::endl;
	for (int i = 0; i < v.size(); i++)
		std::cout << v[i] << std::endl;
}