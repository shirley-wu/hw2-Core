#pragma once

#include <ostream>
#include <assert.h>


class Fraction {

private:
	int numer = 0;
	int denom = 1;

public:
	Fraction() { }
	Fraction(int nv, int dv) {
		assert(denom != 0);
		numer = nv;
		denom = dv;
	}
	operator double() const;
	Fraction operator+(const Fraction& f) const;
	Fraction operator-(const Fraction& f) const;
	Fraction operator*(const Fraction& f) const;
	Fraction operator/(const Fraction& f) const;
	Fraction operator^(int exp) const;
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

};


class Num {

private:
	enum {
		DOUBLE, INT, PROPER_FRACTION
	} attrib;
	union {
		double double_val;
		int int_val;
		Fraction pf_val;
	};

public:

};