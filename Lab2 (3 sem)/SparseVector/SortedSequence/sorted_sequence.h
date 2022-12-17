#pragma once
#include "sparse_vector.h"
#include "sequence.h"

template <class T>
class SortedSequence : public Sequence<T>, public SparseVector<T> {
public:
    virtual int get_length() = 0;
    virtual const T& get(int index) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual const T& get_first() = 0;//может выбрасывать исключение IndexOutOfRange
    virtual const T& get_last() = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void remove(const T& item) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void add(const T& item) = 0;
    virtual void get_subsequence(int startindex, int engindex) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual bool is_empty() = 0;
    virtual void get_keys() = 0;
    virtual void get_values() = 0;
};