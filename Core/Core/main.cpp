#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "dll.h"

using namespace std;


int main() {
	const int size = 100;
	char *cs = new char[size];
	char *cresult = new char[size];

	set(1000, 10, 10, 1);
	generate();
	for (int i = 0; i < 10; i++) {
		bool s1 = get_expression(i, cs, size);
		bool s2 = get_answer(i, cresult, size);
		if (s1 && s2) {
			cout << cs << " = " << cresult << endl;
		}
		else {
			if (s1 == false) {
				cout << "false1\n";
			}
			else cout << "expression " << cs << endl;
			if (s2 == false) {
				cout << "false2\n";
			}
			else cout << "answer " << cresult << endl;
		}
	}
	system("pause");
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	set(1000, 10, 10, 0);
	generate();
	for (int i = 0; i < 10; i++) {
		bool s1 = get_expression(i, cs, size);
		bool s2 = get_answer(i, cresult, size);
		if (s1 && s2) {
			cout << cs << " = " << cresult << endl;
		}
		else {
			if (s1 == false) {
				cout << "false1\n";
			}
			else cout << "expression " << cs << endl;
			if (s2 == false) {
				cout << "false2\n";
			}
			else cout << "answer " << cresult << endl;
		}
	}
	system("pause");
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	set(1000, 100, 10, 2);
	generate();
	for (int i = 0; i < 10; i++) {
		bool s1 = get_expression(i, cs, size);
		bool s2 = get_answer(i, cresult, size);
		if (s1 && s2) {
			cout << cs << " = " << cresult << endl;
		}
		else {
			if (s1 == false) {
				cout << "false1\n";
			}
			else cout << "expression " << cs << endl;
			if (s2 == false) {
				cout << "false2\n";
			}
			else cout << "answer " << cresult << endl;
		}
	}
	system("pause");
	if (exp_to_file("D:\\Users\\wu-pc\\repos\\hw2\\expression0.txt") == false) system("pause");
	if (ans_to_file("D:\\Users\\wu-pc\\repos\\hw2\\answer0.txt") == false)system("pause");

	clear();

	return 0;
}
