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

	void set_lchild(Node * p) {
		if (lchild != NULL) delete lchild;
		lchild = p; calculated = false;
	}
	void set_rchild(Node * p) {
		if (rchild != NULL) delete rchild;
		rchild = p; calculated = false;
	}
	void exchange_lr() {
		Node * tmp;
		tmp = lchild;
		lchild = rchild;
		rchild = tmp;
	}

	void calc_val(double limit = -1);
	Num get_val();

	friend bool equal(const Node * t1, const Node * t2);
	friend bool to_expression(Node * p, std::string& s);
	friend bool to_answer(Node * p, std::string& s, std::string& result);

} ;
