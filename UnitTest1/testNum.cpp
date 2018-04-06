#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>
#include <string>

#include "../Core/num.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::stringstream;
using std::string;

namespace UnitTest1
{		
	TEST_CLASS(TestNum)
	{
	public:
		
		TEST_METHOD(TestInt)
		{
			Num n(12);
			stringstream ss;
			string s;
			ss << n;
			ss >> s;
			Assert::AreEqual(string("12"), s);
		}

		TEST_METHOD(TestDouble)
		{
			Num n(1.134);
			stringstream ss;
			string s;
			ss << n;
			ss >> s;
			Assert::AreEqual(string("1.134"), s);
		}

		TEST_METHOD(TestFraction)
		{
			Num n(Fraction(12, 13));
			stringstream ss;
			string s;
			ss << n;
			ss >> s;
			Assert::AreEqual(string("12/13"), s);
		}

		TEST_METHOD(TestAdd)
		{
			Num n1(3), n2(1.5), n3(Fraction(27, 100));
			stringstream ss;
			string s;
			ss << n1 + n1 << ' ';
			ss << n1 + n2 << ' ';
			ss << n1 + n3 << ' ';
			ss << n2 + n2 << ' ';
			ss << n2 + n3 << ' ';
			ss << n3 + n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("6"), s);
			ss >> s;
			Assert::AreEqual(string("4.5"), s);
			ss >> s;
			Assert::AreEqual(string("3.27"), s);
			ss >> s;
			Assert::AreEqual(string("3"), s);
			ss >> s;
			Assert::AreEqual(string("1.77"), s);
			ss >> s;
			Assert::AreEqual(string("27/50"), s);
		}

		TEST_METHOD(TestSub)
		{
			Num n1(3), n2(1.5), n22(0.7), n3(Fraction(27, 100)), n32(Fraction(13, 100));
			stringstream ss;
			string s;
			ss << n1 - n1 << ' ';
			ss >> s;
			Assert::AreEqual(string("0"), s);
			ss << n1 - n2 << ' ';
			ss >> s;
			Assert::AreEqual(string("1.5"), s);
			ss << n1 - n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("2.73"), s);
			ss << n2 - n22 << ' ';
			ss >> s;
			Assert::AreEqual(string("0.8"), s);
			ss << n2 - n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("1.23"), s);
			ss << n3 - n32 << ' ';
			ss >> s;
			Assert::AreEqual(string("7/50"), s);
		}

		TEST_METHOD(TestMul)
		{
			Num n1(3), n12(7), n2(1.5), n22(0.7), n3(Fraction(27, 100)), n32(Fraction(13, 100));
			stringstream ss;
			string s;
			ss << n1 * n12 << ' ';
			ss >> s;
			Assert::AreEqual(string("21"), s);
			ss << n1 * n2 << ' ';
			ss >> s;
			Assert::AreEqual(string("4.5"), s);
			ss << n1 * n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("0.81"), s);
			ss << n2 * n22 << ' ';
			ss >> s;
			Assert::AreEqual(string("1.05"), s);
			ss << n2 * n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("0.405"), s);
			ss << n3 * n32 << ' ';
			ss >> s;
			Assert::AreEqual(string("351/10000"), s);
		}

		TEST_METHOD(TestDiv)
		{
			Num n1(3), n12(7), n2(1.5), n22(0.7), n3(Fraction(27, 100)), n32(Fraction(13, 100));
			stringstream ss;
			string s;
			ss << n1 / n12 << ' ';
			ss >> s;
			Assert::AreEqual(string("0"), s);
			ss << n1 / n2 << ' ';
			ss >> s;
			Assert::AreEqual(string("2"), s);
			ss << n1 / n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("11.1111"), s);
			ss << n2 / n22 << ' ';
			ss >> s;
			Assert::AreEqual(string("2.14286"), s);
			ss << n2 / n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("5.55556"), s);
			ss << n32 / n3 << ' ';
			ss >> s;
			Assert::AreEqual(string("13/27"), s);
		}

	};
}