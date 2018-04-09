#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "../../Core/Core/generator.h"

using namespace std;


int main() {
	srand((unsigned)time(0));
	string s, result;

	set(1000, 20, 10, 0, 3);
	generate();
	for (int i = 0; i < 10; i++) {
		if (get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	cout << endl;
/*
	set(1000, 20, 10, 1);
	generate();
	for (int i = 0; i < 10; i++) {
		if (get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	cout << endl;

	set(1000, 20, 10, 2);
	generate();
	for (int i = 0; i < 10; i++) {
		if (get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
*/
	system("pause");
	return 0;
}