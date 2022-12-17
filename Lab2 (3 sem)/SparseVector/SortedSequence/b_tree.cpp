#include "library.h"
#include "b_tree.h"
#include "global.h"

template <class T>
BTreeNode<T>::BTreeNode(int min_degree, bool _leaf) {
    leaf = _leaf;
    keys = new Keys<T>[2 * min_degree - 1];
    number_of_keys_in_the_current_node = 0;
    children = new BTreeNode<T>*[2 * min_degree];
}

template <class T>
void BTreeNode<T>::insert_in_the_non_full_node(int min_degree, const T& item, int index_of_element_in_sparse_vector) {
    int i = number_of_keys_in_the_current_node - 1;
    if (leaf == true) {
        while ((i >= 0) && (keys[i].key > item)) {
            keys[i + 1].key = keys[i].key;
            keys[i + 1].index_in_sparse_vector = keys[i].index_in_sparse_vector;
            --i;
        }
        keys[i + 1].key = item;
        keys[i + 1].index_in_sparse_vector = index_of_element_in_sparse_vector;
        ++number_of_keys_in_the_current_node;
    }
    else {
        while ((i >= 0) && (keys[i].key > item))
            --i;
        if (children[i + 1]->number_of_keys_in_the_current_node == 2 * min_degree - 1) {
            split_the_child(min_degree, i + 1, children[i + 1]);
            if (keys[i + 1].key < item)
                ++i;
        }
        children[i + 1]->insert_in_the_non_full_node(min_degree, item, index_of_element_in_sparse_vector);
    }
}
template <class T>
void BTreeNode<T>::split_the_child(int min_degree, int i, BTreeNode<T>* node_for_splitting) {
    BTreeNode<T>* new_one = new BTreeNode<T>(min_degree, node_for_splitting->leaf);
    new_one->number_of_keys_in_the_current_node = min_degree - 1;

    for (int j = 0; j < min_degree - 1; j++) {
        new_one->keys[j].key = node_for_splitting->keys[j + min_degree].key;
        new_one->keys[j].index_in_sparse_vector = node_for_splitting->keys[j + min_degree].index_in_sparse_vector;
    }
    if (node_for_splitting->leaf == false)
        for (int j = 0; j < min_degree; j++)
            new_one->children[j] = node_for_splitting->children[j + min_degree];
    node_for_splitting->number_of_keys_in_the_current_node = min_degree - 1;

    for (int j = number_of_keys_in_the_current_node; j >= i + 1; j--)
        children[j + 1] = children[j];
    children[i + 1] = new_one;
    for (int j = number_of_keys_in_the_current_node - 1; j >= i; j--) {
        keys[j + 1].key = keys[j].key;
        keys[j + 1].index_in_sparse_vector = keys[j].index_in_sparse_vector;
    }
    keys[i].key = node_for_splitting->keys[min_degree - 1].key;
    keys[i].index_in_sparse_vector = node_for_splitting->keys[min_degree - 1].index_in_sparse_vector;
    ++number_of_keys_in_the_current_node;
}
template <class T>
const T& BTreeNode<T>::get_first() {
    if (leaf == false)
        children[0]->get_first();
    else return keys[0].key;
}
template <class T>
int BTreeNode<T>::get_first_index() {
    if (leaf == false)
        children[0]->get_first_index();
    else return keys[0].index_in_sparse_vector;
}
template <class T>
const T& BTreeNode<T>::get_last() {
    if (leaf == false)
        children[number_of_keys_in_the_current_node]->get_last();
    else return keys[number_of_keys_in_the_current_node - 1].key;
}
template <class T>
int BTreeNode<T>::get_last_index() {
    if (leaf == false)
        children[number_of_keys_in_the_current_node]->get_last_index();
    else return keys[number_of_keys_in_the_current_node - 1].index_in_sparse_vector;
}

template <class T>
BTree<T>::BTree(int _min_degree) {
    root = nullptr;
    min_degree = _min_degree;
    index_of_element_in_sparse_vector = 0;
}
template <class T>
BTree<T>::BTree() {
    root = nullptr;
    min_degree = 2;
    index_of_element_in_sparse_vector = 0;
}

template <class T>
void BTree<T>::add_min_degree(int _min_degree) {
    min_degree = _min_degree;
}
template <class T>
void BTree<T>::traverse() {
    traverse_from_some_node(root);
}
template <class T>
void BTree<T>::traverse_from_some_node(BTreeNode<T>* current) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                traverse_from_some_node(current->children[i]);
            cout << current->keys[i].key << ' ';
        }
        if (current->leaf == false)
            traverse_from_some_node(current->children[i]);
    }
}
template <class T>
BTreeNode<T>* BTree<T>::search(const T& item) {
    if (root == nullptr)
        return nullptr;
    else
        return search_from_some_node(root, item);
}
template <class T>
BTreeNode<T>* BTree<T>::search_from_some_node(BTreeNode<T>* current, const T& item) {
    int i = 0;
    while ((i < current->number_of_keys_in_the_current_node) && (item > current->keys[i].key))
        ++i;
    if (current->keys[i].key == item)
        return current;
    if (current->leaf == true)
        return nullptr;
    return search_from_some_node(current->children[i], item);
}
template <class T>
void BTree<T>::append(const T& item) {
    if (root == nullptr) {
        root = new BTreeNode<T>(min_degree, true);
        root->keys[0].key = item;
        root->keys[0].index_in_sparse_vector = index_of_element_in_sparse_vector;
        ++index_of_element_in_sparse_vector;
        root->number_of_keys_in_the_current_node = 1;
    }
    else {
        if (root->number_of_keys_in_the_current_node == 2 * min_degree - 1) {
            BTreeNode<T>* tmp = new BTreeNode<T>(min_degree, false);
            tmp->children[0] = root;
            tmp->split_the_child(min_degree, 0, root);
            int i = 0;
            if (tmp->keys[0].key < item)
                i++;
            tmp->children[i]->insert_in_the_non_full_node(min_degree, item, index_of_element_in_sparse_vector);
            ++index_of_element_in_sparse_vector;
            root = tmp;
        }
        else {
            root->insert_in_the_non_full_node(min_degree, item, index_of_element_in_sparse_vector);
            ++index_of_element_in_sparse_vector;
        }
    }
}
template <class T>
bool BTree<T>::is_empty() {
    if (root == nullptr)
        return true;
    return false;
}
template <class T>
bool BTree<T>::is_the_vector_empty() {
    if (root == nullptr) {
        if (index_of_element_in_sparse_vector == 0)
            return true;
        return false;
    }
    return false;
}
template <class T>
const T& BTree<T>::get_first() {
    if (root != nullptr)
        return root->get_first();
    else {
        cout << "Первый элемент получить невозможно, поскольку длина последовательности, равна ";
        return 0;
    }
}
template <class T>
const T& BTree<T>::get_last() {
    if (root != nullptr)
        return root->get_last();
    else {
        cout << "Последний элемент получить невозможно, поскольку длина последовательности, равна ";
        return 0;
    }
}
template <class T>
int BTree<T>::get_length_of_vector() {
    return index_of_element_in_sparse_vector;
}
template <class T>
void BTree<T>::add(const T& item) {
    if (item != 0)
        append(item);
    else ++index_of_element_in_sparse_vector;
}
template <class T>
void BTree<T>::get_subsequence(int startindex, int endindex) {
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
void BTree<T>::get_keys_from_some_node(BTreeNode<T>* current) {
    int i;
    if (current != nullptr) {
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                get_keys_from_some_node(current->children[i]);
            cout << current->keys[i].index_in_sparse_vector << ' ';
        }
        if (current->leaf == false)
            get_keys_from_some_node(current->children[i]);
    }
}
template <class T>
void BTree<T>::get_keys() {
    get_keys_from_some_node(root);
}
template <class T>
void BTree<T>::get_values_from_some_node(BTreeNode<T>* current) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                traverse_from_some_node(current->children[i]);
            cout << current->keys[i].key << ' ';
        }
        if (current->leaf == false)
            traverse_from_some_node(current->children[i]);
    }
}
template <class T>
void BTree<T>::get_values() {
    get_values_from_some_node(root);
}
template <class T>
void BTree<T>::length(BTreeNode<T>* current) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                length(current->children[i]);
            file << "*";
        }
        if (current->leaf == false)
            length(current->children[i]);
    }
}
template <class T>
int BTree<T>::get_length() {
    string name_of_file = "length";
    string str, str1;
    file.open(name_of_file, fstream::out);
    if (!file.is_open())
        cout << "Ошибка открытия файла!" << endl;
    else
        length(root);
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
    return str.length();
}
template <class T>
void BTree<T>::get_item_from_some_node(BTreeNode<T>* current, int index) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                get_item_from_some_node(current->children[i], index);
            if (counter == index) {
                file << current->keys[i].key << ' ';
            }
            ++counter;
        }
        if (current->leaf == false)
            get_item_from_some_node(current->children[i], index);
    }
}
template <class T>
const T& BTree<T>::get(int index) {
    string name_of_file = "important";
    string str, str1;
    try {
        if ((index < 0) || (index >= this->get_length()))
            throw (index);
        file.open(name_of_file, fstream::out);
        if (!file.is_open())
            cout << "Ошибка открытия файла!" << endl;
        else
            get_item_from_some_node(root, index);
        file.close();
        counter = 0;
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
        return from_string_to_int(str);
    }
    catch (int index) {
        cout << "Введённый вами индекс равен " << index << ", в то время как общее количество ненулевых элементов в последовательности - " << this->get_length() << ". Получение элемента осуществить невозможно!" << endl;
        cout << "Работа функции завершилась с кодом ";
        return -1;
    }
}
template <class T>
void BTree<T>::index_of_in_btree(BTreeNode<T>* current, const T& item) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                index_of_in_btree(current->children[i], item);
            if (current->keys[i].key == item)
                file << current->keys[i].index_in_sparse_vector << ' ';
        }
        if (current->leaf == false)
            index_of_in_btree(current->children[i], item);
    }
}
template <class T>
string BTree<T>::index_of(const T& item) {
    string name_of_file = "important";
    string str, str1;
    bool is_here = this->is_present_in_BTree(item);
    try {
        if (is_here == false)
            throw (item);
        if (is_here == true) {
            file.open(name_of_file, fstream::out);
            if (!file.is_open())
                cout << "Ошибка открытия файла!" << endl;
            else
                index_of_in_btree(root, item);
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
void BTree<T>::get_item_from_vector(BTreeNode<T>* current, int index) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                get_item_from_vector(current->children[i], index);
            if (index == current->keys[i].index_in_sparse_vector) {
                file << current->keys[i].key << ' ';
            }
        }
        if (current->leaf == false)
            get_item_from_vector(current->children[i], index);
    }
}
template <class T>
const T& BTree<T>::get_item_from_sparse_vector(int index) {
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
void BTree<T>::prepend(const T& item) {
    this->insert_at(item, 0);
}
template <class T>
void BTree<T>::insert_at(const T& item, int index) {
    try {
        if ((index < 0) || (index > this->get_length_of_vector()))
            throw (index);
        BTree<T> tree(min_degree);
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
void BTree<T>::set(const T& item, int index) {
    try {
        if ((index < 0) || (index >= this->get_length_of_vector()))
            throw (index);
        BTree<T> tree(min_degree);
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
void BTree<T>::concat(Sequence<T>& sorted_sequence) {
    for (int i = 0; i < sorted_sequence.get_length(); i++)
        this->add(sorted_sequence.get(i));
}
template <class T>
int BTree<T>::find_a_key(BTreeNode<T>* current, const T& item) {
    int index = 0;
    while ((index < current->number_of_keys_in_the_current_node) && (item > current->keys[index].key))
        ++index;
    return index;
}
template <class T>
void BTree<T>::borrow_from_left_sibling(BTreeNode<T>* current, int index) {
    BTreeNode<T>* child = current->children[index];
    BTreeNode<T>* left_sibling = current->children[index - 1];

    for (int i = child->number_of_keys_in_the_current_node - 1; i >= 0; i--) {
        child->keys[i + 1].key = child->keys[i].key;
        child->keys[i + 1].index_in_sparse_vector = child->keys[i].index_in_sparse_vector;
    }
    if (!child->leaf)
        for (int i = child->number_of_keys_in_the_current_node; i >= 0; i--)
            child->children[i + 1] = child->children[i];
    child->keys[0].key = current->keys[index - 1].key;
    child->keys[0].index_in_sparse_vector = current->keys[index - 1].index_in_sparse_vector;
    if (!child->leaf)
        child->children[0] = left_sibling->children[left_sibling->number_of_keys_in_the_current_node];
    current->keys[index - 1].key = left_sibling->keys[left_sibling->number_of_keys_in_the_current_node - 1].key;
    current->keys[index - 1].index_in_sparse_vector = left_sibling->keys[left_sibling->number_of_keys_in_the_current_node - 1].index_in_sparse_vector;
    child->number_of_keys_in_the_current_node = child->number_of_keys_in_the_current_node + 1;
    left_sibling->number_of_keys_in_the_current_node = left_sibling->number_of_keys_in_the_current_node - 1;
}
template <class T>
void BTree<T>::borrow_from_right_sibling(BTreeNode<T>* current, int index) {
    BTreeNode<T>* child = current->children[index];
    BTreeNode<T>* right_sibling = current->children[index + 1];

    child->keys[child->number_of_keys_in_the_current_node].key = current->keys[index].key;
    child->keys[child->number_of_keys_in_the_current_node].index_in_sparse_vector = current->keys[index].index_in_sparse_vector;
    if (!child->leaf)
        child->children[child->number_of_keys_in_the_current_node + 1] = right_sibling->children[0];
    current->keys[index].key = right_sibling->keys[0].key;
    current->keys[index].index_in_sparse_vector = right_sibling->keys[0].index_in_sparse_vector;
    for (int i = 0; i < right_sibling->number_of_keys_in_the_current_node - 1; i++) {
        right_sibling->keys[i].key = right_sibling->keys[i + 1].key;
        right_sibling->keys[i].index_in_sparse_vector = right_sibling->keys[i + 1].index_in_sparse_vector;
    }
    if (!right_sibling->leaf)
        for (int i = 0; i < right_sibling->number_of_keys_in_the_current_node; i++)
            right_sibling->children[i] = right_sibling->children[i + 1];
    child->number_of_keys_in_the_current_node = child->number_of_keys_in_the_current_node + 1;
    right_sibling->number_of_keys_in_the_current_node = right_sibling->number_of_keys_in_the_current_node - 1;
}
template <class T>
void BTree<T>::merge(BTreeNode<T>* current, int index) {
    BTreeNode<T>* child = current->children[index];
    BTreeNode<T>* sibling = current->children[index + 1];

    child->keys[min_degree - 1].key = current->keys[index].key;
    child->keys[min_degree - 1].index_in_sparse_vector = current->keys[index].index_in_sparse_vector;
    for (int i = 0; i < sibling->number_of_keys_in_the_current_node; i++) {
        child->keys[i + min_degree].key = sibling->keys[i].key;
        child->keys[i + min_degree].index_in_sparse_vector = sibling->keys[i].index_in_sparse_vector;
    }
    if (!child->leaf)
        for (int i = 0; i <= sibling->number_of_keys_in_the_current_node; i++)
            child->children[i + min_degree] = sibling->children[i];
    for (int i = index; i < current->number_of_keys_in_the_current_node - 1; i++) {
        current->keys[i].key = current->keys[i + 1].key;
        current->keys[i].index_in_sparse_vector = current->keys[i + 1].index_in_sparse_vector;
    }
    for (int i = index + 1; i < current->number_of_keys_in_the_current_node; i++)
        current->children[i] = current->children[i + 1];
    child->number_of_keys_in_the_current_node = child->number_of_keys_in_the_current_node + sibling->number_of_keys_in_the_current_node + 1;
    current->number_of_keys_in_the_current_node = current->number_of_keys_in_the_current_node - 1;
    delete sibling;
}
template <class T>
void BTree<T>::extend(BTreeNode<T>* current, int index) {
    if ((index != 0) && (current->children[index - 1]->number_of_keys_in_the_current_node >= min_degree))
        borrow_from_left_sibling(current, index);
    else if ((index != current->number_of_keys_in_the_current_node) && (current->children[index + 1]->number_of_keys_in_the_current_node >= min_degree))
        borrow_from_right_sibling(current, index);
    else {
        if (index != current->number_of_keys_in_the_current_node)
            merge(current, index);
        else merge(current, index - 1);
    }
}
template <class T>
void BTree<T>::remove_from_leaf(BTreeNode<T>* current, int index) {
    for (int i = index; i < current->number_of_keys_in_the_current_node - 1; i++) {
        current->keys[i].key = current->keys[i + 1].key;
        current->keys[i].index_in_sparse_vector = current->keys[i + 1].index_in_sparse_vector;
    }
    current->number_of_keys_in_the_current_node = current->number_of_keys_in_the_current_node - 1;
}
template <class T>
void BTree<T>::change_the_index(BTreeNode<T>* current, int index, int new_one) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                change_the_index(current->children[i], index, new_one);
            if (current->keys[i].index_in_sparse_vector == index)
                current->keys[i].index_in_sparse_vector = new_one;
        }
        if (current->leaf == false)
            change_the_index(current->children[i], index, new_one);
    }
}
template <class T>
void BTree<T>::remove_from_some_node(BTreeNode<T>* current, const T& item, int _index) {
    int index = find_a_key(current, item);
    if ((index < current->number_of_keys_in_the_current_node) && (current->keys[index].key == item)) {
        if (current->keys[index].index_in_sparse_vector != _index) {
            int _index_ = current->keys[index].index_in_sparse_vector;
            change_the_index(root, _index, _index_);
            current->keys[index].index_in_sparse_vector = _index;
        }
        if (current->leaf)
            remove_from_leaf(current, index);
        else remove_from_non_leaf(current, index, _index);
    }
    else {
        bool flag = (index == current->number_of_keys_in_the_current_node) ? true : false;
        if (current->children[index]->number_of_keys_in_the_current_node < min_degree)
            extend(current, index);
        if ((flag) && (index > current->number_of_keys_in_the_current_node))
            remove_from_some_node(current->children[index - 1], item, _index);
        else remove_from_some_node(current->children[index], item, _index);
    }
}
template <class T>
int BTree<T>::get_index_of_del_elem(BTreeNode<T>* current, const T& item) {
    int index = find_a_key(current, item);
    if ((index < current->number_of_keys_in_the_current_node) && (current->keys[index].key == item)) {
        return current->keys[index].index_in_sparse_vector;
    }
    else {
        bool flag = (index == current->number_of_keys_in_the_current_node) ? true : false;
        if (current->children[index]->number_of_keys_in_the_current_node < min_degree)
            extend(current, index);
        if ((flag) && (index > current->number_of_keys_in_the_current_node))
            get_index_of_del_elem(current->children[index - 1], item);
        else get_index_of_del_elem(current->children[index], item);
    }
}
template <class T>
void BTree<T>::is_present(BTreeNode<T>* current, const T& item) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                is_present(current->children[i], item);
            if (current->keys[i].key == item)
                file << "*";
        }
        if (current->leaf == false)
            is_present(current->children[i], item);
    }
}
template <class T>
bool BTree<T>::is_present_in_BTree(const T& item) {
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
bool BTree<T>::has_a_null_element_been_inserted() {
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
void BTree<T>::remove(const T& item) {
    bool is_here = this->is_present_in_BTree(item);
    try {
        if (is_here == false)
            throw (item);
        if (is_here == true) {
            int indexer = get_index_of_del_elem(root, item);
            remove_from_some_node(root, item, indexer);
            if (root->number_of_keys_in_the_current_node == 0) {
                BTreeNode<T>* tmp = root;
                if (root->leaf)
                    root = nullptr;
                else root = root->children[0];
                delete tmp;
            }
            traversing_with_decreasing_indexes(root, indexer);
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
void BTree<T>::remove_from_non_leaf(BTreeNode<T>* current, int index, int _indexer) {
    T item = current->keys[index].key;
    if (current->children[index]->number_of_keys_in_the_current_node >= min_degree) {
        T max_from_left_subtree = current->children[index]->get_last();
        int indexer = current->children[index]->get_last_index();
        change_the_index(root, indexer, current->keys[index].index_in_sparse_vector);
        current->keys[index].key = max_from_left_subtree;
        current->keys[index].index_in_sparse_vector = indexer;
        remove_from_some_node(current->children[index], max_from_left_subtree, _indexer);
    }
    else if (current->children[index + 1]->number_of_keys_in_the_current_node >= min_degree) {
        T min_from_right_subtree = current->children[index + 1]->get_first();
        int indexer = current->children[index + 1]->get_first_index();
        change_the_index(root, indexer, current->keys[index].index_in_sparse_vector);
        current->keys[index].key = min_from_right_subtree;
        current->keys[index].index_in_sparse_vector = indexer;
        remove_from_some_node(current->children[index + 1], min_from_right_subtree, _indexer);
    }
    else {
        merge(current, index);
        remove_from_some_node(current->children[index], item, _indexer);
    }
}
template <class T>
void BTree<T>::traversing_with_decreasing_indexes(BTreeNode<T>* current, int index) {
    if (current != nullptr) {
        int i;
        for (i = 0; i < current->number_of_keys_in_the_current_node; i++) {
            if (current->leaf == false)
                traversing_with_decreasing_indexes(current->children[i], index);
            if (current->keys[i].index_in_sparse_vector > index)
                current->keys[i].index_in_sparse_vector = current->keys[i].index_in_sparse_vector - 1;

        }
        if (current->leaf == false)
            traversing_with_decreasing_indexes(current->children[i], index);
    }
}
template <class T>
void BTree<T>::remove_first() {
    T item = this->get_item_from_sparse_vector(0);
    remove(item);
}