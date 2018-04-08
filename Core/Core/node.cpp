#include <iostream>
#include <assert.h>
#include <sstream>
#include<iomanip> 

#include "exception.h"
#include "node.h"

using namespace std;


Node* Node::randNum(NumType type, int num_max) {
	Node * p = NULL;
	if (type == INT) {
		p = new Node(rand() % num_max);
	}
	else if (type == DOUBLE) {
		int base = pow(10, setting.precision);
		int real_max = base * num_max;
		int val = rand() % real_max;
		double real_val = (double)val / base;
		p = new Node(real_val);
	}
	else if (type == FRACTION) {
		p = new Node(Fraction(rand() % num_max));
	}
	return p;
}


void Node::calc_val() {
	if (calculated) return ;
	if (nodetype == NUM) {
		assert(lchild == NULL);
		assert(rchild == NULL);
	}
	else {
		assert(lchild != NULL);
		assert(rchild != NULL);
		lchild->calc_val();
		rchild->calc_val();
		if (opr == ADD) {
			assert(lchild->numtype == rchild->numtype);
			numtype = lchild->numtype;
			if (numtype == INT) {
				ival = lchild->ival + rchild->ival;
				if (ival < INT_MIN || ival > INT_MAX) throw(Overflow());
			}
			else if (numtype == DOUBLE) {
				dval = lchild->dval + rchild->dval;
				if (dval < DBL_MIN || dval > DBL_MAX) throw(Overflow());
			}
			else {
				add(lchild->fval, rchild->fval, fval);
			}
		}
		else if (opr == SUB) {
			assert(lchild->numtype == rchild->numtype);
			numtype = lchild->numtype;
			if (numtype == INT) {
				ival = lchild->ival - rchild->ival;
				if (ival < 0) throw(Negerror());
			}
			else if (numtype == DOUBLE) {
				dval = lchild->dval + rchild->dval;
				if (dval < 0) throw(Negerror());
			}
			else {
				sub(lchild->fval, rchild->fval, fval);
			}
		}
		else if (opr == MUL) {
			assert(lchild->numtype == rchild->numtype);
			numtype = lchild->numtype;
			if (numtype == INT) {
				ival = lchild->ival * rchild->ival;
				if (ival < INT_MIN || ival > INT_MAX) throw(Overflow());
			}
			else if (numtype == DOUBLE) {
				dval = lchild->dval * rchild->dval;
				if (dval < DBL_MIN || dval > DBL_MAX) throw(Overflow());
			}
			else {
				mul(lchild->fval, rchild->fval, fval);
			}
		}
		else if (opr == DIV) {
			assert(lchild->numtype == rchild->numtype);
			numtype = lchild->numtype;
			if (numtype == INT) {
				if (rchild->ival == 0) throw(Zeroerror());
				if (lchild->ival % rchild->ival != 0) throw(Exaerror());
				ival = lchild->ival / rchild->ival;
			}
			else if (numtype == DOUBLE) {
				dval = lchild->dval + rchild->dval;
				if (dval < DBL_MIN || dval > DBL_MAX) throw(Overflow());
			}
			else {
				div(lchild->fval, rchild->fval, fval);
			}
		}
	}
	calculated = true;
}


bool equal(const Node * t1, const Node * t2) {
	if (t1 == NULL && t2 == NULL) return true;
	else if (t1 == NULL || t2 == NULL) return false;
	else if (t1->nodetype != t2->nodetype) return false;
	else if (t1->nodetype == NUM) {
		if (t1->numtype != t2->numtype) return false;
		if (t1->numtype == INT) return t1->ival == t2->ival;
		else if (t1->numtype == DOUBLE) return t1->dval == t2->dval;
		else return t1->fval == t2->fval;
	}
	else {
		if (t1->opr != t2->opr) return false;
		if (equal(t1->lchild, t2->lchild) && equal(t1->rchild, t2->rchild)) return true;
		if ((t1->opr == ADD || t1->opr == MUL) && (equal(t1->lchild, t2->rchild) && equal(t1->rchild, t2->lchild))) return true;
		return false;
	}
}


int prior(OPRTYPE type) {
	if (type == ADD || type == SUB) return 1;
	else if (type == MUL || type == DIV) return 2;
	else return -1;
}


void to_expression(Node * t, string& s) {
	stringstream is;
	if (t->nodetype == NUM) {
		to_answer(t, s);
	}
	else {
		string child;

		to_expression(t->lchild, child);
		if (t->lchild->nodetype == OPR && prior(t->lchild->opr) < prior(t->opr)) {
			is << "(" << child << ")";
		}
		else is << child;

		string c;
		if (t->opr == ADD) c = "+";
		else if (t->opr == SUB) c = "-";
		else if (t->opr == MUL) c = "*";
		else if (t->opr == DIV) c = "/";
		else if (t->opr == POW) c = "^";
		else c = '?';
		is << ' ' << c << ' ';

		to_expression(t->rchild, child);
		if (t->rchild->nodetype == OPR && prior(t->rchild->opr) <= prior(t->opr)) {
			is << '(' << child << ')';
		}
		else is << child;
	}
	getline(is, s);
}


void to_answer(Node * p, string& s) {
	if (p->calculated == false) p->calc_val();
	
	stringstream ir;
	if (p->numtype == INT) ir << p->ival;
	else if (p->numtype == DOUBLE) ir << setprecision(setting.precision) << p->dval;
	else ir << p->fval;
	getline(ir, s);
}