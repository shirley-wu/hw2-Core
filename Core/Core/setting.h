#pragma once


#define EPS (1e-6)


typedef enum { DOUBLE, INT, FRACTION } NumType;


typedef enum { NUM, OPR } NODETYPE;
static const int TYPENUM = 2;


typedef enum { ADD, SUB, MUL, DIV, POW } OPRTYPE;
static const int OPRNUM = 5;


typedef struct Setting {

	int num_max = 1000;
	int num_limit = 20;
	int exp_num = 5;
	NumType type = DOUBLE;
	int precision = 2;
	int pow_max = 5; // max power exp

} Setting;


extern Setting setting;