#pragma once
#include "sequence.h"

template <class T>
class SparseVector {
public:
    virtual bool is_the_vector_empty() = 0;
    virtual int get_length_of_vector() = 0;
    virtual string index_of(const T& item) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void insert_at(const T& item, int index) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void add(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void remove(const T& item) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void concat(Sequence<T>& sorted_sequence) = 0;
    virtual void get_keys() = 0;
    virtual void get_values() = 0;
};