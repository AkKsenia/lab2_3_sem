#include "library.h"
#include "dynamic_array.cpp"
#include "linked_list.cpp"
#include "sequence.h"
#include "array_sequence.cpp"
#include "linked_list_sequence.cpp"
#include "sparse_vector.h"
#include "sorted_sequence.h"
#include "balanced_bst.cpp"
#include "bst.cpp"
#include "b_tree.cpp"
#include "global.h"
fstream file;


int from_string_to_int(string str) {
    int kol_vo = 0;
    for (int i = 0; str[i] != ' '; i++)
        ++kol_vo;
    for (int i = 0; i < kol_vo; i++)
        str.erase(kol_vo);
    return stoi(str);
}
void fill_the_file(string name_of_file) {
    string str;
    int buf[100000];
    for (int i = 0; i < 100000; i++)
        buf[i] = 0;
    for (int i = 0; i < 10000; i++)
        buf[rand() % 100000] = 1 + rand() % 10000;
    file.open(name_of_file, fstream::out);
    if (!file.is_open())
        cout << "Ошибка открытия файла!" << endl;
    else
        for (int i = 0; i < 100000; i++)
            file << buf[i] << " ";
    file.close();
}
string the_remaining_part_of_the_line(string str) {
    int kol_vo = 0;
    for (int i = 0; str[i] != ' '; i++)
        ++kol_vo;
    str.erase(0, kol_vo + 1);
    return str;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int option0 = 0, option1 = 0, option2, option3, option4;

    int min_degree;

    BST<int> tree1;
    BTree<int> tree2;
    BalancedBST<int> tree3;
    SparseVector<int>* sp_vector = nullptr;

    int coordinate, item, index, counter = 0;
    int index_beginning, index_ending;

    LinkedListSequence<int> list1;
    Sequence<int>* concat_sequence = &list1;

    string name_of_file = "coordinate";
    string str, str1;

    high_resolution_clock::time_point t_start, t_end;
    duration<double> time_span1, time_span2, time_span3, time_span4, time_span5, time_span6, time_span7, time_span8, time_span9, time_span10, time_span11, time_span12, time_span13, time_span14, time_span15, time_span16, time_span17, time_span18;

    int arr_sorted_in_increasing_order[20] = { 0,0,0,3,7,34,56,211,432,523,597,597,612,637,744,876,890,915,987,999 };
    int arr_sorted_in_decreasing_order[20] = { 999,987,915,890,976,744,637,612,597,597,523,532,211,56,34,7,3,0,0,0 };
    int non_sorted_arr[20] = { 890,3,0,7,0,0,56,34,999,211,523,432,597,612,597,637,915,987,744,876};

    BST<int> tree_1;
    BST<int> tree__1;
    BST<int> tree___1;
    SparseVector<int>* sp_vector_1 = &tree_1;
    SparseVector<int>* sp_vector__1 = &tree__1;
    SparseVector<int>* sp_vector___1 = &tree___1;

    BTree<int> tree_2(4);
    BTree<int> tree__2(4);
    BTree<int> tree___2(4);
    SparseVector<int>* sp_vector_2 = &tree_2;
    SparseVector<int>* sp_vector__2 = &tree__2;
    SparseVector<int>* sp_vector___2 = &tree___2;

    BalancedBST<int> tree_3;
    BalancedBST<int> tree__3;
    BalancedBST<int> tree___3;
    SparseVector<int>* sp_vector_3 = &tree_3;
    SparseVector<int>* sp_vector__3 = &tree__3;
    SparseVector<int>* sp_vector___3 = &tree___3;


    cout << endl;
    cout << "РАБОТА С РАЗРЕЖЕННЫМИ ВЕКТОРАМИ" << endl;
    cout << "-----------------------------" << endl;
    cout << endl;
    do {
        cout << "Необходимо задать способ посторения вектора. Выберите нужную опцию из списка ниже:" << endl;
        cout << endl;
        cout << "1 - использовать SortedSequence" << endl;
        cout << "2 - использовать сбалансированное бинарное дерево поиска" << endl;
        cout << endl;
        cin >> option0;
        cout << endl;
        switch (option0) {
        case 1:
            do {
                cout << "Необходимо сделать ещё один выбор:" << endl;
                cout << endl;
                cout << "1 - использовать бинарное дерево поиска" << endl;
                cout << "2 - использовать B-дерево" << endl;
                cout << endl;
                cin >> option1;
                cout << endl;
                switch (option1) {
                case 1:
                    sp_vector = &tree1;
                    break;
                case 2:
                    cout << "Введите минимальную степень B-дерева: ";
                    cin >> min_degree;
                    cout << endl;
                    tree2.add_min_degree(min_degree);
                    sp_vector = &tree2;
                    break;
                default:
                    cout << "Введённый вами номер отсутствует в списке!" << endl;
                    cout << endl;
                    break;
                }
            } while ((option1 != 1) && (option1 != 2));
            break;
        case 2:
            sp_vector = &tree3;
            break;
        default:
            cout << "Введённый вами номер отсутствует в списке!" << endl;
            cout << endl;
            break;
        }
    } while ((option0 != 1) && (option0 != 2));//

    do {
        cout << "Что вы хотите сделать?" << endl;
        cout << endl;
        cout << "1 - узнать, задан ли вектор хотя бы одной координатой" << endl;
        cout << "2 - получить координаты вектора из файла" << endl;
        cout << "3 – задать новую координату" << endl;
        cout << "4 – получить индекс координаты вектора" << endl;
        cout << "5 - удалить координату разреженного вектора" << endl;
        cout << "6 - узнать длину вектора" << endl;
        cout << "7 - выполнить операцию конкатенации" << endl;
        cout << "8 - сравнить алгоритмы поиска и добавления элементов" << endl;
        cout << "9 - отобразить ненулевые координаты вектора" << endl;
        cout << "10 - отобразить индексы, соответствующие ненулевым координатам вектора" << endl;
        cout << "11 - очистить экран" << endl;
        cout << "12 - завершить работу" << endl;

        cout << endl;
        cin >> option2;
        cout << endl;
        switch (option2) {
        case 1:
            if (sp_vector->is_the_vector_empty() == true)
                cout << "Вектор не содержит координат!" << endl;
            else cout << "Вектор содержит по крайней мере одну координату!" << endl;
            cout << endl;
            break;
        case 2:
            fill_the_file(name_of_file);
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
            for (int i = 0; i < 100000; i++) {
                sp_vector->add(from_string_to_int(str));
                str = the_remaining_part_of_the_line(str);
            }
            break;
        case 3:
            do {
                cout << "Выберите действие из списка ниже: " << endl;
                cout << "1 - вставить координату в начало вектора" << endl;
                cout << "2 - вставить координату в конец вектора" << endl;
                cout << "3 - вставить координату по индексу" << endl;
                cout << "4 - завершить вставку" << endl;
                cout << endl;
                cin >> option4;
                switch (option4) {
                case 1:
                    cout << endl;
                    cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                    cin >> item;
                    sp_vector->prepend(item);
                    cout << endl;
                    break;
                case 2:
                    cout << endl;
                    cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                    cin >> item;
                    sp_vector->add(item);
                    cout << endl;
                    break;
                case 3:
                    cout << endl;
                    cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                    cin >> item;
                    cout << endl;
                    cout << "На какое место вы хотите поместить элемент? Введите его: ";
                    cin >> index;
                    sp_vector->insert_at(item, index);
                    cout << endl;
                    break;
                case 4:
                    cout << endl;
                    break;
                default:
                    cout << endl;
                    cout << "Введённый вами номер отсутствует в списке!" << endl;
                    cout << endl;
                    break;
                }
            } while (option4 != 4);
            break;
        case 4:
            cout << "Индекс какой координаты вы хотите получить? Введите её: ";
            cin >> coordinate;
            cout << endl;
            cout << sp_vector->index_of(coordinate) << endl;
            cout << endl;
            break;
        case 5:
            cout << "Какую координату вы хотите удалить? Введите её: ";
            cin >> item;
            sp_vector->remove(item);
            cout << endl;
            break;
        case 6:
            cout << sp_vector->get_length_of_vector() << endl;
            cout << endl;
            break;
        case 7:
            cout << "Для выполнения этой операции необходимо создать последовательность" << endl;
            cout << endl;
            do {
                cout << "Выберите действие из списка ниже: " << endl;
                cout << "1 - вставить элемент в начало" << endl;
                cout << "2 - вставить элемент в конец" << endl;
                cout << "3 - вставить элемент по индексу" << endl;
                cout << "4 - завершить вставку" << endl;
                cout << endl;
                cin >> option3;
                switch (option3) {
                case 1:
                    cout << endl;
                    cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                    cin >> item;
                    concat_sequence->prepend(item);
                    cout << endl;
                    break;
                case 2:
                    cout << endl;
                    cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                    cin >> item;
                    concat_sequence->append(item);
                    cout << endl;
                    break;
                case 3:
                    cout << endl;
                    cout << "Какой элемент вы хотите вставить в последовательность? Введите его: ";
                    cin >> item;
                    cout << endl;
                    cout << "На какое место вы хотите поместить элемент? Введите его: ";
                    cin >> index;
                    cout << endl;
                    concat_sequence->insert_at(item, index);
                    break;
                case 4:
                    cout << endl;
                    break;
                default:
                    cout << endl;
                    cout << "Введённый вами номер отсутствует в списке!" << endl;
                    cout << endl;
                    break;
                }
            } while (option3 != 4);

            sp_vector->concat(*concat_sequence);
            while (concat_sequence->get_length() != 0)
                concat_sequence->remove_first();
            break;
        case 8:
            //BST
            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector_1->add(arr_sorted_in_increasing_order[i]);
            t_end = high_resolution_clock::now();
            time_span1 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector__1->add(arr_sorted_in_decreasing_order[i]);
            t_end = high_resolution_clock::now();
            time_span2 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector___1->add(non_sorted_arr[i]);
            t_end = high_resolution_clock::now();
            time_span3 = duration_cast<duration<double>>(t_end - t_start);


            t_start = high_resolution_clock::now();
            sp_vector_1->index_of(597);
            t_end = high_resolution_clock::now();
            time_span4 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            sp_vector__1->index_of(597);
            t_end = high_resolution_clock::now();
            time_span5 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            sp_vector___1->index_of(597);
            t_end = high_resolution_clock::now();
            time_span6 = duration_cast<duration<double>>(t_end - t_start);

            //BTree
            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector_2->add(arr_sorted_in_increasing_order[i]);
            t_end = high_resolution_clock::now();
            time_span7 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector__2->add(arr_sorted_in_decreasing_order[i]);
            t_end = high_resolution_clock::now();
            time_span8 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector___2->add(non_sorted_arr[i]);
            t_end = high_resolution_clock::now();
            time_span9 = duration_cast<duration<double>>(t_end - t_start);


            t_start = high_resolution_clock::now();
            sp_vector_2->index_of(597);
            t_end = high_resolution_clock::now();
            time_span10 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            sp_vector__2->index_of(597);
            t_end = high_resolution_clock::now();
            time_span11 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            sp_vector___2->index_of(597);
            t_end = high_resolution_clock::now();
            time_span12 = duration_cast<duration<double>>(t_end - t_start);

            //BalancedBST
            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector_3->add(arr_sorted_in_increasing_order[i]);
            t_end = high_resolution_clock::now();
            time_span13 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector__3->add(arr_sorted_in_decreasing_order[i]);
            t_end = high_resolution_clock::now();
            time_span14 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            for (int i = 0; i < 20; i++)
                sp_vector___3->add(non_sorted_arr[i]);
            t_end = high_resolution_clock::now();
            time_span15 = duration_cast<duration<double>>(t_end - t_start);


            t_start = high_resolution_clock::now();
            sp_vector_3->index_of(597);
            t_end = high_resolution_clock::now();
            time_span16 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            sp_vector__3->index_of(597);
            t_end = high_resolution_clock::now();
            time_span17 = duration_cast<duration<double>>(t_end - t_start);

            t_start = high_resolution_clock::now();
            sp_vector___3->index_of(597);
            t_end = high_resolution_clock::now();
            time_span18 = duration_cast<duration<double>>(t_end - t_start);

            file.open("comparison.csv", fstream::out | fstream::in | fstream::app);
            file << "Структура;Время построения дерева;;;Время поиска элемента в дереве;;\n";
            file << ";по отсортированной в нужном порядке последовательности; по отсортированной в обратном порядке последовательности; по неотсортированной последовательности; по отсортированной в нужном порядке последовательности; по отсортированной в обратном порядке последовательности; по неотсортированной последовательности\n";
            file << "BST;" << time_span1.count() << ";" << time_span2.count() << ";" << time_span3.count() << ";" << time_span4.count() << ";" << time_span5.count() << ";" << time_span6.count() << ";" << "\n";
            file << "BTree;" << time_span7.count() << ";" << time_span8.count() << ";"  << time_span9.count() << ";"  << time_span10.count() << ";" << time_span11.count() << ";" << time_span12.count() << ";" << "\n";
            file << "BalancedBST;" << time_span13.count() << ";" << time_span14.count() << ";" << time_span15.count() << ";" << time_span16.count() << ";" << time_span17.count() << ";" << time_span18.count() << ";" << "\n";
            file << "\n";
            file.close();
            cout << "Результаты сравнительного анализа можно увидеть в файле comparison.csv" << endl;
            cout << endl;
            break;
        case 9:
            sp_vector->get_values();
            cout << endl;
            cout << endl;
            break;
        case 10:
            sp_vector->get_keys();
            cout << endl;
            cout << endl;
            break;
        case 11:
            system("cls");
            break;
        case 12:
            break;
        default:
            cout << "Введённый вами номер отсутствует в списке!" << endl;
            cout << endl;
            break;
        }
    } while (option2 != 12);
    return 0;
}