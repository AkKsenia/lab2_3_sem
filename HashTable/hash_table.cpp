#include "library.h"
#include "others.h"
#include "hash_table.h"

template<class K, class V>
HT_Node<K,V>::HT_Node() {
	key = 0;
	value = 0;
	next = nullptr;
}
template<class K, class V>
HT_Node<K, V>::HT_Node(K key, V value) {
	this->key = key;
	this->value = value;
	next = nullptr;
}

template<class K, class V>
HashTable<K,V>::HashTable() {
	array = new HT_Node<K, V>*[size_of_HT];
	for (int i = 0; i < size_of_HT; i++)
		array[i] = nullptr;
}
template<class K, class V>
HashTable<K, V>::HashTable(int size_of_HT) {
	this->size_of_HT = size_of_HT;
	array = new HT_Node<K, V>*[size_of_HT];
	for (int i = 0; i < size_of_HT; i++)
		array[i] = nullptr;
}
template<class K, class V>
HashTable<K, V>::~HashTable() {
	for (int i = 0; i < size_of_HT; i++) {
		HT_Node<K, V>* current = array[i];
		while (current != nullptr) {
			HT_Node<K, V>* previous = current;
			current = current->next;
			delete previous;
		}
	}
	delete[] array;
}

template<class K, class V>
int HashTable<K, V>::hash_function(const K& key) {
	return key % nearest_prime_number(size_of_HT);
}
template<class K, class V>
void HashTable<K, V>::insert(const K& key, const V& value) {
	int hash = hash_function(key);
	HT_Node<K, V>* previous = nullptr;
	HT_Node<K, V>* current = array[hash];
	while (current != nullptr) {
		if (current->key != key) {
			previous = current;
			current = current->next;
		}
		else break;
	}
	if (current == nullptr) {
		current = new HT_Node<K, V>(key, value);
		if (previous == nullptr) //лист пуст
			array[hash] = current;
		else previous->next = current;
		++count;
	}
	else current->value = value;
	if (count >= load_factor * size_of_HT) rehash();
}
template<class K, class V>
bool HashTable<K, V>::search(const K& key) {
	int hash = hash_function(key);
	HT_Node<K, V>* current = array[hash];
	while (current != nullptr) {
		if (current->key == key)
			return true;
		current = current->next;
	}
	return false;
}
template<class K, class V>
void HashTable<K, V>::remove(const K& key) {
	try {
		if (!search(key))
			throw(key);
		int hash = hash_function(key);
		HT_Node<K, V>* current = array[hash];
		HT_Node<K, V>* previous = current;
		int counter = 0;
		while (current != nullptr) {
			if (current->key == key)
				break;
			previous = current;
			current = current->next;
			++counter;
		}
		if (current != nullptr) {
			if (counter != 0)
				previous->next = current->next;
			else
				array[hash] = current->next;
			delete current;
		}
		--count;
	}
	catch (const K& key) {
		cout << "Удаление невозможно, поскольку хэш-таблица не содержит ключа " << key << endl;
	}
}
template<class K, class V>
void HashTable<K, V>::rehash() {
	int prev_size = size_of_HT;
	size_of_HT *= 2;
	HT_Node<K, V>** array_ = new HT_Node<K, V>*[size_of_HT];
	for (int i = 0; i < size_of_HT; i++)
		array_[i] = nullptr;
	swap(array, array_);
	HT_Node<K, V>* current = nullptr;
	for (int i = 0; i < prev_size; i++) {
		current = array_[i];
		while (current != nullptr) {
			insert(current->key, current->value);
			current = current->next;
		}
	}
	for (int i = 0; i < prev_size; i++)
		if (array_[i])
			delete array_[i];
	delete[] array_;
}

template<class K, class V>
void HashTable<K, V>::print_table() {
	HT_Node<K, V>* current = nullptr;
	for (int i = 0; i < size_of_HT; i++) {
		current = array[i];
		while (current != nullptr) {
			cout << current->key << ' ' << current->value << endl;
			current = current->next;
		}
		cout << endl;
	}
}