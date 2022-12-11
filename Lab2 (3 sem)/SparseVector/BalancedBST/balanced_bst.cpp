#include "library.h"
#include "balanced_bst.h"
#include "global.h"

template <class T>
BalancedBSTNode<T>::BalancedBSTNode() {
    left = nullptr;
    right = nullptr;
    data = 0;
    index_of_node_in_sparse_vector = 0;
}
template <class T>
BalancedBSTNode<T>::BalancedBSTNode(T item) {
    left = nullptr;
    right = nullptr;
    data = item;
    index_of_node_in_sparse_vector = 0;
}

template <class T>
BalancedBST<T>::BalancedBST() {
    root = nullptr;
    index_of_element_in_sparse_vector = 0;
};

template <class T>
bool BalancedBST<T>::is_the_vector_empty() {
    if (root == nullptr) {
        if (index_of_element_in_sparse_vector == 0)
            return true;
        return false;
    }
    return false;
}
template <class T>
int BalancedBST<T>::get_length_of_vector() {
    return index_of_element_in_sparse_vector;
}
template <class T>
void BalancedBST<T>::add(const T& item) {
    if (item != 0)
        root = append(root, item);
    else ++index_of_element_in_sparse_vector;
}
template <class T>
BalancedBSTNode<T>* BalancedBST<T>::append(BalancedBSTNode<T>* current, const T& item) {
    if (current == nullptr) {
        current = new BalancedBSTNode<T>(item);
        current->index_of_node_in_sparse_vector = index_of_element_in_sparse_vector;
        ++index_of_element_in_sparse_vector;
        return current;
    }
    if (current->data >= item)
        current->left = append(current->left, item);
    else current->right = append(current->right, item);
    int balance_factor = this->get_balance_factor(current);
    if ((balance_factor > 1) && (item <= current->left->data))
        return right_rotate(current);
    if ((balance_factor < -1) && (item > current->right->data))
        return left_rotate(current);
    if ((balance_factor > 1) && (item > current->left->data)) {
        current->left = left_rotate(current->left);
        return right_rotate(current);
    }
    if ((balance_factor < -1) && (item <= current->right->data)) {
        current->right = right_rotate(current->right);
        return left_rotate(current);
    }
    return current;
}
template <class T>
BalancedBSTNode<T>* BalancedBST<T>::max_elem_from_left_subtree(BalancedBSTNode<T>* current) {
    while (current->right != nullptr)
        current = current->right;
    return current;
}
template <class T>
void BalancedBST<T>::is_present(BalancedBSTNode<T>* current, const T& item) {
    if (current != nullptr) {
        is_present(current->left, item);
        if (current->data == item)
            file << "*";
        is_present(current->right, item);
    }
}
template <class T>
bool BalancedBST<T>::is_present_in_balancedBST(const T& item) {
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
bool BalancedBST<T>::has_a_null_element_been_inserted() {
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
void BalancedBST<T>::remove(const T& item) {
    bool is_here = this->is_present_in_balancedBST(item);
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
BalancedBSTNode<T>* BalancedBST<T>::delete_node(BalancedBSTNode<T>* current, const T& item) {
    if (current == nullptr)
        return current;
    if (current->data > item)
        current->left = delete_node(current->left, item);
    else if (current->data < item)
        current->right = delete_node(current->right, item);
    else {
        if (current->left == nullptr) {
            BalancedBSTNode<T>* tmp = current->right;
            traversing_with_decreasing_indexes(root, current->index_of_node_in_sparse_vector);
            delete[] current;
            return tmp;
        }
        else if (current->right == nullptr) {
            BalancedBSTNode<T>* tmp = current->left;
            traversing_with_decreasing_indexes(root, current->index_of_node_in_sparse_vector);
            delete[] current;
            return tmp;
        }
        else {
            BalancedBSTNode<T>* tmp = max_elem_from_left_subtree(current->left);
            current->data = tmp->data;
            swap(tmp->index_of_node_in_sparse_vector, current->index_of_node_in_sparse_vector);
            current->left = delete_node(current->left, tmp->data);
        }
    }
    int balance_factor = this->get_balance_factor(current);
    if ((balance_factor == 2) && (this->get_balance_factor(current->left) >= 0))
        return right_rotate(current);
    else if ((balance_factor == 2) && (this->get_balance_factor(current->left) == -1)) {
        current->left = left_rotate(current->left);
        return right_rotate(current);
    }
    else if ((balance_factor == -2) && (this->get_balance_factor(current->left) <= 0))
        return left_rotate(current);
    else if ((balance_factor == -2) && (this->get_balance_factor(current->left) == 1)) {
        current->right = right_rotate(current->right);
        return left_rotate(current);
    }
    return current;
}
template <class T>
int BalancedBST<T>::height(BalancedBSTNode<T>* current) {
    if (current == nullptr)
        return -1;
    int left_hight = height(current->left);
    int right_hight = height(current->right);
    return max(left_hight, right_hight) + 1;
}
template <class T>
int BalancedBST<T>::get_balance_factor(BalancedBSTNode<T>* current) {
    if (current == nullptr)
        return -1;
    return height(current->left) - height(current->right);
}
template <class T>
BalancedBSTNode<T>* BalancedBST<T>::left_rotate(BalancedBSTNode<T>* x) {
    BalancedBSTNode<T>* y = x->right;
    BalancedBSTNode<T>* tmp = y->left;
    y->left = x;
    x->right = tmp;
    return y;
}
template <class T>
BalancedBSTNode<T>* BalancedBST<T>::right_rotate(BalancedBSTNode<T>* x) {
    BalancedBSTNode<T>* y = x->left;
    BalancedBSTNode<T>* tmp = y->right;
    y->right = x;
    x->left = tmp;
    return y;
}
template <class T>
void BalancedBST<T>::get_item_from_vector(BalancedBSTNode<T>* current, int index) {
    if (current != nullptr) {
        get_item_from_vector(current->left, index);
        if (current->index_of_node_in_sparse_vector == index)
            file << current->data << ' ';
        get_item_from_vector(current->right, index);
    }
}
template <class T>
const T& BalancedBST<T>::get_item_from_sparse_vector(int index) {
    string name_of_file = "important";
    string str, str1;
    try {
        if ((index < 0) || (index >= index_of_element_in_sparse_vector))
            throw (index);
        file.open(name_of_file, fstream::out);
        if (!file.is_open())
            cout << "Ошибка открытия файла!" << endl;
        else
            get_item_from_vector(root, index);
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
            return 0;
        else return from_string_to_int(str);
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как длина вектора - " << this->get_length_of_vector() << ". Получение элемента осуществить невозможно!" << endl;
        cout << "Работа функции завершилась с кодом ";
        return -1;
    }
}
template <class T>
void BalancedBST<T>::index_of_in_balancedBST(BalancedBSTNode<T>* current, const T& item) {
    if (current != nullptr) {
        index_of_in_balancedBST(current->left, item);
        if (current->data == item)
            file << current->index_of_node_in_sparse_vector << ' ';
        index_of_in_balancedBST(current->right, item);
    }
}
template <class T>
string BalancedBST<T>::index_of(const T& item) {
    string name_of_file = "important";
    string str, str1;
    bool is_here = this->is_present_in_balancedBST(item);
    try {
        if (is_here == false)
            throw (item);
        if (is_here == true) {
            file.open(name_of_file, fstream::out);
            if (!file.is_open())
                cout << "Ошибка открытия файла!" << endl;
            else
                index_of_in_balancedBST(root, item);
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
void BalancedBST<T>::insert_at(const T& item, int index) {
    try {
        if ((index < 0) || (index > this->get_length_of_vector()))
            throw (index);
        BalancedBST<T> tree;
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
void BalancedBST<T>::prepend(const T& item) {
    this->insert_at(item, 0);
}
template <class T>
void BalancedBST<T>::concat(Sequence<T>& sorted_sequence) {
    for (int i = 0; i < sorted_sequence.get_length(); i++)
        this->add(sorted_sequence.get(i));
}
template <class T>
void BalancedBST<T>::get_values_from_some_node(BalancedBSTNode<T>* current) {
    if (current != nullptr) {
        get_values_from_some_node(current->left);
        cout << current->data << ' ';
        get_values_from_some_node(current->right);
    }
}
template <class T>
void BalancedBST<T>::get_values() {
    get_values_from_some_node(root);
}
template <class T>
void BalancedBST<T>::get_keys() {
    get_keys_from_some_node(root);
}
template <class T>
void BalancedBST<T>::get_keys_from_some_node(BalancedBSTNode<T>* current) {
    if (current != nullptr) {
        get_keys_from_some_node(current->left);
        cout << current->index_of_node_in_sparse_vector << ' ';
        get_keys_from_some_node(current->right);
    }
}
template <class T>
void BalancedBST<T>::traversing_with_decreasing_indexes(BalancedBSTNode<T>* current, int index) {
    if (current != nullptr) {
        traversing_with_decreasing_indexes(current->left, index);
        if (current->index_of_node_in_sparse_vector > index)
            current->index_of_node_in_sparse_vector = current->index_of_node_in_sparse_vector - 1;
        traversing_with_decreasing_indexes(current->right, index);
    }
}