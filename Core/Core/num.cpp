#include <iostream>
#include <cmath>
#include "Exception.h"
#include "num.h"
#include "node.h"

using namespace std;



Num::operator double() const {
	if (type == DOUBLE) return dat.double_val;
	else if (type == INT) return (double)dat.int_val;
	else return (double)dat.f_val;
}


Num Num::operator+(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		if (Num((double)(*this) + (double)f) < 0) {
			throw(Overflow());
		}
		else return Num((double)(*this) + (double)f);
	}
	else if (type == INT) {
		if (Num(dat.int_val + f.dat.int_val)<0) {
			throw(Overflow());
		}
		else return Num(dat.int_val + f.dat.int_val);
	}
	else {
		if (Num(dat.f_val + f.dat.f_val)<0) {
			throw(Overflow());
		}
		else return Num(dat.f_val + f.dat.f_val);
	}
}


Num Num::operator-(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		if (Num((double)(*this) - (double)f) < 0) {
			throw(Negerror());
		}
		else return Num((double)(*this) - (double)f);
	}
	else if (type == INT) {
		if (Num(dat.int_val - f.dat.int_val) < 0) {
			throw(Negerror());
		}
		else return Num(dat.int_val - f.dat.int_val);
	}
	else {
		if (Num(dat.f_val - f.dat.f_val) < 0) {
			throw(Negerror());
		}
		else return Num(dat.f_val - f.dat.f_val);
	}
}


Num Num::operator*(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		if (Num((double)(*this) * (double)f) < 0) {
			throw(Overflow());
		}
		else return Num((double)(*this) * (double)f);
	}
	else if (type == INT) {
		if (Num(dat.int_val * f.dat.int_val) < 0) {
			throw(Overflow());
		}
		else return Num(dat.int_val * f.dat.int_val);
	}
	else {
		if (Num(dat.f_val * f.dat.f_val) < 0) {
			throw(Overflow());
		}
		else return Num(dat.f_val * f.dat.f_val);
	}
}


Num Num::operator/(const Num& f) const {
	if (type != f.type || type == DOUBLE) {
		if ((double)f == 0) {
			throw(Zeroerror());
		}
		else return Num((double)(*this) / (double)f);
	}
	else if (type == INT) {
		if (f.dat.int_val == 0) { 
			throw(Zeroerror()); 
		}
		// else if (dat.int_val%f.dat.int_val != 0) {
		// 	throw(Exaerror());
		// }
		else return Num(dat.int_val / f.dat.int_val);
	}
	else {
		if ((double)f.dat.f_val == 0) { throw(Zeroerror()); }
		else return Num(dat.f_val / f.dat.f_val);
	}
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


bool Num::operator==(double w) const {
	return fabs((double)(*this) - w) < EPS;
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
		int real_limit = (int)base * limit;
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
		return Num(Fraction(val, 1));
	}
}