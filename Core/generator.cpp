#include <iostream>
#include <assert.h>
#include <sstream>

#include "generator.h"

using namespace std;


bool Node::calc_val() {
	if (calculated) return true;
	if (type == NUM) {
		assert(lchild == NULL);
		assert(rchild == NULL);
		val = dat.num;
	}
	else if (type == OPR) {
		assert(lchild != NULL);
		assert(rchild != NULL);
		NUMTYPE lval = lchild->get_val(), rval = rchild->get_val();
		if (dat.opr == ADD) {
			val = lval + rval;
		}
		else if (dat.opr == SUB) {
			if (lval < rval) return false;
			val = lval - rval;
		}
		else if (dat.opr == MUL) {
			val = lval * rval;
		}
		else if (dat.opr == DIV) {
			if (rval == 0) return false;
			val = lval / rval;
		}
	}
	calculated = true;
	return true;
}


NUMTYPE Node::get_val() {
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


bool to_expression(const Node * t, string& s) {
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
			is << '(' << child << ')';
		}
		else is << child;

		char c;
		if (t->dat.opr == ADD) c = '+';
		else if (t->dat.opr == SUB) c = '-';
		else if (t->dat.opr == MUL) c = '*';
		else if (t->dat.opr == DIV) c = '/';
		else c = '?';
		is << c;

		status = to_expression(t->rchild, child);
		if (status == false) return false;
		if (t->rchild->type == OPR && prior(t->rchild->dat.opr) <= prior(t->dat.opr)) {
			is << '(' << child << ')';
		}
		else is << child;
	}
	is >> s;
	return true;
}


Node * Generator::generate_tree(int limit, bool num_en) {
	Node * p;
	NODETYPE type;
	if (limit == 1) type = NUM;
	else if (num_en == false) type = OPR;
	else type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
		NUMTYPE val = rand() % setting.num_max;
		p = new Node(val);
	}
	else {
		OPRTYPE opr = OPRTYPE(rand() % OPRNUM);
		p = new Node(opr);

		int limit1, limit2;
		if (limit == 2) limit1 = limit2 = 1;
		else {
			limit1 = (rand() % (limit - 2)) + 1;
			limit2 = limit - limit1;
		}

		while(true) {
			Node *pl, *pr;
			pl = generate_tree(limit1);
			pr = generate_tree(limit2);
			p->set_lchild(pl);
			p->set_rchild(pr);

			if (p->calc_val()) break;
			else {
				delete pl;
				delete pr;
				// TODO: don't have to
			}
		}
	}

	return p;
}


bool Generator::generate() {
	arr.clear();
	for (int i = 0; i < setting.exp_num; i++) {
		Node * p = generate_tree(setting.num_limit, false);
		bool unique;
		while(1) {
			unique = true;
			for (int j = 0; j < i; j++) {
				if (equal(p, arr[j])) {
					unique = false;
					break;
				}
			}
			if (unique) break;
			else {
				delete p;
				p = generate_tree(setting.num_limit);
			}
		}
		arr.push_back(p);
	}
	return true;
}


bool Generator::get_exp(int i, string& s, NUMTYPE& result) {
	if (i < 0 || i >= arr.size()) return false;
	Node * t = arr[i];
	if (to_expression(t, s) == false) return false;
	result = t->get_val();
	return true;
}