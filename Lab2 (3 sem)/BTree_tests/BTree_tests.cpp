#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2 (3 sem)/lab2 (3 sem).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BTreetests
{
	TEST_CLASS(BTreetests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BTree<int> tree(2);
			tree.add(9);
			tree.add(15);
			tree.add(15);
			bool elem_expected = false;
			bool elem_actual = tree.is_empty();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod2)
		{
			BTree<int> tree(2);
			bool elem_expected = true;
			bool elem_actual = tree.is_empty();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod3)
		{
			BTree<int> tree(2);
			tree.add(9);
			tree.add(15);
			tree.add(15);
			int elem_expected = 9;
			int elem_actual = tree.get_first();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod4)
		{
			BTree<int> tree(2);
			tree.add(9);
			tree.add(15);
			tree.add(15);
			int elem_expected = 15;
			int elem_actual = tree.get_last();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod5)
		{
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
			int elem_expected = 0;
			int elem_actual = tree.get_length();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod8)
		{
			BTree<int> tree(2);
			int elem_expected = 0;
			int elem_actual = tree.get_length_of_vector();
			Assert::AreEqual(elem_expected, elem_actual);
		}
		TEST_METHOD(TestMethod9)
		{
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
			BTree<int> tree(2);
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
