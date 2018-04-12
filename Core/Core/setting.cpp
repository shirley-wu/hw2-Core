#include <cstdlib>

#include "setting.h"

#ifndef CORE_DLL_IMPLEMENT
#define CORE_DLL_IMPLEMENT
#endif

#include "dll.h"

using namespace std;


Setting setting;


void set(int num_max, int num_limit, int exp_num, int type, int precision) {
	if (setting.num_max > 0) {
		setting.num_max = num_max;
	}
	if (setting.num_limit > 0) {
		setting.num_limit = num_limit;
	}
	if (setting.exp_num > 0) {
		setting.exp_num = exp_num;
	}
	if (0 <= type && type <= 2) {
		setting.type = NumType(type);
	}
	if (precision > 0) {
		setting.precision = precision;
	}
}


void set_precision(int precision) {
	if (precision > 0) {
		setting.precision = precision;
	}
}


void set_opr(bool add, bool sub, bool mul, bool div, bool pow) {
	if (add == false && sub == false && mul == false && div == false && pow == false) return;
	setting.opr[0] = add;
	setting.opr[1] = sub;
	setting.opr[2] = mul;
	setting.opr[3] = div;
	setting.opr[4] = pow;
	setting.opr_num = 0;
	for (int i = 0; i < OPRNUM; i++) {
		if (setting.opr[i]) setting.opr_num++;
	}
}


OPRTYPE randomopr() {
	int v = rand() % setting.opr_num;
	for (int i = 0; i < OPRNUM; i++) {
		if (setting.opr[i]) {
			if (v == 0) return OPRTYPE(i);
			else v--;
		}
	}
	throw("wtf");
}


void set_power_signal(bool s) {
	setting.power_signal = s;
}