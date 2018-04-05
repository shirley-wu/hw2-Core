// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "cstdio"
#include "cstdlib"
#include "string"
#include "iostream"

using namespace std;


typedef struct code {//字符栈
	struct code *next;
	char data;
}stack, *sstack;
typedef struct num {//数字栈
	double data;
	struct num *next;
}Lnode, *Linklist;
void Init_code(sstack &s) {
	s = NULL;
	return;
}
void Init_num(Linklist &s) {
	s = NULL;
	return;
}
char gettop_code(stack *S) {
	char e;
	if (S == NULL) return '$';
	e = S->data;
	return e;
}
double gettop_num(Lnode *S) {
	double e;
	if (S == NULL) return 0;
	e = S->data;
	return e;
}
int stackempty(stack *S) {
	if (S == NULL) return 1;
	else return 0;
}
sstack push_code(sstack &S, char e) {
	sstack p;
	p = (sstack)malloc(sizeof(stack));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}
Linklist push_num(Linklist &S, double e) {
	Linklist p;
	p = (Linklist)malloc(sizeof(Lnode));
	p->data = e;
	p->next = S;
	S = p;
	return S;
}
sstack pop_code(sstack &S, char &e) {
	sstack p;
	if (S == NULL) {
		e ='@';
		return S;
	}
	e = S->data;
	p = S;
	S = S->next;
	free(p);
	return S;
}
Linklist pop_num(Linklist &S, double &e) {
	Linklist p;
	if (S == NULL) return S;
	e = S->data;
	p = S;
	S = S->next;
	free(p);
	return S;
}
char precede(char a, char b) {//判断操作符优先级
	if ((a == '+'&&b == '+') || (a == '+'&&b == '-') || (a == '+'&&b == ')') || (a == '+'&&b == '#') || (a == '-'&&b == '-') || (a == '-'&&b == '+') || (a == '-'&&b == ')') || (a == '-'&&b == '#') || (a == '*'&&b == '+') || (a == '*'&&b == '-') || (a == '*'&&b == '*') || (a == '*'&&b == '/') || (a == '*'&&b == ')') || (a == '*'&&b == '#') || (a == '/'&&b == '+') || (a == '/'&&b == '-') || (a == '/'&&b == '*') || (a == '/'&&b == '/') || (a == '/'&&b == ')') || (a == '/'&&b == '#') || (a == ')'&&b == '+') || (a == ')'&&b == '-') || (a == ')'&&b == '*') || (a == ')'&&b == '/') || (a == ')'&&b == ')') || (a == ')'&&b == '#') || (a == '^'&&b == '+') || (a == '^'&&b == '-') || (a == '^'&&b == '*') || (a == '^'&&b == ')') || (a == '^'&&b == '#') || (a == '^'&&b == '^') || (a == ')'&&b == '^')) return '>';
	if ((a == '+'&&b == '*') || (a == '+'&&b == '/') || (a == '+'&&b == '(') || (a == '-'&&b == '*') || (a == '-'&&b == '/') || (a == '-'&&b == '(') || (a == '*'&&b == '(') || (a == '/'&&b == '(') || (a == '('&&b == '+') || (a == '('&&b == '-') || (a == '('&&b == '*') || (a == '('&&b == '/') || (a == '('&&b == '(') || (a == '#'&&b == '+') || (a == '#'&&b == '-') || (a == '#'&&b == '*') || (a == '#'&&b == '/') || (a == '#'&&b == '(') || (a == '+'&&b == '^') || (a == '-'&&b == '^') || (a == '*'&&b == '^') || (a == '('&&b == '^') || (a == '#'&&b == '^') || (a == '^'&&b == '(')) return '<';
	if ((a == '('&&b == ')') || (a == '#'&&b == '#')) return '=';
	else return '?';
}
int judge_num(char a) {
	if (a >= '0'&&a <= '9') return 1;
	else if (a == ' ') return 3;
	else return 0;
}
double operate(double a, char c, double b) {
	if (c == '+') return (a + b);
	if (c == '-') return (a - b);
	if (c == '*') return (a * b);
	if (c == '/') {
		if (b != 0) return (a / b);
		else {
			printf("ERROR\n");
			return 0;
		}
	}
	else {
		printf("ERROR\n");
		return 0;
	}
}
int is_left(char ch) {
	if (ch == '(') return 1;
	else return 0;
}
int is_right(char ch) {
	if (ch == ')') return 1;
	else return 0;
}
int match(char a, char b) {
	if (a == '('&&b == ')') return 1;
	else return 0;
}
int check(char *exp) {//如果有括号，检验括号是否匹配
	char *p = exp, ch, e;
	sstack s = NULL;
	while ((ch = *p) != '\0') {
		if (is_left(ch)) push_code(s, ch);
		else if (is_right(ch)) {
			s = pop_code(s, e);
			if (e == '@') return 0;
			if (!match(e, ch)) return 0;
		}
		p++;
	}
	if (!stackempty(s)) return 0;
	else return 1;
}


void Calc(char cal[]) {
	sstack code;
	Linklist num=NULL;
	int count = 0,sign;
	double sum = 0,x,z,result;
	char e,f;//算式总长不得超过200
	// gets_s(cal);
	if (check(cal) == 0) {
		printf("ERROR:Cracket Error\n");
		return;
	}
	else {
		code = push_code(code, '#');
		for (count= 0; cal[count] != '\0'; count++);
		cal[count] = '#';
		count = 0;
		while (cal[count] != '#' || gettop_code(code) != '#') {
			sign = judge_num(cal[count]);
			if (sign == 3) count++;
			else if (sign == 1) {
				sum = cal[count] - 48;
				while (judge_num(cal[count+1]) == 1) {//不确定
					sum = 10 * sum + cal[count+1]-48 ;
					count++;
					/*if (sum >= setting) {超过设定大小
						printf("ERROR:Overflow\n");
						return;
					}*/
				}
				push_num(num, sum);
				sum = 0;
				count++;
				}
			else if (sign == 0) {//如果读到操作符
				if (cal[count] != '('&&cal[count] != ')') {
					if ((count == 0 && cal[count] != '-') || cal[count + 1] == '+' || cal[count + 1] == '-'||cal[count + 1] == '*'||cal[count + 1] == '/') {
						printf("ERROR:Code Error\n");
						return;
					}
				}
				if ((cal[count] == ')') || cal[count] == '(') {//左括号前面或右括号后面直接跟数字
					if (is_left(cal[count])) {
						if (count > 0 && judge_num(cal[count - 1]) == 1) {
							printf("ERROR:Cracket Error\n");
							return;
						}
					}
					if (is_right(cal[count])) {
						if (judge_num(cal[count + 1]) == 1) {
							printf("ERROR:Cracket Error\n");
							return;
						}
					}
					
				}
				e = gettop_code(code);
				if (e == '$') {
					push_code(code, cal[count]);
				}
				else{
					if (precede(e, cal[count]) == '<') {
						push_code(code, cal[count]);
						count++;
					}
					else if (precede(e, cal[count]) == '=') {
						pop_code(code, f);
						count++;
					}
					else while (precede(e, cal[count]) == '>') {
						pop_num(num, x);
						pop_num(num, z);
						pop_code(code, f);
						if (e == '/'&&x == 0) {
							printf("ERROR:Can't divide 0\n");
							return;
						}
						push_num(num, operate(z, e, x));
						e = gettop_code(code);
					}
				
				}
			}
		}
		result = gettop_num(num);
	}
	printf("%f\n", result);

}