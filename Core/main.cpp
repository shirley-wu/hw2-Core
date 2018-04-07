#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "generator.h"

using namespace std;


int main() {
	srand((unsigned)time(0));
	set(1000, 20, 10, DOUBLE, 3);
	generate();
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
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
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
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	system("pause");
	return 0;
}