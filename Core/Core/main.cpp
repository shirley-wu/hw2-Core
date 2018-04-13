#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "dll.h"

using namespace std;


int main() {
<<<<<<< HEAD
	string s, result;
	const int n = 1000;
	char s[10];

	/*int i = snprintf(s, 10, "hi");
	cout << i << endl;
	cout << s << endl;
	int j = snprintf(s + i, 10 - i, "hello");
	cout << j << endl;
	cout << s << endl;
	int k = snprintf(s, 5, "1234567890");
	cout << k << endl;
	cout << s << endl;

	system("pause");
	return 0;*/

	generate();

	char *cs = new char[10000];
	char *cresult = new char[10000];

	set(1000, 100, n, 0);
	generate();
	for (int i = 0; i < n; i++) {
		if (get_exp(i, s, result) == false) {
			system("pause");
		}
	}
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	set(1000, 100, n, 1);
	generate();
	for (int i = 0; i < n; i++) {
		if (get_exp(i, s, result) == false) {
			system("pause");
		}
	}
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
