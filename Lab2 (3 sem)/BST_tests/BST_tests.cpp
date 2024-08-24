#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2 (3 sem)/lab2 (3 sem).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BSTtests
{
	TEST_CLASS(BSTtests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(15);
			bool elem_expected = false;
			bool elem_actual = tree.is_empty();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod2)
		{
			BST<int> tree;
			bool elem_expected = true;
			bool elem_actual = tree.is_empty();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod3)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(15);
			int elem_expected = 9;
			int elem_actual = tree.get_first();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod4)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(15);
			int elem_expected = 15;
			int elem_actual = tree.get_last();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod5)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			int elem_expected = 3;
			int elem_actual = tree.get_length();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod6)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			int elem_expected = 5;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod7)
		{
			BST<int> tree;
			int elem_expected = 0;
			int elem_actual = tree.get_length();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod8)
		{
			BST<int> tree;
			int elem_expected = 0;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod9)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			int elem_expected = 15;
			int elem_actual = tree.get(2);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod10)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod11)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod12)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.remove(0);
			int elem_expected = 3;
			int elem_actual = tree.get_length();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod13)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.remove(15);
			int elem_expected = 2;
			int elem_actual = tree.get_length();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod14)
		{
			BST<int> tree;
			int items[3] = { 1,2,0 };
			LinkedListSequence<int> list(items, 3);
			Sequence<int>* seq = &list;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.concat(*seq);
			int elem_expected = 5;
			int elem_actual = tree.get_length();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod15)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod16)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod17)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod18)
		{
			BST<int> tree;
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
			int elem_actual = tree.get(0);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod19)
		{
			BST<int> tree;
			int items[3] = { 1,2,0 };
			LinkedListSequence<int> list(items, 3);
			Sequence<int>* seq = &list;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.concat(*seq);
			tree.remove(1);
			int elem_expected = 2;
			int elem_actual = tree.get(0);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod20)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.remove_first();
			int elem_expected = 15;
			int elem_actual = tree.get(0);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod21)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod22)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.insert_at(2, 2);
			int elem_expected = 2;
			int elem_actual = tree.get(0);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod23)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod24)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.set(2, 2);
			int elem_expected = 2;
			int elem_actual = tree.get_item_from_sparse_vector(2);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod25)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			tree.set(2, 2);
			int elem_expected = 2;
			int elem_actual = tree.get(0);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod26)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(15);
			tree.set(2, 2);
			int elem_expected = 15;
			int elem_actual = tree.get_item_from_sparse_vector(3);
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod27)
		{
			BST<int> tree;
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
		TEST_METHOD(TestMethod28)
		{
			BST<int> tree;
			tree.add(9);
			tree.add(15);
			tree.add(0);
			tree.add(0);
			tree.add(15);
			string str = tree.index_of(15);
			int elem_expected = 1;
			int elem_actual = from_string_to_int(str);
			Assert::AreEqual(elem_expected, elem_actual);
		}
	};
}
