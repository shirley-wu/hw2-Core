#include <iostream>
#include <cmath>

#include "exception.h"
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


void Fraction::adjust() {
	if (numer == 0) denom = 1;
	else {
		long long g = gcd(numer, denom);
		numer /= g;
		denom /= g;
	}
}


void add(const Fraction& f1, const Fraction& f2, Fraction& f) {
	// TODO: can be quicker
	f.denom = lcm(f1.denom, f2.denom);
	if (f.denom < 0) throw(Overflow());
	else if (f.denom == 0) throw(Zeroerror());

	f.numer = f.denom / f1.denom * f1.numer + f.denom / f2.denom * f2.numer;
	if (f.numer < 0) throw(Overflow());

	f.adjust();
}


void sub(const Fraction& f1, const Fraction& f2, Fraction& f) {
	// TODO: can be quicker
	f.denom = lcm(f1.denom, f2.denom);
	if (f.denom < 0) throw(Overflow());
	else if (f.denom == 0) throw(Zeroerror());

	f.numer = f.denom / f1.denom * f1.numer - f.denom / f2.denom * f2.numer;
	if(f.numer < 0) throw(Negerror());

	f.adjust();
}


void mul(const Fraction& f1, const Fraction& f2, Fraction& f) {
	// TODO: can be quicker
	f.denom = f1.denom * f2.denom;
	if (f.denom < 0) throw(Overflow());
	else if (f.denom == 0) throw(Zeroerror());

	f.numer = f1.numer * f2.numer;
	if (f.numer < 0) throw(Overflow());

	f.adjust();
}


void div(const Fraction& f1, const Fraction& f2, Fraction& f) {
	// TODO: can be quicker
	f.denom = f1.denom * f2.numer;
	if (f.denom < 0) throw(Overflow());
	else if (f.denom == 0) throw(Zeroerror());

	f.numer = f1.numer * f2.denom;
	if (f.numer < 0) throw(Overflow());

	f.adjust();
}


void pow(const Fraction& f1, int p, Fraction& f) {
	f.numer = (long long)pow(f1.numer, p);
	if (f.numer < 0) throw(Overflow());

	f.denom = (long long)pow(f1.denom, p);
	if (f.denom < 0) throw(Overflow());

    f.adjust();
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


int Fraction::to_str(char * s, int start, int end) const {
	int k;
	int size = end - start;

	k = snprintf(s + start, size, "%lld", numer);
	if (k > size) throw(Overlength());
	else start += k;

	if (denom != 1) {
		s[start++] = '/';
		if (start >= end) throw(Overlength());

		k = snprintf(s + start, size, "%lld", denom);
		if (k > size) throw(Overlength());
		else start += k;
	}

	s[start] = 0;
	return start;
}