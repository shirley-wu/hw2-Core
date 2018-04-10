#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "../Core/node.h"
#include "../Core/dll.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;
using std::stringstream;
using std::fixed;
using std::setprecision;

namespace UnitTest1
{		
	TEST_CLASS(TestNode)
	{
	public:
		TestNode() {
			srand((unsigned)time(0));
		}
		
		TEST_METHOD(SingleINT)
		{
			int val = rand() % 50000;
			Node n(val);
			string s1, s2, st1, st2;
			stringstream ss;
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << val;
			st1 = st2 = ss.str();
			Assert::AreEqual(s1, st1, L"expression");
			Assert::AreEqual(s2, st2, L"answer");
		}

		TEST_METHOD(AddINT) {
			int val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000;
			Node n(ADD);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << val1 << " + " << val2;
			st1 = ss.str();
			getline(ss, st1);
			ss.clear();
			ss << val1 + val2;
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
		}

		TEST_METHOD(MulINT) {
			int val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000;
			Node n(MUL);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << val1 << " * " << val2;
			getline(ss, st1);
			ss.clear();
			ss << val1 * val2;
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
		}

		TEST_METHOD(DivINT) {
			int val1, val2;
			val2 = rand() % 1000;
			val1 = val2 * (rand() % 5000);
			Node n(DIV);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << val1 << " / " << val2;
			getline(ss, st1);
			ss.clear();
			ss << val1 / val2;
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
		}

		TEST_METHOD(PowINT) {
			int val1, val2;
			val1 = rand() % 100;
			val2 = 3;
			Node n(POW);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			set_power_signal(true);
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << val1 << " ^ " << val2;
			getline(ss, st1);
			ss.clear();
			ss << (int)pow(val1, val2);
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
			set_power_signal(false);
			to_expression(&n, s1);
			ss << val1 << " ** " << val2;
			getline(ss, st1);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
		}

		TEST_METHOD(SingleDOUBLE)
		{
			int p = 3;
			set_precision(p);
			double val = (rand() % 50000) / pow(10, p);
			Node n(val);
			string s1, s2, st1, st2;
			stringstream ss;
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << fixed << setprecision(p) << val;
			st1 = st2 = ss.str();
			Assert::AreEqual(s1, st1, L"expression");
			Assert::AreEqual(s2, st2, L"answer");
		}

		TEST_METHOD(AddDOUBLE) {
			int p = 3;
			set_precision(p);
			double val1, val2;
			val1 = (rand() % 50000) / pow(10, p);
			val2 = (rand() % 50000) / pow(10, p);
			Node n(ADD);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << fixed << setprecision(p) << val1 << " + " << val2;
			st1 = ss.str();
			getline(ss, st1);
			ss.clear();
			ss << fixed << setprecision(p) << val1 + val2;
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
		}

		TEST_METHOD(MulDOUBLE) {
			int p = 3;
			set_precision(p);
			double val1, val2;
			val1 = (rand() % 50000) / pow(10, p);
			val2 = (rand() % 50000) / pow(10, p);
			Node n(MUL);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << fixed << setprecision(p) << val1 << " * " << val2;
			st1 = ss.str();
			getline(ss, st1);
			ss.clear();
			ss << fixed << setprecision(p) << val1 * val2;
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
		}

		TEST_METHOD(DivDOUBLE) {
			int p = 3;
			set_precision(p);
			double val1, val2;
			val1 = (rand() % 50000) / pow(10, p);
			val2 = (rand() % 50000) / pow(10, p);
			Node n(DIV);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << fixed << setprecision(p) << val1 << " / " << val2;
			getline(ss, st1);
			ss.clear();
			ss << fixed << setprecision(p) << val1 / val2;
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
		}

		TEST_METHOD(PowDOUBLE) {
			int p = 3;
			set_precision(p);
			double val1;
			val1 = (rand() % 50000) / pow(10, p);
			int val2;
			val2 = 3;
			Node n(POW);
			string s1, s2, st1, st2;
			stringstream ss;
			n.set_lchild(new Node(val1));
			n.set_rchild(new Node(val2));
			n.calc_val();
			set_power_signal(true);
			to_expression(&n, s1);
			to_answer(&n, s2);
			ss << fixed << setprecision(p) << val1 << " ^ " << val2;
			getline(ss, st1);
			ss.clear();
			ss << fixed << setprecision(p) << pow(val1, val2);
			getline(ss, st2);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
			Assert::AreEqual(st2, s2, L"answer");
			set_power_signal(false);
			to_expression(&n, s1);
			ss << fixed << setprecision(p) << val1 << " ** " << val2;
			getline(ss, st1);
			ss.clear();
			Assert::AreEqual(st1, s1, L"expression");
		}

		TEST_METHOD(Equal) {
			int val1 = rand()%50000, val2 = rand()%50000, val3 = rand()%50000;
			Node node1(ADD), node2(ADD), node3(MUL), node4(MUL);
			Node *p, *q;

			p = new Node(ADD);
			p->set_lchild(new Node(val1));
			p->set_rchild(new Node(val2));
			node1.set_lchild(p);
			q = new Node(val3);
			node1.set_rchild(q);

			q = new Node(val3);
			node2.set_rchild(q);
			p = new Node(ADD);
			p->set_lchild(new Node(val2));
			p->set_rchild(new Node(val1));
			node2.set_lchild(p);

			p = new Node(MUL);
			p->set_lchild(new Node(val1));
			p->set_rchild(new Node(val2));
			node3.set_lchild(p);
			q = new Node(val3);
			node3.set_rchild(q);

			q = new Node(val3);
			node4.set_rchild(q);
			p = new Node(MUL);
			p->set_lchild(new Node(val2));
			p->set_rchild(new Node(val1));
			node4.set_lchild(p);

			Assert::IsTrue(equal(&node1, &node2));
			Assert::IsTrue(equal(&node3, &node4));
		}

	};
}