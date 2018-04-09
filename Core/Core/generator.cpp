#include <iostream>
#include <assert.h>
#include <sstream>
#include <vector>

#include "exception.h"
#include "node.h"
#include "setting.h"

#ifndef CORE_DLL_IMPLEMENT
#define CORE_DLL_IMPLEMENT
#endif

#include "dll.h"

using namespace std;


std::vector<Node *> arr;


Node * generate_tree(int limit, int depth);
Node * create_int_node(int a, int limit_depth);
OPRTYPE randomopr();


void clear() {
	if (arr.size() > 0) {
		for (unsigned i = 0; i < arr.size(); i++) {
			delete arr[i];
		}
		arr.clear();
	}
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


bool get_exp(int i, string& s, string& result) {
	if (i < 0 || (unsigned)i >= arr.size()) return false;
	
	Node * t = arr[i];
	to_expression(t, s);
	to_answer(t, result);
	return true;
}


Node * generate_tree(int limit, int depth) {
	Node * p;
	NODETYPE type;
	if (limit == 1) {
		if (depth < setting.min_depth) throw("wtf");
		else type = NUM;
	}
	else if (depth == setting.max_depth) type = NUM;
	else if (depth < setting.min_depth) type = OPR;
	else type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
		p = Node::randNum();
	}
	else {
		int v = rand() % OPRNUM;
		OPRTYPE opr = randomopr();
		p = new Node(opr);

		if (setting.type == INT && opr == DIV) {
			int denom = rand() % (setting.num_max - 1) + 1;
			int numer = (rand() % (setting.num_max / denom) + 1) * denom;
			p->set_lchild(create_int_node(numer, setting.max_depth - depth));
			p->set_rchild(create_int_node(denom, setting.max_depth - depth));
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
				p->set_lchild(generate_tree(limit1, depth + 1));
				p->set_rchild(create_int_node(v, setting.max_depth - depth));

				while (true) {
					try {
						p->calc_val();
					}
					catch (Overflow& e) {
						v--;
						p->set_rchild(create_int_node(v, setting.max_depth - depth));
						continue;
					}
					catch (...) {
						throw;
					}
					break;
				}
			}
			else {
				p->set_lchild(generate_tree(limit1, depth + 1));
				p->set_rchild(generate_tree(limit2, depth + 1));

				while (true) {
					try {
						p->calc_val();
					}
					catch (Overflow& e) {
						p->set_lchild(generate_tree(limit1, depth + 1));
						p->set_rchild(generate_tree(limit2, depth + 1));
						continue;
					}
					catch (Zeroerror& e) {
						p->set_lchild(generate_tree(limit1, depth + 1));
						p->set_rchild(generate_tree(limit2, depth + 1));
						continue;
					}
					catch (Negerror& e) {
						p->exchange_lr();
						continue;
					}
					catch (Exaerror& e) {
						p->set_lchild(generate_tree(limit1, depth + 1));
						p->set_rchild(generate_tree(limit2, depth + 1));
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


Node * create_int_node(int a, int limit_depth) {
	if (a < 0) throw(Negerror());

	Node *p = NULL;
	NODETYPE type;
	OPRTYPE tool;

	if (limit_depth == 1 || (setting.opr[(int)SUB] == false && setting.opr[(int)ADD] == false)) {
		type = NUM;
	}
	else if (a == 0) {
		if (setting.opr[(int)SUB] == false) type = NUM;
		else {
			type = NODETYPE(rand() % TYPENUM);
			if (type == OPR) tool = SUB;
		}
	}
	else {
		type = NODETYPE(rand() % TYPENUM);
		if (type == OPR) {
			if (setting.opr[(int)SUB] == false) tool = ADD;
			else if (setting.opr[(int)ADD] == false) tool = SUB;
			else tool = (rand() % 2) == 0 ? ADD : SUB;
		}
	}
	

	if (type == NUM) {
		p = new Node(a);
	}
	else {
		int lchnum, rchnum;

		if (tool == ADD) {
			lchnum = rand() % a;
			rchnum = a - lchnum;
			p = new Node(ADD);
			p->set_lchild(create_int_node(lchnum, limit_depth - 1));
			p->set_rchild(create_int_node(rchnum, limit_depth - 1));
			p->calc_val();
		}
		else {
			rchnum = rand() % (setting.num_max - a);
			lchnum = a + rchnum;
			p = new Node(SUB);
			p->set_lchild(create_int_node(lchnum, limit_depth - 1));
			p->set_rchild(create_int_node(rchnum, limit_depth - 1));
			p->calc_val();
		}
	}
	return p;
}