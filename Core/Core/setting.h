#pragma once


#define EPS (1e-6)


typedef enum { DOUBLE, INT, FRACTION } NumType;


typedef enum { NUM, OPR } NODETYPE;
static const int TYPENUM = 2;


typedef enum { ADD, SUB, MUL, DIV, POW } OPRTYPE;
static const int OPRNUM = 5;


typedef struct Setting {

	int num_max = 1000;
	// maximum of num
	int num_limit = 20;
	// limit of nums
	int exp_num = 5;
	// number of expressions
	NumType type = DOUBLE;
	// type of number
	int precision = 2;
	// precision of double
	int pow_max = 5;
	// max power exp
	bool opr[OPRNUM] = { true, true, true, true, false };
	// available opr
	int opr_num = 4;
	// number of available opr
	bool power_signal = true;
	// way to show power: true -> '^', false -> '**'
	int min_depth = 1;
	int max_depth = 10;

} Setting;


extern Setting setting;