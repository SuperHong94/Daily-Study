#include "global.h"
int main()
{
	//std::vector<int> v;
	//v.push_back(8);
	//v.push_back(8);
	//v.push_back(8);
	//v[2] = 10;
	//
	//for (int i = 0; i < v.size(); i++)
	//	std::cout << v[i] << std::endl;

	//std::cout << "========" << std::endl;
	//std::cout << v.size() << std::endl;
	//std::cout << "========" << std::endl;
	//for (int d : v)
	//	std::cout << d << std::endl;

	//�µ��� vector�� �о� ���δ�.

	//std::vector<double> temps;

	//for (double temp; std::cin >> temp;) {  //for���ȿ� std::cin�� ���ִµ� �⺻������ std::cin�� ���� �ùٸ��� ������ ��,�׷��� ���ϸ� �����̴�.
	//	temps.push_back(temp);
	//}
	//double average = 0;
	//for (int i = 0; i < temps.size(); i++) {
	//	average += temps[i];
	//}
	//average = average / temps.size();
	//std::cout << "�µ� ���:" << average << std::endl;
	//std::cout << "�µ� �߾Ӱ�:" << temps[temps.size() / 2] << std::endl;

	//������ ����: ���ĵ� �ܾ� ���

	//vector<string> words;

	//for (string x; cin >> x;) words.push_back(x);

	//sort(words);

	//for (int i = 0; i < words.size(); ++i)
	//	if (i == 0 || words[i - 1] != words[i])
	//		cout << words[i] << endl;

	//��������

	string dis = "super";

	vector<string> words = {"dkdk","dkdk"};

	for (string temp; cin >> temp;) {
		words.push_back(temp);
	}
	sort(words);

	for (string d : words) {
			std::cout << d << std::endl;
	}
	cout <<words.begin() << endl;

}