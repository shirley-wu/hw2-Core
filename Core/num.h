#pragma once


class Fraction {

private:
	int numer = 0;
	int denom = 1;

public:
	Fraction(int nv, int dv) { numer = nv; denom = dv; }
	Fraction(int iv, int nv, int dv) { denom = dv; numer = nv + iv * denom; }
	operator double() const;
	Fraction operator+(const Fraction& f) const;
	Fraction operator-(const Fraction& f) const;
	Fraction operator*(const Fraction& f) const;
	Fraction operator/(const Fraction& f) const;
	Fraction operator^(int exp) const;

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