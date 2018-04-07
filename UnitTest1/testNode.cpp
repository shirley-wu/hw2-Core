#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include <ctime>

#include "../Core/node.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(TestNode)
	{
	public:
		
		TEST_METHOD(SingleNUM)
		{
			srand((unsigned)time(0));
			int val = rand() % 50000;
			Node node1(val);
			node1.calc_val();
			Assert::IsTrue(Num(val) == node1.get_val());
		}

		TEST_METHOD(SingleADD) {
			int val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000;
			Node node1(ADD);
			Node *p, *q;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			node1.calc_val();
			Assert::IsTrue(Num(val1 + val2) == node1.get_val());
		}

		TEST_METHOD(SingleSUB) {
			int val1, val2;
			val1 = 1000;
			val2 = 500;
			Node node1(SUB);
			Node *p, *q;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			node1.calc_val();
			Assert::IsTrue(Num(val1 - val2) == node1.get_val());
		}

		TEST_METHOD(SingleMUL) {
			int val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000;
			Node node1(MUL);
			Node *p, *q;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			node1.calc_val();
			Assert::IsTrue(Num(val1 * val2) == node1.get_val());
		}

		TEST_METHOD(SingleDIV) {
			int val1, val2;
			val1 = rand() % 50000;
			val2 = val1 * 2;
			Node node1(DIV);
			Node *p, *q;
			p = new Node(val2);
			node1.set_lchild(p);
			q = new Node(val1);
			node1.set_rchild(q);
			node1.calc_val();
			Assert::IsTrue(Num(2) == node1.get_val());
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