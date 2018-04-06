#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "generator.h"

using namespace std;


void Calc(char cal[]);


int main() {
	srand(time(0));
	Generator generator;
	generator.set(1000, 20, 10, DOUBLE);
	generator.generate();
	for (int i = 0; i < 10; i++) {
		string s;
		Num result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "index: " << i << endl;
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	generator.set(1000, 20, 10, INT);
	generator.generate();
	for (int i = 0; i < 10; i++) {
		string s;
		Num result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		// char str[10000];
		// strcpy(str, s.c_str());
		cout << "index: " << i << endl;
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
		cout << "calc:" << endl;
		// Calc(str);
	}
	generator.set(1000, 20, 10, FRACTION);
	generator.generate();
	for (int i = 0; i < 10; i++) {
		string s;
		Num result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "index: " << i << endl;
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
		cout << "calc:" << endl;
	}
	system("pause");
	return 0;
}