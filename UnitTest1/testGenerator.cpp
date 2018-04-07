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
			set(100, 100, 1);
			bool status;
			string s, r;
			status = get_exp(0, s, r);
			Assert::IsFalse(status, L"no expression");
			generate();
			status = get_exp(0, s, r);
			Assert::IsTrue(status, L"proper expression");
			status = get_exp(1, s, r);
			Assert::IsFalse(status, L"overflow");
			status = get_exp(-1, s, r);
			Assert::IsFalse(status, L"improper quest");
		}

	};
}