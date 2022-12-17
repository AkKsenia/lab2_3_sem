#pragma once

template <class T>
class Sequence {
public:
    virtual const T& get_first() = 0;//может выбрасывать исключение IndexOutOfRange
    virtual const T& get_last() = 0;//может выбрасывать исключение IndexOutOfRange
    virtual const T& get(int index) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual int get_length() = 0;
    virtual void append(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void set(const T& item, int index) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void remove_first() = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void concat(Sequence<T>&) = 0;
    virtual void insert_at(const T& item, int index) = 0;//может выбрасывать исключение IndexOutOfRange
    virtual void get_subsequence(int startindex, int endindex) = 0;//может выбрасывать исключение IndexOutOfRange
};