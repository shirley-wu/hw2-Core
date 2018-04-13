#pragma once

#include <string>
#include <vector>

#include "setting.h"
#include "fraction.h"



class Node {

private:
	NODETYPE nodetype;

	OPRTYPE opr;

	NumType numtype;
	int ival;
	double dval;
	Fraction fval;

	bool calculated = false;
	Node * lchild = NULL;
	Node * rchild = NULL;

public:
	Node() { }
	Node(int v) {
		nodetype = NUM;
		numtype = INT;
		ival = v;
	}
	Node(double v) {
		nodetype = NUM;
		numtype = DOUBLE;
		dval = v;
	}
	Node(OPRTYPE ov) {
		nodetype = OPR;
		opr = ov;
	}
	~Node() {
		if(lchild) delete lchild;
		if(rchild) delete rchild;
	}

	static Node * randNum();

	void set_lchild(Node * p) {
		if (lchild != NULL) delete lchild;
		lchild = p; calculated = false;
	}
	void set_rchild(Node * p) {
		if (rchild != NULL) delete rchild;
		rchild = p; calculated = false;
	}
	void exchange_lr() {
		Node * tmp;
		tmp = lchild;
		lchild = rchild;
		rchild = tmp;
	}

	void calc_val();

	friend bool equal(const Node * t1, const Node * t2);

	friend void to_expression(Node * p, std::string& s);
	friend void to_answer(Node * p, std::string& s);

	friend int to_expression(Node * t, char *s, int start, int end);
	friend int to_answer(Node * p, char *s, int start, int end);

} ;
