#pragma once

template<class K, class V>
class HT_Node {
public:
	K key;
	V value;
	HT_Node<K, V>* next;

	HT_Node();
	HT_Node(K key, V value);
};

template<class K, class V>
class HashTable {
	int size_of_HT = 11;
	HT_Node<K, V>** array;
	int count = 0;
	double load_factor = 0.75;
public:
	HashTable();
	HashTable(int size_of_HT);
	~HashTable();

	int hash_function(const K& key);
	void insert(const K& key, const V& value);
	bool search(const K& key);
	void remove(const K& key);
	void rehash();

	void print_table();
};