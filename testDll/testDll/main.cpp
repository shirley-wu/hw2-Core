#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "../../Core/Core/dll.h"

using namespace std;


int main() {
	char s[100], result[100];

	bool add, sub, mul, div, pow;
	add = true; sub = 1; mul = 1; div = true; pow = true;
	set(1000, 20, 10, 2);
	set_opr(add, sub, mul, div, pow);
	generate();

	for (int i = 0; i < 10; i++) {
		if (get_expression(i, s, 100) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		if (get_answer(i, result, 100) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	cout << endl;

	clear();

	system("pause");
	return 0;
}