#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "generator.h"

using namespace std;


void Calc(char cal[]);


int main() {
	char str[10000];
	srand((unsigned)time(0));
	Generator generator;
	generator.set(3, 20, 10, DOUBLE, 3);
	generator.generate();
	for (int i = 0; i < 10; i++) {
		string s;
		Num result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	cout << endl;
	generator.set(1000, 20, 10, INT);
	generator.generate();
	for (int i = 0; i < 10; i++) {
		string s;
		Num result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		memset(str, 0, sizeof(char) * 10000);
		strcpy(str, s.c_str());
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
		cout << "calc:";
		Calc(str);
	}
	cout << endl;
	generator.set(1000, 20, 10, FRACTION);
	generator.generate();
	for (int i = 0; i < 10; i++) {
		string s;
		Num result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		memset(str, 0, sizeof(char) * 10000);
		strcpy(str, s.c_str());
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
		cout << "calc:";
		Calc(str);
	}
	system("pause");
	return 0;
}