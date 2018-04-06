#pragma once

#include <string>
#include <vector>

#include "node.h"


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