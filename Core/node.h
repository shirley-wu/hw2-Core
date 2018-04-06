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
