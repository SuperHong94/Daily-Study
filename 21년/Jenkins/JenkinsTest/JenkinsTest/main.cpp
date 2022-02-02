#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	cout << "Hello World!\n";

	char s[] = "if buildOk Test";

	ofstream out{ "test.txt" };
	if (!out)
		return 0;
	out.write(s, sizeof(s));
	out.close();

	std::cout << "build test Jenkins build Test!\n";
}