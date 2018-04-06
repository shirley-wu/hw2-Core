#include <iostream>
#include <cmath>

#include "num.h"

using namespace std;


Num::operator double() const {
	if (type == DOUBLE) return dat.double_val;
	else if (type == INT) return (double)dat.int_val;
	else return (double)dat.f_val;
}


Num Num::operator+(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		return Num((double)(*this) + (double)f);
	}
	else if (type == INT){
		return Num(dat.int_val + f.dat.int_val);
	}
	else return Num(dat.f_val + f.dat.f_val);
}


Num Num::operator-(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		return Num((double)(*this) - (double)f);
	}
	else if (type == INT) {
		return Num(dat.int_val - f.dat.int_val);
	}
	else return Num(dat.f_val - f.dat.f_val);
}


Num Num::operator*(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		return Num((double)(*this) * (double)f);
	}
	else if (type == INT) {
		return Num(dat.int_val * f.dat.int_val);
	}
	else return Num(dat.f_val * f.dat.f_val);
}


Num Num::operator/(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		return Num((double)(*this) / (double)f);
	}
	else if (type == INT) {
		return Num(dat.int_val / f.dat.int_val);
	}
	else return Num(dat.f_val / f.dat.f_val);
}


bool Num::operator==(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		return fabs((double)(*this) - (double)f) < EPS;
	}
	else if (type == INT) {
		return dat.int_val == f.dat.int_val;
	}
	else return dat.f_val == f.dat.f_val;
}


ostream& operator<<(ostream& os, const Num& n) {
	if (n.type == INT) os << n.dat.int_val;
	else if (n.type == DOUBLE) os << n.dat.double_val;
	else os << n.dat.f_val;
	return os;
}


Num Num::randomNum(NumType t, int limit, int precision) {
	if (t == DOUBLE) {
		double base = pow(10, precision);
		int real_limit = base * limit;
		int val = rand() % real_limit;
		double dval = (double)val / base;
		return Num(dval);
	}
	else if (t == INT) {
		int val = rand() % limit;
		return Num(val);
	}
	else {
		// int den = rand() % limit + 2;
		// int num = rand() % (den - 1) + 1;
		// return Num(num, den);
		int val = rand() % limit;
		return Num(val, 1);
	}
}