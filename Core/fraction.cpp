#include <iostream>
#include <cmath>

#include "fraction.h"

using namespace std;


int gcd(int a, int b) {
	// greatest common divisor
	if (a < b) {
		int tmp = a;
		a = b;
		b = tmp;
	}
	while (b > 0) {
		int tmp = a % b;
		a = b;
		b = tmp;
	}
	return a;
}


int lcm(int a, int b) {
	// least common multiple
	int g = gcd(a, b);
	return a / g * b;
}


Fraction::operator double() const {
	if (denom != 0) return (double)numer / denom;
	else {
		cout << "problem!" << endl;
		return 0;
	}
}


Fraction Fraction::operator+(const Fraction& f) const {
	// TODO: can be quicker
	int nv, dv;
	dv = lcm(denom, f.denom);
	nv = dv / denom * numer + dv / f.denom * f.numer;

	if (nv == 0) dv = 1;
	else {
		int g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator-(const Fraction& f) const {
	// TODO: can be quicker
	int nv, dv;
	dv = lcm(denom, f.denom);
	nv = dv / denom * numer - dv / f.denom * f.numer;

	if (nv == 0) dv = 1;
	else {
		int g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator*(const Fraction& f) const {
	// TODO: can be quicker
	int nv, dv;
	dv = denom * f.denom;
	nv = numer * f.numer;

	if (nv == 0) dv = 1;
	else {
		int g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator/(const Fraction& f) const {
	// TODO: can be quicker
	int nv, dv;
	dv = denom * f.numer;
	nv = numer * f.denom;

	if (nv == 0) dv = 1;
	else {
		int g = gcd(nv, dv);
		nv /= g;
		dv /= g;
	}

	return Fraction(nv, dv);
}


Fraction Fraction::operator^(int exp) const {
	int nv = (int)pow(numer, exp);
	int dv = (int)pow(denom, exp);
	return Fraction(nv, dv);
}


bool Fraction::operator==(const Fraction& f) const {
	return numer == f.numer && denom == f.denom;
}


ostream& operator<<(ostream& os, const Fraction& f) {
	if (f.denom == 1) {
		os << f.numer << endl;
	}
	else {
		os << f.numer << '/' << f.denom;
	}
	return os;
}