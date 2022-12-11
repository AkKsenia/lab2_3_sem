#include "library.h"
#include "linked_list.h"

template<class T>
Node<T>::Node() : data(0), next(nullptr) {}
template<class T>
Node<T>::Node(const T& item, Node<T>* ptr) : data(item), next(ptr) {}

template <class T>
LinkedList<T>::LinkedList(T* items, int amount) {
    if (amount == 0)
        head = nullptr;
    else {
        Node<T>* current = new Node<T>;
        head = current;
        for (int i = 0; i < amount; i++) {
            current->data = items[i];
            if (i != amount - 1) {
                Node<T>* new_node = new Node<T>;
                current->next = new_node;
                current = current->next;
            }
        }
    }
}
template <class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& old_version) {
    int kol_vo = 0;
    Node<T>* cur_node = old_version.head;
    if (cur_node != nullptr) {
        while (cur_node->next != nullptr) {
            ++kol_vo;
            cur_node = cur_node->next;
        }
        ++kol_vo;
        Node<T>* node1 = new Node<T>;
        Node<T>* old_node = old_version.head;
        node1->data = old_node->data;
        old_node = old_node->next;
        if (kol_vo == 1) {
            node1->next = nullptr;
            head = node1;
        }
        else {
            node1->next = old_node;
            head = node1;
            node1 = node1->next;
            for (int i = 1; i < kol_vo - 1; ++i) {
                node1->data = old_node->data;
                old_node = old_node->next;
                node1->next = old_node;
                node1 = node1->next;
            }
            node1->data = old_node->data;
            node1->next = nullptr;
        }
    }
    else head = nullptr;
}
template <class T>
LinkedList<T>::LinkedList(LinkedList<T>&& old_version) {
    int kol_vo = 0;
    Node<T>* cur_node = old_version.head;
    if (cur_node != nullptr) {
        while (cur_node->next != nullptr) {
            ++kol_vo;
            cur_node = cur_node->next;
        }
        ++kol_vo;
        Node<T>* node1 = new Node<T>;
        Node<T>* old_node = old_version.head;
        node1->data = old_node->data;
        old_node = old_node->next;
        if (kol_vo == 1) {
            node1->next = nullptr;
            head = node1;
        }
        else {
            node1->next = old_node;
            head = node1;
            node1 = node1->next;
            for (int i = 1; i < kol_vo - 1; ++i) {
                node1->data = old_node->data;
                old_node = old_node->next;
                node1->next = old_node;
                node1 = node1->next;
            }
            node1->data = old_node->data;
            node1->next = nullptr;
        }
    }
    else head = nullptr;
    old_version.head = nullptr;
}
template<class T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while (current) {
        Node<T>* for_deleting = current;
        current = current->next;
        delete for_deleting;
    }
}

template <class T>
const T& LinkedList<T>::get_first() {
    Node<T>* current = head;
    try {
        if (current == nullptr)
            throw (0);
        return current->data;
    }
    catch (int number) {
        cout << "Первый элемент получить невозможно, поскольку длина последовательности, равна ";
        return number;
    }
}
template <class T>
const T& LinkedList<T>::get_last() {
    Node<T>* current = head;
    try {
        if (current == nullptr)
            throw (0);
        while (current->next != nullptr) {
            current = current->next;
        }
        return current->data;
    }
    catch (int number) {
        cout << "Последний элемент получить невозможно, поскольку длина последовательности, равна ";
        return number;
    }
}
template <class T>
const T& LinkedList<T>::get(int index) {
    Node<T>* current = head;
    Node<T>* current1 = head;
    int kol_vo = 0, k = 0;
    while (current != nullptr) {
        current = current->next;
        ++kol_vo;
    }
    try {
        if ((index < 0) || (index > kol_vo - 1))
            throw (index);
        while (k != index) {
            current1 = current1->next;
            ++k;
        }
        return current1->data;
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество элементов в последовательности - " << kol_vo << ". Получение элемента осуществить невозможно!" << endl;
        cout << "Работа функции завершилась с кодом ";
        return -1;
    }
}
template <class T>
LinkedList<T>* LinkedList<T>::get_sub_list(int startindex, int endindex) {
    Node<T>* node = head;
    int kol_vo = 0;
    while (node != nullptr) {
        node = node->next;
        ++kol_vo;
    }
    try {
        LinkedList<T>* list = new LinkedList<T>();
        if ((startindex < 0) || (startindex >= kol_vo) || (endindex < 0) || (endindex >= kol_vo) || (startindex > endindex))
            throw (list);
        Node<T>* current = head;
        int k = 0;
        while (k != startindex) {
            current = current->next;
            ++k;
        }
        for (k; k <= endindex; k++) {
            list->append(current->data);
            current = current->next;
        }
        return list;
    }
    catch (LinkedList<T>* list) {
        cout << "Введённые вами индексы начала и конца подпоследовательности равны " << startindex << " и " << endindex << ", в то время как общее число элементов равно " << kol_vo << ". Операцию извлечения подпоследовательности произвести невозможно!" << endl;
        return list;
    }
}
template <class T>
LinkedList<T>* LinkedList<T>::concat(const LinkedList<T>& list) {
    LinkedList<T>* concat_list = new LinkedList<T>();
    Node<T>* node1 = head;
    Node<T>* node2 = list.head;
    while (node1 != nullptr)
    {
        concat_list->append(node1->data);
        node1 = node1->next;
    }
    while (node2 != nullptr)
    {
        concat_list->append(node2->data);
        node2 = node2->next;
    }
    return concat_list;
}
template <class T>
int LinkedList<T>::get_length() {
    int kol_vo = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        ++kol_vo;
        current = current->next;
    }
    return kol_vo;
}
template <class T>
void LinkedList<T>::append(const T& item) {
    Node<T>* new_node = new Node<T>;
    new_node->data = item;
    new_node->next = nullptr;
    Node<T>* current = head;
    if (current != nullptr) {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
    else
        head = new_node;
}
template <class T>
void LinkedList<T>::set(const T& item, int index) {
    Node<T>* current = head;
    Node<T>* current1 = head;
    int kol_vo = 0, k = 0;
    while (current != nullptr) {
        current = current->next;
        ++kol_vo;
    }
    try {
        if ((index < 0) || (index > kol_vo - 1))
            throw (index);
        while (current1 != nullptr) {
            if (k == index) {
                current1->data = item;
                return;
            }
            else {
                ++k;
                current1 = current1->next;
            }
        }
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество элементов в последовательности - " << kol_vo << ". Установку " << item << " на место " << index << " осуществить невозможно!" << endl;
        cout << endl;
    }
}
template <class T>
void LinkedList<T>::prepend(const T& item) {
    Node<T>* new_node = new Node<T>;
    new_node->data = item;
    new_node->next = head;
    head = new_node;
}
template <class T>
void LinkedList<T>::insert_at(const T& item, int index) {
    Node<T>* node = head;
    int kol_vo = 0;
    while (node != nullptr) {
        node = node->next;
        ++kol_vo;
    }
    try {
        if ((index < 0) || (index > kol_vo))
            throw (index);
        Node<T>* new_node = new Node<T>;
        new_node->data = item;
        new_node->next = nullptr;
        Node<T>* current = head;
        Node<T>* current1 = nullptr;
        int k = 0;
        if (index > 0) {
            while (k != index - 1) {
                current = current->next;
                ++k;
            }
            current1 = current->next;
            current->next = new_node;
            current = current->next;
            current->next = current1;
        }
        if (index == 0) {
            new_node->next = head;
            head = new_node;
        }
    }
    catch (int index) {
        cout << endl;
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество элементов в последовательности - " << kol_vo << ". Вставку осуществить невозможно!" << endl;
    }
}
template <class T>
void LinkedList<T>::remove_first() {
    Node<T>* current = head;
    try {
        if (current != nullptr) {
            head = head->next;
            delete current;
        }
        else
            throw (0);
    }
    catch (int number) {
        cout << "Первый элемент удалить невозможно, поскольку длина последовательности, равна " << number << endl;
    }
}