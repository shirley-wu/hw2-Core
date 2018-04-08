#include <iostream>
#include <assert.h>
#include <sstream>
#include <vector>

#include "exception.h"
#include "node.h"
#include "setting.h"

#define GENERATOR_DLL_IMPLEMENT
#include "generator.h"

using namespace std;


std::vector<Node *> arr;
Setting setting;


Node * generate_tree(int limit, bool num_en = true);


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


void generate() {
	clear();
	for (int i = 0; i < setting.exp_num; i++) {
		Node * p = generate_tree(setting.num_limit, false);
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
				p = generate_tree(setting.num_limit, false);
			}
		}
		arr.push_back(p);
	}
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
	to_expression(t, s);
	to_answer(t, result);
	return true;
}


Node * generate_tree(int limit, bool num_en) {
	Node * p;
	NODETYPE type;
	if (limit == 1) type = NUM;
	else if (num_en == false) type = OPR;
	else type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
		p = Node::randNum(setting.type, setting.num_max);
	}
	else {
		int v = rand() % OPRNUM;
		OPRTYPE opr = OPRTYPE(v);
		p = new Node(opr);

		if (setting.type == INT && opr == DIV) {
			int denom = rand() % (setting.num_max - 1) + 1;
			int numer = (rand() % (setting.num_max / denom) + 1) * denom;
			Node *pl = new Node(numer);
			Node *pr = new Node(denom);
			p->set_lchild(pl);
			p->set_rchild(pr);
			p->calc_val();
		}
		else {
			int limit1, limit2;
			if (limit == 2) limit1 = limit2 = 1;
			else {
				limit1 = (rand() % (limit - 2)) + 1;
				limit2 = limit - limit1;
			}

			if (opr == POW) {
				int v = rand() % setting.pow_max;
				p->set_lchild(generate_tree(limit1));
				p->set_rchild(Node::randNum(INT, v));

				while (true) {
					try {
						p->calc_val();
					}
					catch (Overflow& e) {
						v /= 2;
						p->set_rchild(Node::randNum(INT, v));
						continue;
					}
					catch (...) {
						throw;
					}
					break;
				}
			}
			else {
				p->set_lchild(generate_tree(limit1));
				p->set_rchild(generate_tree(limit2));

				while (true) {
					try {
						p->calc_val();
					}
					catch (Overflow& e) {
						p->set_lchild(generate_tree(limit1));
						p->set_rchild(generate_tree(limit2));
						continue;
					}
					catch (Zeroerror& e) {
						p->set_lchild(generate_tree(limit1));
						p->set_rchild(generate_tree(limit2));
						continue;
					}
					catch (Negerror& e) {
						p->exchange_lr();
						continue;
					}
					catch (Exaerror& e) {
						p->set_lchild(generate_tree(limit1));
						p->set_rchild(generate_tree(limit2));
						continue;
					}
					catch (...) {
						throw;
					}
					break;
				}
			}
		}

	}

	return p;
}