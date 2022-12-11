#include "library.h"
#include "bst.h"
#include "global.h"

template <class T>
BSTNode<T>::BSTNode() {
    left = nullptr;
    right = nullptr;
    data = 0;
    index_of_node_in_sparse_vector = 0;
}
template <class T>
BSTNode<T>::BSTNode(T item) {
    left = nullptr;
    right = nullptr;
    data = item;
    index_of_node_in_sparse_vector = 0;
}

template <class T>
BST<T>::BST() {
    root = nullptr;
    index_of_element_in_sparse_vector = 0;
};

template <class T>
bool BST<T>::is_empty() {
    if (root == nullptr)
        return true;
    return false;
}
template <class T>
bool BST<T>::is_the_vector_empty() {
    if (root == nullptr) {
        if (index_of_element_in_sparse_vector == 0)
            return true;
        return false;
    }
    return false;
}
template <class T>
const T& BST<T>::get_first() {
    BSTNode<T>* current = root;
    try {
        if (current == nullptr)
            throw (0);
        while (current->left != nullptr)
            current = current->left;
        return current->data;
    }
    catch (int number) {
        cout << "Первый элемент получить невозможно, поскольку длина последовательности, равна ";
        return number;
    }
}
template <class T>
const T& BST<T>::get_last() {
    BSTNode<T>* current = root;
    try {
        if (current == nullptr)
            throw (0);
        while (current->right != nullptr)
            current = current->right;
        return current->data;
    }
    catch (int number) {
        cout << "Последний элемент получить невозможно, поскольку длина последовательности, равна ";
        return number;
    }
}
template <class T>
int BST<T>::get_length() {
    return this->amount(root);
}
template <class T>
int BST<T>::amount(BSTNode<T>* current) {
    if (current == nullptr)
        return 0;
    return amount(current->right) + amount(current->left) + 1;
}
template <class T>
int BST<T>::get_length_of_vector() {
    return index_of_element_in_sparse_vector;
}
template <class T>
void BST<T>::append(const T& item) {
    if (root == nullptr) {
        root = new BSTNode<T>(item);
        ++index_of_element_in_sparse_vector;
        return;
    }
    BSTNode<T>* current = root;
    while (current != nullptr) {
        if (item <= current->data) {
            if (current->left == nullptr) {
                current->left = new BSTNode<T>(item);
                current->left->index_of_node_in_sparse_vector = index_of_element_in_sparse_vector;
                ++index_of_element_in_sparse_vector;
                return;
            }
            else
                current = current->left;
        }
        else {
            if (current->right == nullptr) {
                current->right = new BSTNode<T>(item);
                current->right->index_of_node_in_sparse_vector = index_of_element_in_sparse_vector;
                ++index_of_element_in_sparse_vector;
                return;
            }
            else
                current = current->right;
        }
    }
}
template <class T>
void BST<T>::add(const T& item) {
    if (item != 0)
        append(item);
    else ++index_of_element_in_sparse_vector;
}
template <class T>
void BST<T>::is_present(BSTNode<T>* current, const T& item) {
    if (current != nullptr) {
        is_present(current->left, item);
        if (current->data == item)
            file << "*";
        is_present(current->right, item);
    }
}
template <class T>
bool BST<T>::is_present_in_BST(const T& item) {
    string name_of_file = "important";
    string str, str1;
    file.open(name_of_file, fstream::out);
    if (!file.is_open())
        cout << "Ошибка открытия файла!" << endl;
    else
        is_present(root, item);
    file.close();
    file.open(name_of_file, fstream::in);
    if (!file.is_open())
        cout << "Ошибка открытия файла!" << endl;
    else
        getline(file, str);
    file.close();
    file.open(name_of_file, fstream::out);
    if (!file.is_open())
        cout << "Ошибка открытия файла!" << endl;
    else
        while (getline(file, str1))
            file << " ";
    file.close();
    if (str.empty())
        return false;
    else return true;
}
template <class T>
bool BST<T>::has_a_null_element_been_inserted() {
    if (index_of_element_in_sparse_vector == 0)
        return false;
    int kol_vo = 0;
    for (int i = 0; i < index_of_element_in_sparse_vector; i++)
        if (this->get_item_from_sparse_vector(i) == 0)
            ++kol_vo;
    if (kol_vo == 0)
        return false;
    return true;
}
template <class T>
void BST<T>::remove(const T& item) {
    bool is_here = this->is_present_in_BST(item);
    try {
        if (is_here == false)
            throw (item);
        if (is_here == true) {
            root = delete_node(root, item);
            --index_of_element_in_sparse_vector;
        }
    }
    catch (const T& item) {
        if ((item == 0) && (this->has_a_null_element_been_inserted() == true)) {
            string str = index_of(0);
            int indexer = from_string_to_int(str);
            traversing_with_decreasing_indexes(root, indexer);
            --index_of_element_in_sparse_vector;
        }
        else {
            cout << endl;
            cout << "Удаление элемента " << item << " невозможно, поскольку он не содержится в поледовательности координат вектора!" << endl;
        }
    }
}
template <class T>
BSTNode<T>* BST<T>::max_elem_from_left_subtree(BSTNode<T>* current) {
    while (current->right != nullptr)
        current = current->right;
    return current;
}
template <class T>
const T& BST<T>::get(int index) {
    BSTNode<T>* current = root;
    stack<T> st;
    stack<T> stack_additional;
    T item;
    int counter = 0;
    try {
        if ((index < 0) || (index >= this->get_length()))
            throw (index);
        while ((!st.empty()) || (current != nullptr)) {
            if (current != nullptr) {
                st.push(current->data);
                stack_additional.push(current->index_of_node_in_sparse_vector);
                current = current->left;
            }
            else {
                if (index == counter) {
                    item = st.top();
                    return item;
                }
                ++counter;
                current = pointer_to_node(st.top(), stack_additional.top());
                current = current->right;
                st.pop();
                stack_additional.pop();
            }
        }
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество ненулевых элементов в последовательности - " << this->get_length() << ". Получение элемента осуществить невозможно!" << endl;
        cout << "Работа функции завершилась с кодом ";
        return -1;
    }
}
template <class T>
BSTNode<T>* BST<T>::pointer_to_node(const T& item, int index) {
    BSTNode<T>* current = root;
    while ((current != nullptr) && (current->index_of_node_in_sparse_vector != index)) {
        if (current->data >= item)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}
template <class T>
string BST<T>::index_of(const T& item) {
    BSTNode<T>* current = root;
    stack<T> st;
    stack<T> stack_additional;
    string str, tmp;
    bool is_here = this->is_present_in_BST(item);
    try {
        if (is_here == false)
            throw (item);
        if (is_here == true) {
            while ((!st.empty()) || (current != nullptr)) {
                if (current != nullptr) {
                    st.push(current->data);
                    stack_additional.push(current->index_of_node_in_sparse_vector);
                    current = current->left;
                }
                else {
                    if (st.top() == item) {
                        tmp = to_string(stack_additional.top());
                        str.insert(0, tmp);
                        str.insert(0, " ");
                    }
                    current = pointer_to_node(st.top(), stack_additional.top());
                    current = current->right;
                    st.pop();
                    stack_additional.pop();
                }
            }
            str.erase(0, 1);
            return str;
        }
    }
    catch (const T& item) {
        if ((item == 0) && (this->has_a_null_element_been_inserted() == true)) {
            for (int i = 0; i < index_of_element_in_sparse_vector; i++) {
                if (get_item_from_sparse_vector(i) == 0) {
                    str.append(to_string(i));
                    str.append(" ");
                }
            }
            return str;
        }
        else {
            cout << "Определение индекса элемента " << item << " невозможно, поскольку он не содержится в поледовательности координат вектора!";
            return("");
        }
    }
}
template <class T>
void BST<T>::get_values_from_some_node(BSTNode<T>* current) {
    if (current != nullptr) {
        get_values_from_some_node(current->left);
        cout << current->data << ' ';
        get_values_from_some_node(current->right);
    }
}
template <class T>
void BST<T>::get_values() {
    get_values_from_some_node(root);
}
template <class T>
void BST<T>::get_keys() {
    get_keys_from_some_node(root);
}
template <class T>
void BST<T>::get_keys_from_some_node(BSTNode<T>* current) {
    if (current != nullptr) {
        get_keys_from_some_node(current->left);
        cout << current->index_of_node_in_sparse_vector << ' ';
        get_keys_from_some_node(current->right);
    }
}
template <class T>
void BST<T>::get_subsequence(int startindex, int endindex) {
    try {
        if ((startindex < 0) || (startindex >= this->get_length()) || (endindex < 0) || (endindex >= this->get_length()))
            throw (-1);
        for (int i = startindex; i <= endindex; i++)
            cout << this->get(i) << ' ';
        cout << endl;
    }
    catch (int index) {
        cout << "Введённые вами индексы начала и конца подпоследовательности равны " << startindex << " и " << endindex << ", в то время как общее число элементов равно " << this->get_length() << ". Операцию извлечения подпоследовательности произвести невозможно!" << endl;
        cout << "Работа функции завершилась с кодом " << index << endl;
    }
}
template <class T>
void BST<T>::concat(Sequence<T>& sorted_sequence) {
    for (int i = 0; i < sorted_sequence.get_length(); i++)
        this->add(sorted_sequence.get(i));
}
template <class T>
BSTNode<T>* BST<T>::delete_node(BSTNode<T>* current, const T& item) {
    if (current == nullptr)
        return current;
    if (item < current->data)
        current->left = delete_node(current->left, item);
    else if (item > current->data)
        current->right = delete_node(current->right, item);
    else {
        if (current->left == nullptr) {
            BSTNode<T>* tmp = current->right;
            traversing_with_decreasing_indexes(root, current->index_of_node_in_sparse_vector);
            delete[] current;
            return tmp;
        }
        else if (current->right == nullptr) {
            BSTNode<T>* tmp = current->left;
            traversing_with_decreasing_indexes(root, current->index_of_node_in_sparse_vector);
            delete[] current;
            return tmp;
        }
        else {
            BSTNode<T>* tmp = max_elem_from_left_subtree(current->left);
            current->data = tmp->data;
            swap(tmp->index_of_node_in_sparse_vector, current->index_of_node_in_sparse_vector);
            current->left = delete_node(current->left, tmp->data);
        }
    }
    return current;
}
template <class T>
const T& BST<T>::get_item_from_sparse_vector(int index) {
    BSTNode<T>* current = root;
    stack<T> st;
    stack<T> stack_additional;
    T item;
    int flag = 0;
    try {
        if ((index < 0) || (index >= index_of_element_in_sparse_vector))
            throw (index);
        while ((!st.empty()) || (current != nullptr)) {
            if (current != nullptr) {
                st.push(current->data);
                stack_additional.push(current->index_of_node_in_sparse_vector);
                current = current->left;
            }
            else {
                if (index == stack_additional.top()) {
                    ++flag;
                    item = st.top();
                    return item;
                }
                current = pointer_to_node(st.top(), stack_additional.top());
                current = current->right;
                st.pop();
                stack_additional.pop();
            }
        }
        if (flag == 0)
            return 0;
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как длина вектора - " << this->get_length_of_vector() << ". Получение элемента осуществить невозможно!" << endl;
        cout << "Работа функции завершилась с кодом ";
        return -1;
    }
}
template <class T>
void BST<T>::prepend(const T& item) {
    this->insert_at(item, 0);
}
template <class T>
void BST<T>::insert_at(const T& item, int index) {
    try {
        if ((index < 0) || (index > this->get_length_of_vector()))
            throw (index);
        BST<T> tree;
        for (int i = 0; i < index; i++)
            tree.add(this->get_item_from_sparse_vector(i));
        tree.add(item);
        for (int i = index; i < this->get_length_of_vector(); i++)
            tree.add(this->get_item_from_sparse_vector(i));
        this->root = tree.root;
        index_of_element_in_sparse_vector = tree.index_of_element_in_sparse_vector;
    }
    catch (int index) {
        cout << endl;
        cout << "Введённый вами индекс равен " << index << ", в то время как длина разреженного вектора - " << this->get_length_of_vector() << ". Вставку осуществить невозможно!" << endl;
    }
}
template <class T>
void BST<T>::set(const T& item, int index) {
    try {
        if ((index < 0) || (index >= this->get_length_of_vector()))
            throw (index);
        BST<T> tree;
        for (int i = 0; i < index; i++)
            tree.add(this->get_item_from_sparse_vector(i));
        tree.add(item);
        for (int i = index + 1; i < this->get_length_of_vector(); i++)
            tree.add(this->get_item_from_sparse_vector(i));
        this->root = tree.root;
        index_of_element_in_sparse_vector = tree.index_of_element_in_sparse_vector;
    }
    catch (int index) {
        cout << endl;
        cout << "Введённый вами индекс равен " << index << ", в то время как длина разреженного вектора - " << this->get_length_of_vector() << ". Установку " << item << " на место " << index << " осуществить невозможно!" << endl;
    }
}
template <class T>
void BST<T>::remove_first() {
    T item = this->get_item_from_sparse_vector(0);
    remove(item);
}
template <class T>
void BST<T>::traversing_with_decreasing_indexes(BSTNode<T>* current, int index) {
    if (current != nullptr) {
        traversing_with_decreasing_indexes(current->left, index);
        if (current->index_of_node_in_sparse_vector > index)
            current->index_of_node_in_sparse_vector = current->index_of_node_in_sparse_vector - 1;
        traversing_with_decreasing_indexes(current->right, index);
    }
}