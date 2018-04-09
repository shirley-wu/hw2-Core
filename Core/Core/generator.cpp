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
Node * create_int_node(int a);


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
			p->set_lchild(create_int_node(numer));
			p->set_rchild(create_int_node(denom));
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
				int v = rand() % 5;
				p->set_lchild(generate_tree(limit1));
				p->set_rchild(create_int_node(v));

				while (true) {
					try {
						p->calc_val();
					}
					catch (Overflow& e) {
						v--;
						p->set_rchild(create_int_node(v));
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


Node * create_int_node(int a) {
	if (a < 0) throw(Negerror());

	Node *p = NULL;
	NODETYPE type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
		p = new Node(a);
	}
	else {
		OPRTYPE tool;
		if (a == 0) tool = SUB;
		else tool = (rand() % 2) == 0 ? ADD : SUB;
		int lchnum, rchnum;

		if (tool == ADD) {
			lchnum = rand() % a;
			rchnum = a - lchnum;
			p = new Node(ADD);
			p->set_lchild(create_int_node(lchnum));
			p->set_rchild(create_int_node(rchnum));
			p->calc_val();
		}
		else {
			rchnum = rand() % (setting.num_max - a);
			lchnum = a + rchnum;
			p = new Node(SUB);
			p->set_lchild(create_int_node(lchnum));
			p->set_rchild(create_int_node(rchnum));
			p->calc_val();
		}
	}
	return p;
}