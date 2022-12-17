#pragma once
#include "sorted_sequence.h"
#include "global.h"

template <class T>
class Keys {
public:
    T key;
    int index_in_sparse_vector;
};

template <class T>
class BTreeNode {
public:
    Keys<T>* keys;
    int number_of_keys_in_the_current_node;
    bool leaf;
    BTreeNode<T>** children;
public:
    BTreeNode(int min_degree, bool _leaf);

    void insert_in_the_non_full_node(int min_degree, const T& item, int index_of_element_in_sparse_vector);
    void split_the_child(int min_degree, int i, BTreeNode<T>* node_for_splitting);
    const T& get_first();
    int get_first_index();
    const T& get_last();
    int get_last_index();
};

template <class T>
class BTree : public SortedSequence<T> {
private:
    BTreeNode<T>* root;
    int min_degree;
    int index_of_element_in_sparse_vector;
public:
    int counter = 0;
public:
    BTree(int _min_degree);
    BTree();

    void add_min_degree(int _min_degree);
    void traverse();
    void traverse_from_some_node(BTreeNode<T>* current);
    BTreeNode<T>* search(const T& item);
    BTreeNode<T>* search_from_some_node(BTreeNode<T>* current, const T& item);
    void append(const T& item);
    bool is_empty() override;
    bool is_the_vector_empty() override;
    const T& get_first() override;
    const T& get_last() override;
    int get_length_of_vector() override;
    void add(const T& item) override;
    void get_subsequence(int startindex, int endindex) override;
    void get_keys_from_some_node(BTreeNode<T>* current);
    void get_keys() override;
    void get_values_from_some_node(BTreeNode<T>* current);
    void get_values() override;
    void length(BTreeNode<T>* current);
    int get_length() override;
    void get_item_from_some_node(BTreeNode<T>* current, int index);
    const T& get(int index) override;
    void index_of_in_btree(BTreeNode<T>* current, const T& item);
    string index_of(const T& item) override;
    void get_item_from_vector(BTreeNode<T>* current, int index);
    const T& get_item_from_sparse_vector(int index);
    void prepend(const T& item) override;
    void insert_at(const T& item, int index) override;
    void set(const T& item, int index) override;
    void concat(Sequence<T>& sorted_sequence) override;
    int find_a_key(BTreeNode<T>* current, const T& item);
    void borrow_from_left_sibling(BTreeNode<T>* current, int index);
    void borrow_from_right_sibling(BTreeNode<T>* current, int index);
    void merge(BTreeNode<T>* current, int index);
    void extend(BTreeNode<T>* current, int index);
    void remove_from_leaf(BTreeNode<T>* current, int index);
    void change_the_index(BTreeNode<T>* current, int index, int new_one);
    void remove_from_some_node(BTreeNode<T>* current, const T& item, int _index);
    int get_index_of_del_elem(BTreeNode<T>* current, const T& item);
    void is_present(BTreeNode<T>* current, const T& item);
    bool is_present_in_BTree(const T& item);
    bool has_a_null_element_been_inserted();
    void remove(const T& item) override;
    void remove_from_non_leaf(BTreeNode<T>* current, int index, int _indexer);
    void traversing_with_decreasing_indexes(BTreeNode<T>* current, int index);
    void remove_first() override;
};