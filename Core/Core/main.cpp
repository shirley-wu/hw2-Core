#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "dll.h"

using namespace std;


int main() {
	string s, result;
	const int n = 1000;

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