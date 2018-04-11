#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "dll.h"

using namespace std;


int main() {
	generate();
	// 默认生成十个式子，详见github上面的api说明或者直接看代码=w=

	char *cs = new char[10000];
	char *cresult = new char[10000];

	for (int i = 0; i < 10; i++) {
		get_exp(i, cs, 10000, cresult);
		cout << "s" << cs << endl;
		cout << "cresult" << cresult << endl;

		string s, result;
		get_exp(i, s, result);
		cout << "s" << s << endl;
		cout << "cresult" << result << endl;

		system("pause");
	}
	delete[] cs;
	delete[] cresult;

	clear();

	return 0;
}