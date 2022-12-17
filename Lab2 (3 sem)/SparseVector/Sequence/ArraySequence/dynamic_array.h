#pragma once

template <class T>
class DynamicArray {
private:
    int size_of_array;
    int capacity_of_array;
    T* data_of_array;
public:
    DynamicArray(T* items, int count);
    DynamicArray(int size = 1);
    DynamicArray(const DynamicArray<T>& old_version);
    DynamicArray(DynamicArray<T>&& old_version);
    ~DynamicArray();

    const T& get(int index);
    int get_size();
    void set(const T& item, int index);
    void resize(int newSize);
    void remove_first();
    T& operator[](int index);
};