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


ostream& operator<<(ostream& os, const Num& n) {
	if (n.type == INT) os << n.dat.int_val;
	else if (n.type == DOUBLE) os << n.dat.double_val;
	else os << n.dat.f_val;
	return os;
}