#include <iostream>
#include <vector>
int main()
{

	std::vector<int> v = { 5,7,9,4,6,8 };
	std::cout << v.size() << "\n -------------" << std::endl;
	/*for (int i = 0; i < v.size(); ++i)
		std::cout << v[i] << std::endl;*/
	for (int x : v)
		std::cout << x << '\n';
}