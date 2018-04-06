#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../Core/generator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTest1
{		
	TEST_CLASS(TestGenerator)
	{
	public:
		
		TEST_METHOD(TestOverflow)
		{
			Generator g;
			g.set(100, 100, 1);
			bool status;
			Num r;
			string s;
			status = g.get_exp(0, s, r);
			Assert::IsFalse(status, L"no expression");
			g.generate();
			status = g.get_exp(0, s, r);
			Assert::IsTrue(status, L"proper expression");
			status = g.get_exp(1, s, r);
			Assert::IsFalse(status, L"overflow");
			status = g.get_exp(-1, s, r);
			Assert::IsFalse(status, L"improper quest");
		}

	};
}