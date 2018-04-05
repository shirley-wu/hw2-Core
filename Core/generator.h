#pragma once

#include <string>
#include <vector>


typedef enum { NUM, OPR } NODETYPE;
const int TYPENUM = 2;

typedef double NUMTYPE;

typedef enum { ADD, SUB, MUL, DIV } OPRTYPE;
const int OPRNUM = 4;


class Node {

private:
	NODETYPE type;
	union {
		NUMTYPE num;
		OPRTYPE opr;
	} dat;
	NUMTYPE val = 0;
	bool calculated = false;
	Node * lchild = NULL;
	Node * rchild = NULL;

public:
	Node(NUMTYPE num) { type = NUM; dat.num = num; }
	Node(OPRTYPE opr) { type = OPR; dat.opr = opr; }
	~Node() {
		if(lchild) delete lchild;
		if(rchild) delete rchild;
	}

	void set_lchild(Node * p) { lchild = p; calculated = false; }
	void set_rchild(Node * p) { rchild = p; calculated = false; }

	bool calc_val();
	NUMTYPE get_val();

	friend bool equal(const Node * t1, const Node * t2);
	friend bool to_expression(const Node * p, std::string& s);

} ;


typedef struct Setting {
	int num_max   = 1000;
	int num_limit = 20;
	int exp_num   = 5;

	void set(int mv, int lv, int ev) {
		num_max = mv; num_limit = lv; exp_num = ev;
	}
} Setting;


class Generator {

private:
	Setting setting;
	std::vector<Node *> arr; // #TODO: vector may be too slow

	Node * generate_tree(int limit, bool num_en = true);

public:
	void set(int num_max, int num_limit, int exp_num) {
		setting.set(num_max, num_limit, exp_num);
	}
	bool generate();
	bool get_exp(int i, std::string& s, NUMTYPE& result);

};