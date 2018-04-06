#pragma once

#include <string>
#include <vector>

#include "num.h"



typedef enum { NUM, OPR } NODETYPE;
const int TYPENUM = 2;

typedef enum { ADD, SUB, MUL, DIV } OPRTYPE;
const int OPRNUM = 4;


class Node {

private:
	NODETYPE type;
	union node_dat {
		Num num;
		OPRTYPE opr;
		node_dat() { }
	} dat;
	Num val = 0;
	bool calculated = false;
	Node * lchild = NULL;
	Node * rchild = NULL;

public:
	Node(Num num) { type = NUM; dat.num = num; }
	Node(OPRTYPE opr) { type = OPR; dat.opr = opr; }
	~Node() {
		if(lchild) delete lchild;
		if(rchild) delete rchild;
	}

	void set_lchild(Node * p) { lchild = p; calculated = false; }
	void set_rchild(Node * p) { rchild = p; calculated = false; }

	bool calc_val();
	Num get_val();

	friend bool equal(const Node * t1, const Node * t2);
	friend bool to_expression(const Node * p, std::string& s);

} ;


typedef struct Setting {
	int num_max   = 1000;
	int num_limit = 20;
	int exp_num   = 5;
	NumType type  = DOUBLE;

	void set(int mv, int lv, int ev, NumType tv) {
		num_max = mv; num_limit = lv; exp_num = ev; type = tv;
	}
} Setting;


class Generator {

private:
	Setting setting;
	std::vector<Node *> arr; // #TODO: vector may be too slow

	Node * generate_tree(int limit, bool num_en = true);

public:
	void set(int num_max, int num_limit, int exp_num, NumType type = DOUBLE) {
		setting.set(num_max, num_limit, exp_num, type);
	}
	bool generate();
	bool get_exp(int i, std::string& s, Num& result);

};