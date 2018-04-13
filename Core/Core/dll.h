#pragma once

#include <string>

#ifdef CORE_DLL_IMPLEMENT
#define CORE_DLL_API
#else
#define CORE_DLL_API __declspec(dllimport)
#endif


CORE_DLL_API void set(int num_max, int num_limit, int exp_num, int type = 0, int precision = 2);
CORE_DLL_API void set_precision(int precision);
CORE_DLL_API void set_opr(bool add, bool sub, bool mul, bool div, bool pow);
CORE_DLL_API void set_power_signal(bool s);

CORE_DLL_API void generate();
CORE_DLL_API void clear();

CORE_DLL_API bool get_exp(int i, std::string& s, std::string& result);

CORE_DLL_API bool get_expression(int i, char *s, int size);
CORE_DLL_API bool get_answer(int i, char *s, int size);

CORE_DLL_API bool exp_to_file(const char* dir);
CORE_DLL_API bool ans_to_file(const char* dir);