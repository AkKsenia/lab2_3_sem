#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2 (3 sem)/lab2 (3 sem).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BalancedBSTtests
{
	TEST_CLASS(BalancedBSTtests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(15);
			bool elem_expected = false;
			bool elem_actual = tree.is_the_vector_empty();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod2)
		{
			BalancedBST<int> tree;
			bool elem_expected = true;
			bool elem_actual = tree.is_the_vector_empty();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod3)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			int elem_expected = 5;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod4)
		{
			BalancedBST<int> tree;
			int elem_expected = 0;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod5)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.remove(0);
			int elem_expected = 4;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod6)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.remove(15);
			int elem_expected = 4;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod7)
		{
			BalancedBST<int> tree;
			int items[3] = { 1,2,0 };
			LinkedListSequence<int> list(items, 3);
			Sequence<int>* seq = &list;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.concat(*seq);
			int elem_expected = 8;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod8)
		{
			BalancedBST<int> tree;
			int items[3] = { 1,2,0 };
			LinkedListSequence<int> list(items, 3);
			Sequence<int>* seq = &list;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.concat(*seq);
			int elem_expected = 0;
			int elem_actual = tree.get_item_from_sparse_vector(2);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod9)
		{
			BalancedBST<int> tree;
			int items[3] = { 1,2,0 };
			LinkedListSequence<int> list(items, 3);
			Sequence<int>* seq = &list;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.concat(*seq);
			int elem_expected = 1;
			int elem_actual = tree.get_item_from_sparse_vector(5);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod10)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.insert_at(2, 2);
			int elem_expected = 2;
			int elem_actual = tree.get_item_from_sparse_vector(2);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod11)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.insert_at(2, 2);
			int elem_expected = 0;
			int elem_actual = tree.get_item_from_sparse_vector(3);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod12)
		{
			BalancedBST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			string str = tree.index_of(0);
			int elem_expected = 2;
			int elem_actual = from_string_to_int(str);
			Assert::AreEqual(elem_expected, elem_actual);
		}
	};
}
