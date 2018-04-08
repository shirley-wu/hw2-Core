#pragma once

#include <ostream>
#include <assert.h>


class Fraction {

private:
	long long numer = 0;
	long long denom = 1;

	void adjust();

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

	friend void add(const Fraction& f1, const Fraction& f2, Fraction& f);
	friend void sub(const Fraction& f1, const Fraction& f2, Fraction& f);
	friend void mul(const Fraction& f1, const Fraction& f2, Fraction& f);
	friend void div(const Fraction& f1, const Fraction& f2, Fraction& f);
	friend void pow(const Fraction& f1, int p, Fraction& f);

	bool operator==(const Fraction& f) const;
	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);

};