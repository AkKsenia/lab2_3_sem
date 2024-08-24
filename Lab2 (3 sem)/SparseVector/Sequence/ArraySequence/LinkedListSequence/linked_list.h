#pragma once

template <class T>
class Node {
public:
    T data;
    Node<T>* next;

    Node();
    Node(const T& item, Node<T>* ptr = nullptr);
};
template <class T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList(T* items, int amount);
    LinkedList();
    LinkedList(const LinkedList<T>& old_version);
    LinkedList(LinkedList<T>&& old_version);
    ~LinkedList();

    const T& get_first();
    const T& get_last();
    const T& get(int index);
    LinkedList<T>* get_sub_list(int startindex, int endindex);
    LinkedList<T>* concat(const LinkedList<T>& list);
    int get_length();
    void append(const T& item);
    void set(const T& item, int index);
    void prepend(const T& item);
    void insert_at(const T& item, int index);
    void remove_first();
};