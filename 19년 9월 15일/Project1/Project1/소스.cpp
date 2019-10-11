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

	//온도를 vector에 읽어 들인다.

	//std::vector<double> temps;

	//for (double temp; std::cin >> temp;) {  //for문안에 std::cin이 들어가있는데 기본적으로 std::cin은 값을 올바르게 읽으면 참,그렇지 못하면 거짓이다.
	//	temps.push_back(temp);
	//}
	//double average = 0;
	//for (int i = 0; i < temps.size(); i++) {
	//	average += temps[i];
	//}
	//average = average / temps.size();
	//std::cout << "온도 평균:" << average << std::endl;
	//std::cout << "온도 중앙값:" << temps[temps.size() / 2] << std::endl;

	//간단한 사전: 정렬된 단어 목록

	//vector<string> words;

	//for (string x; cin >> x;) words.push_back(x);

	//sort(words);

	//for (int i = 0; i < words.size(); ++i)
	//	if (i == 0 || words[i - 1] != words[i])
	//		cout << words[i] << endl;

	//도전문제

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