#include <iostream>
#include <cmath>
#include "Exception.h"
#include "fraction.h"

using namespace std;


long long gcd(long long a, long long b) {
	// greatest common divisor
	if (a < b) {
		long long tmp = a;
		a = b;
		b = tmp;
	}
	while (b > 0) {
		long long tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}


long long lcm(long long a, long long b) {
	// least common multiple
	long long g = gcd(a, b);
	return a / g * b;
}


Fraction::operator double() const {
	if (denom != 0) return (double)numer / denom;
	else {
		/*cout << "problem!" << endl;
		return 0;*/
		throw(Zeroerror());
	}
}


Fraction Fraction::operator+(const Fraction& f) const {
	// TODO: can be quicker
	long long nv, dv;
	dv = lcm(denom, f.denom);
	nv = dv / denom * numer + dv / f.denom * f.numer;

	if (nv == 0) dv = 1;
	else if (nv < 0 || dv < 0) {
		throw(Overflow());
	}
	else if (dv == 0) {
		throw(Zeroerror());
	}
	else {
		long long g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator-(const Fraction& f) const {
	// TODO: can be quicker
	long long nv, dv;
	dv = lcm(denom, f.denom);
	nv = dv / denom * numer - dv / f.denom * f.numer;

	if (nv == 0) dv = 1;
	else if (nv < 0) {
		throw(Negerror());
	}
	else if (dv == 0) {
		throw(Zeroerror());
	}
	else {
		long long g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator*(const Fraction& f) const {
	// TODO: can be quicker
	long long nv, dv;
	dv = denom * f.denom;
	nv = numer * f.numer;

	if (nv == 0) dv = 1;
	else if (nv < 0 || dv < 0) {
		throw(Overflow());
	}
	else if (dv == 0) {
		throw(Zeroerror());
	}
	else {
		long long g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator/(const Fraction& f) const {
	// TODO: can be quicker
	long long nv, dv;
	dv = denom * f.numer;
	nv = numer * f.denom;

	if (nv == 0) dv = 1;
	else if (dv == 0) {
		throw(Zeroerror());
	}
	else if (nv < 0 || dv < 0) {
		throw(Overflow());
	}
	else {
		long long g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator^(int exp) const {
	int nv = (int)pow(numer, exp);
	int dv = (int)pow(denom, exp);
    if (nv < 0 || dv < 0) {
		throw(Overflow());
	}
	else return Fraction(nv, dv);
}


bool Fraction::operator==(const Fraction& f) const {
	return numer == f.numer && denom == f.denom;
}


ostream& operator<<(ostream& os, const Fraction& f) {
	if (f.denom == 1) {
		os << f.numer;
	}
	else {
		os << f.numer << '/' << f.denom;
	}
	return os;
}