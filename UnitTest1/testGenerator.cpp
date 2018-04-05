#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>

#include "../Core/generator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::string;

namespace UnitTest1
{		
	TEST_CLASS(UnitGenerator)
	{
	public:
		
		TEST_METHOD(TestOverflow)
		{
			Generator g;
			g.set(100, 100, 1);
			bool status;
			NUMTYPE r;
			string s;
			status = g.get_exp(0, s, r);
			Assert::IsFalse(status);
			g.generate();
			status = g.get_exp(0, s, r);
			Assert::IsTrue(status);
			status = g.get_exp(1, s, r);
			Assert::IsFalse(status);
		}

	};
}