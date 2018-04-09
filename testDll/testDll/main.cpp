#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "../../Core/Core/dll.h"

using namespace std;


int main() {
	string s, result;

	bool add, sub, mul, div, pow;
	add = true; sub = 1; mul = 1; div = true; pow = true;
	set(1000, 0, 1, 0, -1);
	set_power_signal(false);
	set_opr(add, sub, mul, div, pow);
	generate();

	for (int i = 0; i < 1000; i++) {
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