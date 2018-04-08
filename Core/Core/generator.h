#pragma once

#include <string>

#ifdef GENERATOR_DLL_IMPLEMENT
#define GENERATOR_DLL_API __declspec(dllexport)
#else
#define GENERATOR_DLL_API __declspec(dllimport)
#endif


GENERATOR_DLL_API void set(int num_max, int num_limit, int exp_num, int type = 0, int precision = 2);
GENERATOR_DLL_API bool generate();
GENERATOR_DLL_API void clear();
GENERATOR_DLL_API bool get_exp(int i, std::string& s, std::string& result);