#pragma once
#include "sorted_sequence.h"
#include "global.h"

template <class T>
class BSTNode {
public:
    T data;
    BSTNode<T>* left;
    BSTNode<T>* right;
    int index_of_node_in_sparse_vector;
public:
    BSTNode();
    BSTNode(T item);
};
template <class T>
class BST : public SortedSequence<T> {
private:
    BSTNode<T>* root;
    int index_of_element_in_sparse_vector;
public:
    BST();

    bool is_empty() override;
    bool is_the_vector_empty() override;
    const T& get_first() override;
    const T& get_last() override;
    int get_length() override;
    int amount(BSTNode<T>* current);
    int get_length_of_vector() override;
    void append(const T& item) override;
    void add(const T& item) override;
    void is_present(BSTNode<T>* current, const T& item);
    bool is_present_in_BST(const T& item);
    bool has_a_null_element_been_inserted();
    void remove(const T& item) override;
    BSTNode<T>* max_elem_from_left_subtree(BSTNode<T>* current);
    const T& get(int index) override;
    BSTNode<T>* pointer_to_node(const T& item, int index);
    string index_of(const T& item) override;
    void get_values_from_some_node(BSTNode<T>* current);
    void get_values() override;
    void get_keys() override;
    void get_keys_from_some_node(BSTNode<T>* current);
    void get_subsequence(int startindex, int endindex) override;
    void concat(Sequence<T>& sorted_sequence) override;
    BSTNode<T>* delete_node(BSTNode<T>* current, const T& item);
    const T& get_item_from_sparse_vector(int index);
    void prepend(const T& item) override;
    void insert_at(const T& item, int index) override;
    void set(const T& item, int index) override;
    void remove_first() override;
    void traversing_with_decreasing_indexes(BSTNode<T>* current, int index);
};