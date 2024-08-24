#pragma once
#include "sparse_vector.h"
#include "global.h"

template <class T>
class BalancedBSTNode {
public:
    T data;
    BalancedBSTNode<T>* left;
    BalancedBSTNode<T>* right;
    int index_of_node_in_sparse_vector;
public:
    BalancedBSTNode();
    BalancedBSTNode(T item);
};
template <class T>
class BalancedBST : public SparseVector<T> {
private:
    BalancedBSTNode<T>* root;
    int index_of_element_in_sparse_vector;
public:
    int counter = 0;
public:
    BalancedBST();

    bool is_the_vector_empty() override;
    int get_length_of_vector() override;
    void add(const T& item) override;
    BalancedBSTNode<T>* append(BalancedBSTNode<T>* current, const T& item);
    BalancedBSTNode<T>* max_elem_from_left_subtree(BalancedBSTNode<T>* current);
    void is_present(BalancedBSTNode<T>* current, const T& item);
    bool is_present_in_balancedBST(const T& item);
    bool has_a_null_element_been_inserted();
    void remove(const T& item) override;
    BalancedBSTNode<T>* delete_node(BalancedBSTNode<T>* current, const T& item);
    int height(BalancedBSTNode<T>* current);
    int get_balance_factor(BalancedBSTNode<T>* current);
    BalancedBSTNode<T>* left_rotate(BalancedBSTNode<T>* x);
    BalancedBSTNode<T>* right_rotate(BalancedBSTNode<T>* x);
    void get_item_from_vector(BalancedBSTNode<T>* current, int index);
    const T& get_item_from_sparse_vector(int index);
    void index_of_in_balancedBST(BalancedBSTNode<T>* current, const T& item);
    string index_of(const T& item) override;
    void insert_at(const T& item, int index) override;
    void prepend(const T& item) override;
    void concat(Sequence<T>& sorted_sequence) override;
    void get_values_from_some_node(BalancedBSTNode<T>* current);
    void get_values() override;
    void get_keys() override;
    void get_keys_from_some_node(BalancedBSTNode<T>* current);
    void traversing_with_decreasing_indexes(BalancedBSTNode<T>* current, int index);
};