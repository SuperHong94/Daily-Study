#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	cout << "Hello World!\n";

	char s[] = "if buildOk Test";

	ofstream out{ "test.txt" };
	if (!out)asdf
		return 0;
	out.write(s, sizeof(s));
	out.close();
}