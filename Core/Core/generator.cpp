#include <iostream>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>

#include "exception.h"
#include "node.h"
#include "setting.h"

#ifndef CORE_DLL_IMPLEMENT
#define CORE_DLL_IMPLEMENT
#endif

#include "dll.h"

using namespace std;


std::vector<Node *> arr;


Node * generate_tree(int limit, bool num_en = true);
Node * create_int_node(int a, int limit);
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
	srand((unsigned)time(0));
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


Node * generate_tree(int limit, bool num_en) {
	Node * p;
	NODETYPE type;
	if (limit == 1) {
		if (num_en == false) throw("wtf");
		else type = NUM;
	}
	else if (num_en == false) type = OPR;
	else type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
		p = Node::randNum();
	}
	else {
		int v = rand() % OPRNUM;
		OPRTYPE opr = randomopr();
		p = new Node(opr);

		int limit1, limit2;
		if (limit == 2) limit1 = limit2 = 1;
		else {
			limit1 = (rand() % (limit - 2)) + 1;
			limit2 = limit - limit1;
		}

		if (setting.type == INT && opr == DIV) {
			int denom = rand() % (setting.num_max - 1) + 1;
			int numer = (rand() % (setting.num_max / denom)) * denom;
			p->set_lchild(create_int_node(numer, limit1));
			p->set_rchild(create_int_node(denom, limit2));
			p->calc_val();
		}
		else {
			if (opr == POW) {
				int v = rand() % 5;
				p->set_lchild(generate_tree(limit1));
				p->set_rchild(create_int_node(v, limit2));

				while (true) {
					try {
						p->calc_val();
					}
					catch (Overflow& e) {
						v--;
						p->set_rchild(create_int_node(v, limit2));
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


Node * create_int_node(int a, int limit) {
	if (a < 0) throw(Negerror());

	Node *p = NULL;
	NODETYPE type;
	OPRTYPE tool;

	if (limit == 1 || (setting.opr[(int)SUB] == false && setting.opr[(int)ADD] == false)) {
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
		int limit1, limit2;
		if (limit == 2) limit1 = limit2 = 1;
		else {
			limit1 = (rand() % (limit - 2)) + 1;
			limit2 = limit - limit1;
		}

		int lchnum, rchnum;

		if (tool == ADD) {
			lchnum = rand() % a;
			rchnum = a - lchnum;
			p = new Node(ADD);
			p->set_lchild(create_int_node(lchnum, limit1));
			p->set_rchild(create_int_node(rchnum, limit2));
			p->calc_val();
		}
		else {
			rchnum = rand() % (setting.num_max - a);
			lchnum = a + rchnum;
			p = new Node(SUB);
			p->set_lchild(create_int_node(lchnum, limit1));
			p->set_rchild(create_int_node(rchnum, limit2));
			p->calc_val();
		}
	}
	return p;
}


bool get_exp(int i, string& s, string& result) {
	if (i < 0 || (unsigned)i >= arr.size()) return false;

	Node * t = arr[i];
	to_expression(t, s);
	to_answer(t, result);
	return true;
}


bool get_expression(int i, char *s, int size) {
	if (i < 0 || (unsigned)i >= arr.size()) return false;

	try {
		to_expression(arr[i], s, 0, size);
	}
	catch (Overlength& e) {
		return false;
	}

	return true;
}


bool get_answer(int i, char *s, int size) {
	if (i < 0 || (unsigned)i >= arr.size()) return false;

	try {
		to_answer(arr[i], s, 0, size);
	}
	catch (Overlength& e) {
		return false;
	}

	return true;
}


bool exp_to_file(const char* dir) {
	ofstream is (dir);
	if (is.fail()) return false;

	for (int i = 0; i < arr.size(); i++) {
		string s;
		to_expression(arr[i], s);
		is << s << endl;
	}
	is.close();

	return true;
}


bool ans_to_file(const char* dir) {
	ofstream is(dir);
	if (is.fail()) return false;

	for (int i = 0; i < arr.size(); i++) {
		string s;
		to_answer(arr[i], s);
		is << s << endl;
	}
	is.close();

	return true;
}
