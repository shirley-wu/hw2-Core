#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "generator.h"

using namespace std;


int main() {
	srand(time(0));
	Generator generator;
	generator.generate();
	for (int i = 0; i < 5; i++) {
		string s;
		int result;
		if (generator.get_exp(i, s, result) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << i << endl;
		cout << s << endl;
		cout << result << endl;
	}
	return 0;
}