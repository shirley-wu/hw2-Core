#pragma once

#include <assert.h>
#include <ostream>

#include "fraction.h"


typedef enum { DOUBLE, INT, FRACTION } NumType;


class Num {

private:
	NumType type;
	struct {
		double double_val;
		int int_val;
		Fraction f_val;
	} dat;

public:
	operator double() const;
	Num() { type = DOUBLE; dat.double_val = 0; }
	Num(double v) { type = DOUBLE; dat.double_val = v; }
	Num(int v) { type = INT;  dat.int_val = v; }
	Num(int nv, int dv) { type = FRACTION; dat.f_val = Fraction(nv, dv); }
	Num(Fraction f) { type = FRACTION; dat.f_val = f; }
	Num operator+(const Num& f) const;
	Num operator-(const Num& f) const;
	Num operator*(const Num& f) const;
	Num operator/(const Num& f) const;
	friend std::ostream& operator<<(std::ostream& os, const Num& n);

};