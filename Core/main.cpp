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
	generator.set(1000, 20, 100);
	while (1) {
		generator.generate();
		for (int i = 0; i < 5; i++) {
			string s;
			NUMTYPE result;
			if (generator.get_exp(i, s, result) == false) {
				cout << "problem" << i << endl;
				system("pause");
			}
			char str[10000];
			strcpy(str, s.c_str());
			cout << "index: " << i << endl;
			cout << "string: " << s << endl;
			cout << "result: " << result << endl;
			cout << "calc:" << endl;
			Calc(str);
		}
	}
	return 0;
}