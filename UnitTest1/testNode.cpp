#include "stdafx.h"
#include "CppUnitTest.h"
#include <cstdlib>
#include <ctime>

#include "../Core/generator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitNode)
	{
	public:
		
		TEST_METHOD(SingleNUM)
		{
			srand(time(0));
			NUMTYPE val = rand() % 50000;
			Node node1(val);
			bool status;
			status = node1.calc_val();
			Assert::IsTrue(status);
			Assert::AreEqual(val, node1.get_val());
		}

		TEST_METHOD(SingleADD) {
			NUMTYPE val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000;
			Node node1(ADD);
			Node *p, *q;
			bool status;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			status = node1.calc_val();
			Assert::IsTrue(status);
			Assert::AreEqual(val1 + val2, node1.get_val());
		}

		TEST_METHOD(SingleSUB) {
			NUMTYPE val1, val2;
			/*do {
				val1 = rand() % 50000;
				val2 = rand() % 50000;
			} while (val1 < val2);*/
			val1 = 1000;
			val2 = 500;
			Node node1(SUB);
			Node *p, *q;
			bool status;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			status = node1.calc_val();
			Assert::IsTrue(status);
			Assert::AreEqual(val1 - val2, node1.get_val());
			delete q;
			val2 = val1 + 2;
			q = new Node(val2);
			node1.set_rchild(q);
			status = node1.calc_val();
			Assert::IsFalse(status);
		}

		TEST_METHOD(SingleMUL) {
			NUMTYPE val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000;
			Node node1(MUL);
			Node *p, *q;
			bool status;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			status = node1.calc_val();
			Assert::IsTrue(status);
			Assert::AreEqual(val1 * val2, node1.get_val());
		}

		TEST_METHOD(SingleDIV) {
			NUMTYPE val1, val2;
			val1 = rand() % 50000;
			val2 = rand() % 50000 + 1;
			Node node1(DIV);
			Node *p, *q;
			bool status;
			p = new Node(val1);
			node1.set_lchild(p);
			q = new Node(val2);
			node1.set_rchild(q);
			status = node1.calc_val();
			Assert::IsTrue(status);
			Assert::AreEqual(val1 / val2, node1.get_val());
			delete q;
			val2 = 0;
			q = new Node(val2);
			node1.set_rchild(q);
			status = node1.calc_val();
			Assert::IsFalse(status);
		}

		TEST_METHOD(Equal) {
			NUMTYPE val1 = rand()%50000, val2 = rand()%50000, val3 = rand()%50000;
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