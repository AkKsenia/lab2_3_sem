#include "library.h"
#include "dynamic_array.h"

template <class T>
DynamicArray<T>::DynamicArray(T* items, int count) {
    size_of_array = count;
    capacity_of_array = size_of_array;
    if (size_of_array != 0) {
        data_of_array = new T[count];
        for (int i = 0; i < count; i++)
            data_of_array[i] = items[i];
    }
    else
        data_of_array = nullptr;
}
template <class T>
DynamicArray<T>::DynamicArray(int size) {
    size_of_array = size;
    capacity_of_array = size_of_array;
    if (size_of_array != 0)
        data_of_array = new T[size];
    else
        data_of_array = nullptr;
}
template <class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& old_version) {
    size_of_array = old_version.size_of_array;
    capacity_of_array = old_version.capacity_of_array;
    data_of_array = old_version.data_of_array;
}
template <class T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& old_version) {
    size_of_array = old_version.size_of_array;
    capacity_of_array = old_version.capacity_of_array;
    data_of_array = std::move(old_version.data_of_array);
    old_version.data_of_array = nullptr;
    old_version.size_of_array = old_version.capacity_of_array = 0;
}
template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template <class T>
const T& DynamicArray<T>::get(int index) {
    try {
        if ((index > size_of_array - 1) || (index < 0))
            throw (index);
        return data_of_array[index];
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество элементов в последовательности - " << size_of_array << ". Получение элемента осуществить невозможно!" << endl;
        cout << "Работа функции завершилась с кодом ";
        return -1;
    }
}
template <class T>
int DynamicArray<T>::get_size() {
    return size_of_array;
}
template <class T>
void DynamicArray<T>::set(const T& item, int index) {
    try {
        if ((index > size_of_array - 1) || (index < 0))
            throw (index);
        data_of_array[index] = item;
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество элементов в последовательности - " << size_of_array << ". Установку " << item << " на место " << index << " осуществить невозможно!" << endl;
        cout << endl;
    }
}
template <class T>
void DynamicArray<T>::resize(int newSize) {
    if (newSize > capacity_of_array) {
        int new_capacity = newSize;
        T* new_data = new T[newSize];
        for (int i = 0; i < size_of_array; ++i)
            new_data[i] = data_of_array[i];
        data_of_array = new_data;
        capacity_of_array = new_capacity;
        delete[] new_data;
    }
    size_of_array = newSize;
}
template <class T>
void DynamicArray<T>::remove_first() {
    try {
        if (data_of_array == nullptr)
            throw (0);
        int size = this->get_size();
        T* new_data = new T[size - 1];
        for (int i = 1; i < size; i++)
            new_data[i - 1] = data_of_array[i];
        this->resize(size - 1);
        for (int i = 0; i < size - 1; i++)
            data_of_array[i] = new_data[i];
        delete[] new_data;
    }
    catch (int number) {
        cout << "Первый элемент удалить невозможно, поскольку длина последовательности, равна " << number << endl;
    }
}
template <class T>
T& DynamicArray<T>::operator[](int index) {
    return data_of_array[index];
}