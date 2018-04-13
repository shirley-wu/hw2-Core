#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "dll.h"

using namespace std;


int main() {
	string s, result;
	const int n = 1000;

	/*char ss[10];

	int i = snprintf(ss, 10, "%.*f", 3, 1.5555555);
	cout << i << endl;
	cout << ss << endl;
	int j = snprintf(ss + i, 10 - i, "hello");
	cout << j << endl;
	cout << ss << endl;
	int k = snprintf(ss, 5, "1234567890");
	cout << k << endl;
	cout << ss << endl;

	system("pause");
	return 0;*/

	generate();

	char *cs = new char[10000];
	char *cresult = new char[10000];

	set(1000, 10, 10, 1);
	generate();
	for (int i = 0; i < 10; i++) {
		if (get_exp(i, s, result) == false) {
			system("pause");
		}
		if (get_exp(i, cs, 1000, cresult) == false) {
			system("pause");
		}
		cout << s << " = " << result << endl;
		cout << cs << " = " << cresult << endl;
	}
	system("pause");
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	set(1000, 10, 10, 0);
	generate();
	for (int i = 0; i < 10; i++) {
		if (get_exp(i, s, result) == false) {
			system("pause");
		}
		if (get_exp(i, cs, 1000, cresult) == false) {
			system("pause");
		}
		cout << s << " = " << result << endl;
		cout << cs << " = " << cresult << endl;
	}
	system("pause");
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	set(1000, 100, n, 2);
	generate();
	for (int i = 0; i < n; i++) {
		if (get_exp(i, s, result) == false) {
			system("pause");
		}
	}
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	clear();

	return 0;
}
