#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "../../Core/Core/dll.h"

using namespace std;

int main() {
	char s[10000], result[10000];

	bool add, sub, mul, div, pow;
	add = 1; sub = 1; mul = 1; div = 1; pow = 0;
	set_power_signal(1);
	set(10, 3, 10, 2);
	set_opr(add, sub, mul, div, pow);
	generate();

	for (int i = 0; i < 10; i++) {
		if (get_expression(i, s, 1000) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		if (get_answer(i, result, 1000) == false) {
			cout << "problem" << i << endl;
			system("pause");
		}
		cout << "string: " << s << endl;
		cout << "result: " << result << endl;
	}
	/*CORE_DLL_API void set(int num_max, int num_limit, int exp_num, int type = 0, int precision = 2);
      CORE_DLL_API void set_precision(int precision);
      CORE_DLL_API void set_opr(bool add, bool sub, bool mul, bool div, bool pow);
      CORE_DLL_API void set_power_signal(bool s);

      CORE_DLL_API void generate();
      CORE_DLL_API void clear();

      CORE_DLL_API bool get_exp(int i, std::string& s, std::string& result);

      CORE_DLL_API bool get_expression(int i, char *s, int size);
      CORE_DLL_API bool get_answer(int i, char *s, int size);

      CORE_DLL_API bool exp_to_file(const char* dir);
      CORE_DLL_API bool ans_to_file(const char* dir);*/
	cout << endl;

	clear();

	system("pause");
	return 0;
}