#pragma once

#include <ostream>
#include <assert.h>


class Fraction {

private:
	long long numer = 0;
	long long denom = 1;

public:
	Fraction() { }
	Fraction(long long nv) {
		numer = nv;
		denom = 1;
	}
	Fraction(long long nv, long long dv) {
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
	bool operator==(const Fraction& f) const;
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

};