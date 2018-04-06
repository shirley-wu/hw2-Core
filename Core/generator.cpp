#include <iostream>
#include <assert.h>
#include <sstream>

#include "generator.h"

using namespace std;


Node * Generator::generate_tree(int limit, bool num_en) {
	Node * p;
	NODETYPE type;
	if (limit == 1) type = NUM;
	else if (num_en == false) type = OPR;
	else type = NODETYPE(rand() % TYPENUM);

	if (type == NUM) {
		Num val = Num::randomNum(setting.type, setting.num_max, setting.precision);
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

			if (p->calc_val(setting.num_max)) break;
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


bool Generator::get_exp(int i, string& s, Num& result) {
	if (i < 0 || (unsigned)i >= arr.size()) return false;
	Node * t = arr[i];
	if (to_expression(t, s) == false) return false;
	result = t->get_val();
	if (result < 0.0) {
		cin.get();
	}
	return true;
}