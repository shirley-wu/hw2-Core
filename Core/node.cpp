#include <iostream>
#include <assert.h>
#include <sstream>
#include "Exception.h"

#include "node.h"

using namespace std;


void Node::calc_val(double limit) {
	if (calculated) return ;
	if (type == NUM) {
		assert(lchild == NULL);
		assert(rchild == NULL);
		val = dat.num;
	}
	else if (type == OPR) {
		assert(lchild != NULL);
		assert(rchild != NULL);
		Num lval = lchild->get_val(), rval = rchild->get_val(), fval;
		if (dat.opr == ADD) {
			fval = lval + rval;
		}
		else if (dat.opr == SUB) {
			fval = lval - rval;
		}
		else if (dat.opr == MUL) {
			fval = lval * rval;
		}
		else if (dat.opr == DIV) {
			fval = lval / rval;
		}
		if (limit > 0 && fval > limit) {
			throw(Overflow());
		}
		val = fval;
	}
	calculated = true;
}


Num Node::get_val() {
	// assert(calculated);
	if(!calculated) calc_val();
	return val;
}


bool equal(const Node * t1, const Node * t2) {
	if (t1 == NULL && t2 == NULL) return true;
	else if (t1 == NULL || t2 == NULL) return false;
	else if (t1->type != t2->type) return false;
	else if (t1->type == NUM) {
		return t1->dat.num == t2->dat.num;
	}
	else {
		if (t1->dat.opr != t2->dat.opr) return false;
		if (equal(t1->lchild, t2->lchild) && equal(t1->rchild, t2->rchild)) return true;
		if ((t1->dat.opr == ADD || t1->dat.opr == MUL) && (equal(t1->lchild, t2->rchild) && equal(t1->rchild, t2->lchild))) return true;
		return false;
	}
}


int prior(OPRTYPE type) {
	if (type == ADD || type == SUB) return 1;
	else if (type == MUL || type == DIV) return 2;
	else return -1;
}


bool to_expression(Node * t, string& s) {
	stringstream is;
	if (t->type == NUM) {
		is << t->dat.num;
	}
	else {
		string child;
		bool status;

		status = to_expression(t->lchild, child);
		if (status == false) return false;
		if (t->lchild->type == OPR && prior(t->lchild->dat.opr) < prior(t->dat.opr)) {
			is << "(" << child << ")";
		}
		else is << child;

		char c;
		if (t->dat.opr == ADD) c = '+';
		else if (t->dat.opr == SUB) c = '-';
		else if (t->dat.opr == MUL) c = '*';
		else if (t->dat.opr == DIV) c = '/';
		else c = '?';
		is << ' ' << c << ' ';

		status = to_expression(t->rchild, child);
		if (status == false) return false;
		if (t->rchild->type == OPR && prior(t->rchild->dat.opr) <= prior(t->dat.opr)) {
			is << '(' << child << ')';
		}
		else is << child;
	}
	getline(is, s);
	return true;
}


bool to_answer(Node * p, string& s, string& result) {
	bool status;
	status = to_expression(p, s);
	if (status == false) return false;
	
	stringstream ir;
	ir << p->get_val();
	getline(ir, result);
	
	return true;
}