#include <iostream>
#include <assert.h>
#include <sstream>
#include <vector>

#include "Exception.h"
#include "node.h"

#define GENERATOR_DLL_IMPLEMENT
#include "generator.h"

using namespace std;


typedef struct Setting {

	int num_max = 1000;
	int num_limit = 20;
	int exp_num = 5;
	NumType type = DOUBLE;
	int precision = 2;

} Setting;


Setting setting;
std::vector<Node *> arr;

Node * generate_tree(int limit, bool root, Num val);


NumType int_to_type(int type) {
	switch (type) {
	case 0:
		return DOUBLE;
	case 1:
		return INT;
	case 2:
		return FRACTION;
	default:
		throw(NumTypeError());
	}
}


void set(int num_max, int num_limit, int exp_num, int type, int precision) {
	setting.num_max = num_max;
	setting.num_limit = num_limit;
	setting.exp_num = exp_num;
	setting.type = int_to_type(type);
	setting.precision = precision;
}


bool generate() {
	clear();
	for (int i = 0; i < setting.exp_num; i++) {
		Node * p = generate_tree(setting.num_limit, true, Num());
		bool unique;
		while (1) {
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
				p = generate_tree(setting.num_limit, true, Num());
			}
		}
		arr.push_back(p);
	}
	return true;
}


void clear() {
	if (arr.size() > 0) {
		for (unsigned i = 0; i < arr.size(); i++) {
			delete arr[i];
		}
		arr.clear();
	}
}


bool get_exp(int i, string& s, string& result) {
	if (i < 0 || (unsigned)i >= arr.size()) return false;
	Node * t = arr[i];
	if (to_answer(t, s, result) == false) return false;
	return true;
}


Node * generate_tree(int limit, bool root, Num val) {
	Node * p;
	NODETYPE type;
	if (root == true) {
		type = OPR;
		if (setting.type == INT) {
			val = Num(limit);
		}
		else if (setting.type == DOUBLE) {
			val = Num((double)limit);
		}
		else {
			val = Num(Fraction(limit));
		}
	}
	else if (limit == 1) type = NUM;
	else type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
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

		while (true) {
			try {
				if (opr == ADD) {
					Num vl = Num::randomNum(setting.type, (double)val, setting.precision);
					Num vr = val - vl;
					p->set_lchild(generate_tree(limit1, false, vl));
					p->set_rchild(generate_tree(limit2, false, vr));
				}
				else if (opr == SUB) {
					Num vl = Num::randomNum(setting.type, (double)val, setting.precision);
					Num vr = Num::randomNum(setting.type, (double)vl, setting.precision);
					p->set_lchild(generate_tree(limit1, false, vl));
					p->set_rchild(generate_tree(limit2, false, vr));
				}
				else if (opr == MUL) {
					Num vl = Num::randomNum(setting.type, (double)val, setting.precision);
					Num vr = val / vl;
					p->set_lchild(generate_tree(limit1, false, vl));
					p->set_rchild(generate_tree(limit2, false, vr));
				}
				else if (opr == DIV) {
					if (setting.type == INT) {
						int denom = rand() % (setting.num_max - 1) + 1;
						int numer = (rand() % (setting.num_max / denom) + 1) * denom;
						p->set_lchild(generate_tree(limit1, false, Num(numer)));
						p->set_rchild(generate_tree(limit1, false, Num(denom)));
					}
					else {
						Num vl = Num::randomNum(setting.type, (double)val, setting.precision);
						Num vr = Num::randomNum(setting.type, (double)val, setting.precision);
						p->set_lchild(generate_tree(limit1, false, vl));
						p->set_rchild(generate_tree(limit2, false, vr));
					}
				}
				p->calc_val(setting.num_max);
			}
			catch (...) {
				throw;
			}
			break;
		}
	}

	return p;
}