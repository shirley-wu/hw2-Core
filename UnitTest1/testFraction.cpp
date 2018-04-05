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
	TEST_CLASS(TestFraction)
	{
	public:
		
		TEST_METHOD(PrintFraction)
		{
			Fraction f(1, 2);
			stringstream ss;
			string s;
			ss << f;
			ss >> s;
			Assert::AreEqual(string("1/2"), s);
		}

		TEST_METHOD(PrintZero)
		{
			Fraction f(0, 1);
			stringstream ss;
			string s;
			ss << f;
			ss >> s;
			Assert::AreEqual(string("0"), s);
		}

		TEST_METHOD(AddFraction)
		{
			Fraction f1(1, 6), f2(4, 21);
			Fraction f = f1 + f2;
			stringstream ss;
			string s;
			ss << f;
			ss >> s;
			Assert::AreEqual(string("5/14"), s);
		}

		TEST_METHOD(SubFraction)
		{
			Fraction f1(5, 6), f2(5, 6);
			Fraction f = f1 - f2;
			stringstream ss;
			string s;
			ss << f;
			ss >> s;
			Assert::AreEqual(string("0"), s);
		}

		TEST_METHOD(MulFraction)
		{
			Fraction f1(7, 12), f2(24, 35);
			Fraction f = f1 * f2;
			stringstream ss;
			string s;
			ss << f;
			ss >> s;
			Assert::AreEqual(string("2/5"), s);
		}

		TEST_METHOD(DivFraction)
		{
			Fraction f1(13, 21), f2(52, 81);
			Fraction f = f1 / f2;
			stringstream ss;
			string s;
			ss << f;
			ss >> s;
			Assert::AreEqual(string("27/28"), s);
		}

	};
}