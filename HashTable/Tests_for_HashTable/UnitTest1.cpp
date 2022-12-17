#include "pch.h"
#include "CppUnitTest.h"
#include "../main/others.cpp"
#include "../main/hash_table.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HashTable<int, int> hash_table(5);
			hash_table.insert(1, 2);
			hash_table.insert(1, 3);
			bool elem_expected = true;
			bool elem_actual = hash_table.search(1);
			Assert::AreEqual(elem_expected, elem_actual);
		}

		TEST_METHOD(TestMethod2)
		{
			HashTable<int, int> hash_table(5);
			hash_table.insert(1, 2);
			hash_table.insert(1, 3);
			bool elem_expected = false;
			bool elem_actual = hash_table.search(2);
			Assert::AreEqual(elem_expected, elem_actual);
		}

		TEST_METHOD(TestMethod3)
		{
			HashTable<int, int> hash_table(5);
			hash_table.insert(1, 2);
			hash_table.insert(1, 3);
			hash_table.remove(1);
			bool elem_expected = false;
			bool elem_actual = hash_table.search(1);
			Assert::AreEqual(elem_expected, elem_actual);
		}
	};
}
