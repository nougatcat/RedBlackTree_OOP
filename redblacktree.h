#pragma once

#include <iostream>
using namespace std;

enum color { RED, BLACK };
template<typename T>
class RBT
{
private:
    struct node
    {
        T key;
        bool color;
        node* left;
        node* right;
        node* p;
        node(const T& k, const bool& c = RED, node* l = nullptr, node* r = nullptr, node* _p = nullptr) :key(k), color(c), left(l), right(r), p(_p) {}
    };
    node* root;
    node* nil; //color:black


    void removeSubtree(node* Ptr) //удалит все, начиная с Ptr
    {
        if (Ptr != nullptr)
        {
            if (Ptr != nil)
            {
                if (Ptr->left != nil)
                {
                    removeSubtree(Ptr->left); //рекурсивно проходим по всем левым
                }
                if (Ptr->right != nil)
                {
                    removeSubtree(Ptr->right); //и правым
                }
                //    cout << "Удаляем узел, содержащий ключ: " << Ptr->key << endl;
                delete Ptr; //корень тоже уберется
            }
        }
    }



    void left_rotate(node* x)
    {
        node* y = x->right;
        x->right = y->left;

        if (y->left != nil && y->left != nullptr)
            y->left->p = x;
        y->p = x->p;
        if (x->p == nil)
            root = y;
        else if (x == x->p->left)
            x->p->left = y;
        else x->p->right = y;
        y->left = x;
        x->p = y;
    }
    void right_rotate(node* x)
    {
        node* y = x->left;
        x->left = y->right;
        if (y->right != nil && y->right != nullptr)
            y->right->p = x;
        y->p = x->p;
        if (x->p == nil)
            root = y;
        else if (x->p->left == x)
            x->p->left = y;
        else
            x->p->right = y;
        x->p = y;
        y->right = x;
    }
    node* insert_tree(node*& p, node*& r, const T& k) //нужна для функции insert
        //insert отправляет (nil,root,key)
    {
        if (r == nil) //если дерево пустое (в первый раз)
        {//или если следующий указатель пустой (когда дерево не пустое и идет рекурсия)
            r = new node(k, RED, nil, nil, p);
            if (p == nil)
                root = r;
            if (k > p->key) //элемент направится налево или направо
                p->right = r;
            else
                p->left = r;
        }
        else
        {
            if (k < r->key) //если ключ меньше корня или след. элемента
                return insert_tree(r, r->left, k); //проходит влево и снова все проверяет
            else if (k > r->key) //если ключ больше корня или след. элемента
                return insert_tree(r, r->right, k); //проходит вправо и снова все проверят
            else
                cout << "Ключ " << k << " невозможно добавить. Такой ключ уже есть в дереве.\n";
        } //эта рекурсия работает так, что каждый раз смещается вниз - влево или вправо, пока не найдет нужное место
        return r;
    }




    void rb_delete_fixup(node* x) 
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->p->left)
            {
                node* w = x->p->right; 
                if (w->color == RED)                                     //А: случай 1
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    left_rotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) //A: случай 2
                {
                    w->color = RED;
                    x = x->p;
                }
                else
                {
                    if (w->right->color == BLACK)                       //А: начало случая 3
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;                             //А: начало случая 4
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->p);
                    x = root;                                           //А: конец случая 3, конец случая 4
                }
            }
            else //замена правого на левый и наоборот
            {
                node* w = x->p->left;
                if (w->color == RED)                                    //B: случай 1
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    right_rotate(x->p);
                    w = x->p->left;
                }
                if (w->right->color == BLACK && w->left->color == RED)  //B: случай 2
                {
                    w->color = RED;
                    x = x->p;
                }
                else
                {
                    if (w->left->color == BLACK)                        //B: случай 3
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;                             //B: случай 4
                    x->p->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->p);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    void rb_transplant(node*& u, node*& v)
    { //u - узел, который мы заменяем узлом v
        if (u->p == nil)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else u->p->right = v;
        v->p = u->p;
    }

    //поиск узла по ключу
    node* tree_search(node* x, T k) //node*x можно поменять на root чтобы искало сначала
    {
        while (x != nil && k != x->key)
        {
            if (k < x->key)
                x = x->left;
            else x = x->right;
        }
        if (x->key == k)return x;
        else return nullptr;
    }


    void rb_delete(node* z)
    {
        node* y = z; //y должен будет заменить z в третьем случае
        node* x = z; //x определяет, что передастся в fixup
        bool y_original_color = y->color;
        if (z->left == nil) //нет потомков слева или вообще нет потомков
        {
            x = z->right;
            rb_transplant(z, z->right); //ставим правый узел на место узла z
            delete y;
        }
        else if (z->right == nil) //нет потомков справа
        {
            x = z->left;
            rb_transplant(z, z->left); //ставим левый узел на место узла z
            delete y;
        }
        else
        {
            y = tree_minimum(z->right); //находит самый маленький элемент правого поддерева
            y_original_color = y->color;
            x = y->right;
            if (y->p == z) //если z - родитель самого маленького элемента в правой части
                x->p = y; //то y станет для x родителем
            else //z - не родитель самого маленького элемента в правой части
            {
                rb_transplant(y, y->right); //1.на место y ставим y->right, y остается висеть
                y->right = z->right; //2.приравниваем y->right правому потомку z
                y->right->p = y; //3. ставим y на место z (или узла, который там был)
            }
            rb_transplant(z, y); //ставим в корень поддерева y
            y->left = z->left; //забираем у z левое поддерево и цвет
            y->left->p = y;
            y->color = z->color;
        }
        if (y_original_color == BLACK)
            rb_delete_fixup(x); //так как могла быть нарушена черная высота
        else delete x;
    } //delete x и delete y я добавил в последний момент. Надо будет все проверить

    node* tree_minimum(node* x) //поиск минимального элемента в дереве, начиная с узла x
    {
        node* p = x;
        while (x != nil)
        {
            p = x;
            x = x->left;
        }
        return p;
    }

    //рекурсивный вывод элементов (слева направо)
    void in_order(node* x)
    {
        if (x == nil || x == nullptr)
            return;
        in_order(x->left); //сначала обходит слева
        cout << x->key; //потом выводит корень
        if (x->color == RED) cout << " RED\n";
        else cout << " BLACK\n";
        in_order(x->right); //потом обходит направо
    }


    //геттеры
    node* getNode(node* r, const T& v)
    {
        if (r == nil)
            return nil;
        if (r->key == v)
            return r;
        else if (v < r->key)
            return getNode(r->left, v);
        else
            return getNode(r->right, v);
    }
    node* getNode(const T& v)
    {
        return getNode(root, v);
    }

public:

    RBT()
    {
        //nil указывает только сам на себя, а на него указывают конечные элементы дерева и корень. nil - черный
        nil = new node(NULL, BLACK, nil, nil, nil); //первый аргумент не имеет значения.
        root = nil;
    }

    RBT(RBT &source) //конструктор копирования (заглушка)
    {
        nil = new node(NULL, BLACK, nil, nil, nil);
        root = new node(source.root->key, BLACK, nil, nil, nil);
        cout << "Копируется только корень, копирование дерева не предусмотрено!\n";
    }

    ~RBT()
    {
        removeSubtree(root);
        delete nil;
    }
    bool tree_search(T k)
    {
        //cout << "Если такой ключ есть, то выдаст 1: ";
        node* result = tree_search(root, k);
        if (result == nullptr) return 0;
        else return 1;
        delete result;
    }

    void insert(const T& k) 
    {
        node* z = insert_tree(nil, root, k);
        while (z->p->color == RED)
        {
            if (z->p->p->left == z->p) //родитель находится слева от "деда"?
            {
                if (z->p->p->right->color == RED)                //A: случай 1
                {
                    z->p->color = BLACK; //1.Красим родителя в черный
                    z->p->p->color = RED; //2.Красим "деда" в красный
                    z->p->p->right->color = BLACK; //3.Красим правого "дядю" в черный
                    z = z->p->p; //4.Присваиваем указатель "деду" и начинаем следующую итерацию
                }
                else
                {
                    if (z->p->right == z)                       //A: начало случая 2
                    {
                        z = z->p;
                        left_rotate(z); //левый поворот преобразует случай 2 в случай 3
                    }                                           //A: начало случая 3
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    right_rotate(z->p->p);                      //конец случаев 2 и 3
                }
            }
            else  //B - то же, что A, но с заменой правого левым и наоборот
            { //родитель находится справа от "деда"?
                if (z->p->p->left->color == RED)                 //B: случай 1
                {
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    z->p->p->left->color = BLACK;
                    z = z->p->p;
                }
                else
                {
                    if (z->p->left == z)                         //B: случай 2
                    {
                        z = z->p;
                        right_rotate(z);
                    }
                    z->p->color = BLACK;                        //B: случай 3
                    z->p->p->color = RED;
                    left_rotate(z->p->p);

                }
            }
        }
        root->color = BLACK; //корень делаем черным
    }

    void _delete(const T& v)
    {
        node* z = getNode(root, v);
        if (z == nil)
            return;
        rb_delete(z); //обращается к приватному методу
    }

    void in_order()
    {
        cout << "Вывод ключей дерева в порядке возрастания: " << endl;
        in_order(root); //обращается к приватному методу
    }
};
