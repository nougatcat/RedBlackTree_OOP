
/*
    Описание публичных методов красно-черного дерева

tree_search(key) - ищет, есть ли в дереве такой ключ
insert(key) - добавление нового узла в дерево. На входе принимает ключ
_delete(key) - удаление узла из дерева по ключу.
in_order() - вывод всех ключей дерева в порядке возрастания

*/






#include <iostream>
#include "redblacktree.h"
#include <ctime>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");

    ////////////////ТЕСТ ВСЕХ ЧЕТЫРЕХ МЕТОДОВ//////////////////
    cout << "Введите количество элементов, которое хотите вручную добавить в дерево\n";
    int n;
    cin >> n;
    RBT<int> T;
    int v;
    for (int i = 0; i < n; i++)
    {
        cin >> v;
        T.insert(v);
    }
    T.in_order();
    cout << "Удалим число (если оно есть в дереве): " << 8 << endl;
    T._delete(8);
    cout << "Если есть ключ 7, то выдаст 1: " << T.tree_search(7) << endl;
    cout << "Если есть ключ 8, то выдаст 1: " << T.tree_search(8) << endl;
    cout << "Вывод всех оставшихся элементов\n";
    T.in_order();
    cout << endl;
    //////////////////////////////////////////

    /*
    cout << " Фальшивый КОНСТРУКТОР КОПИРОВАНИЯ\n";
    //RBT<int> test2;
    RBT<int> test = T;
    //RBT<int> test = test2;
    test.insert(2);
    test.in_order();
    cout << "/////////////////////\n";
    */

    cout << "Добавим в дерево 100 ключей - от 0 до 99\n";
    for (int i = 0; i < 100; i++)
    {
        T.insert(i);
    }
    T.in_order();


    cout << "Проверка char\n";
    RBT<char> LetterTree;
    char letArr[10] = { 'S','C','W','D','E','A','G','H','Y','J' };
    for (int i = 0; i < 10; i++)
    {
        LetterTree.insert(letArr[i]);
    }
    LetterTree.in_order();
    cout << endl;

    cout << "Проверка double\n";
    RBT<double> DoubleTree;
    double dArr[10] = {1.3,1.5,12.5,11.9,1.09,124.2,12.4,99.11,65,41.124};
    for (int i = 0; i < 10; i++)
    {
        DoubleTree.insert(dArr[i]);
    }
    DoubleTree.in_order();
    cout << endl;



    //////////////ПРОВЕРКА СКОРОСТИ РАБОТЫ///////////////////
    cout << "Проверим скорость вставки 10К элементов\n";
    RBT<int> InsTree;
    clock_t t1 = clock();
    for (int i = 0; i < 10000; i++)
    {
        InsTree.insert(i);
    }
    clock_t t2 = clock();
    cout << (t2 - t1 + .0) / CLOCKS_PER_SEC << " сек. затрачено на добавление 10К элементов в к-ч дерево " << endl;
    t2 = 0; t1 = 0;
    //////////////////////////
    cout << "Проверим скорость удаления 10К элементов\n";
    t1 = clock();
    for (int i = 0; i < 10000; i++)
    {
        InsTree._delete(i);
    }
    t2 = clock();
    cout << (t2 - t1 + .0) / CLOCKS_PER_SEC << " сек. затрачено на удаление 10К элементов из к-ч дерево " << endl;
    t2 = 0; t1 = 0;
    ////////////////////////////////////////////////////

    /*
    t1 = clock();
    int array[10000];
    for (int i = 0; i < 10000; i++)
    {
        array[i] = i;
    }
    int array2[10001];
    for (int i = 0; i < 10000; i++)
    {
        array2[i] = array[i];
    }
    array2[10000] = 10000;
    t2 = clock();
    cout << (t2 - t1 + .0) / CLOCKS_PER_SEC << " сек. затрачено на  " << endl;
    t2 = 0; t1 = 0;
    */
    int exit;
    cin >> exit;
    return 0;

}

