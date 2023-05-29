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


    void removeSubtree(node* Ptr) //������ ���, ������� � Ptr
    {
        if (Ptr != nullptr)
        {
            if (Ptr != nil)
            {
                if (Ptr->left != nil)
                {
                    removeSubtree(Ptr->left); //���������� �������� �� ���� �����
                }
                if (Ptr->right != nil)
                {
                    removeSubtree(Ptr->right); //� ������
                }
                //    cout << "������� ����, ���������� ����: " << Ptr->key << endl;
                delete Ptr; //������ ���� ��������
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
    node* insert_tree(node*& p, node*& r, const T& k) //����� ��� ������� insert
        //insert ���������� (nil,root,key)
    {
        if (r == nil) //���� ������ ������ (� ������ ���)
        {//��� ���� ��������� ��������� ������ (����� ������ �� ������ � ���� ��������)
            r = new node(k, RED, nil, nil, p);
            if (p == nil)
                root = r;
            if (k > p->key) //������� ���������� ������ ��� �������
                p->right = r;
            else
                p->left = r;
        }
        else
        {
            if (k < r->key) //���� ���� ������ ����� ��� ����. ��������
                return insert_tree(r, r->left, k); //�������� ����� � ����� ��� ���������
            else if (k > r->key) //���� ���� ������ ����� ��� ����. ��������
                return insert_tree(r, r->right, k); //�������� ������ � ����� ��� ��������
            else
                cout << "���� " << k << " ���������� ��������. ����� ���� ��� ���� � ������.\n";
        } //��� �������� �������� ���, ��� ������ ��� ��������� ���� - ����� ��� ������, ���� �� ������ ������ �����
        return r;
    }




    void rb_delete_fixup(node* x) 
    {
        while (x != root && x->color == BLACK)
        {
            if (x == x->p->left)
            {
                node* w = x->p->right; 
                if (w->color == RED)                                     //�: ������ 1
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    left_rotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) //A: ������ 2
                {
                    w->color = RED;
                    x = x->p;
                }
                else
                {
                    if (w->right->color == BLACK)                       //�: ������ ������ 3
                    {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;                             //�: ������ ������ 4
                    x->p->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->p);
                    x = root;                                           //�: ����� ������ 3, ����� ������ 4
                }
            }
            else //������ ������� �� ����� � ��������
            {
                node* w = x->p->left;
                if (w->color == RED)                                    //B: ������ 1
                {
                    w->color = BLACK;
                    x->p->color = RED;
                    right_rotate(x->p);
                    w = x->p->left;
                }
                if (w->right->color == BLACK && w->left->color == RED)  //B: ������ 2
                {
                    w->color = RED;
                    x = x->p;
                }
                else
                {
                    if (w->left->color == BLACK)                        //B: ������ 3
                    {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;                             //B: ������ 4
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
    { //u - ����, ������� �� �������� ����� v
        if (u->p == nil)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else u->p->right = v;
        v->p = u->p;
    }

    //����� ���� �� �����
    node* tree_search(node* x, T k) //node*x ����� �������� �� root ����� ������ �������
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
        node* y = z; //y ������ ����� �������� z � ������� ������
        node* x = z; //x ����������, ��� ���������� � fixup
        bool y_original_color = y->color;
        if (z->left == nil) //��� �������� ����� ��� ������ ��� ��������
        {
            x = z->right;
            rb_transplant(z, z->right); //������ ������ ���� �� ����� ���� z
            delete y;
        }
        else if (z->right == nil) //��� �������� ������
        {
            x = z->left;
            rb_transplant(z, z->left); //������ ����� ���� �� ����� ���� z
            delete y;
        }
        else
        {
            y = tree_minimum(z->right); //������� ����� ��������� ������� ������� ���������
            y_original_color = y->color;
            x = y->right;
            if (y->p == z) //���� z - �������� ������ ���������� �������� � ������ �����
                x->p = y; //�� y ������ ��� x ���������
            else //z - �� �������� ������ ���������� �������� � ������ �����
            {
                rb_transplant(y, y->right); //1.�� ����� y ������ y->right, y �������� ������
                y->right = z->right; //2.������������ y->right ������� ������� z
                y->right->p = y; //3. ������ y �� ����� z (��� ����, ������� ��� ���)
            }
            rb_transplant(z, y); //������ � ������ ��������� y
            y->left = z->left; //�������� � z ����� ��������� � ����
            y->left->p = y;
            y->color = z->color;
        }
        if (y_original_color == BLACK)
            rb_delete_fixup(x); //��� ��� ����� ���� �������� ������ ������
        else delete x;
    } //delete x � delete y � ������� � ��������� ������. ���� ����� ��� ���������

    node* tree_minimum(node* x) //����� ������������ �������� � ������, ������� � ���� x
    {
        node* p = x;
        while (x != nil)
        {
            p = x;
            x = x->left;
        }
        return p;
    }

    //����������� ����� ��������� (����� �������)
    void in_order(node* x)
    {
        if (x == nil || x == nullptr)
            return;
        in_order(x->left); //������� ������� �����
        cout << x->key; //����� ������� ������
        if (x->color == RED) cout << " RED\n";
        else cout << " BLACK\n";
        in_order(x->right); //����� ������� �������
    }


    //�������
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
        //nil ��������� ������ ��� �� ����, � �� ���� ��������� �������� �������� ������ � ������. nil - ������
        nil = new node(NULL, BLACK, nil, nil, nil); //������ �������� �� ����� ��������.
        root = nil;
    }

    RBT(RBT &source) //����������� ����������� (��������)
    {
        nil = new node(NULL, BLACK, nil, nil, nil);
        root = new node(source.root->key, BLACK, nil, nil, nil);
        cout << "���������� ������ ������, ����������� ������ �� �������������!\n";
    }

    ~RBT()
    {
        removeSubtree(root);
        delete nil;
    }
    bool tree_search(T k)
    {
        //cout << "���� ����� ���� ����, �� ������ 1: ";
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
            if (z->p->p->left == z->p) //�������� ��������� ����� �� "����"?
            {
                if (z->p->p->right->color == RED)                //A: ������ 1
                {
                    z->p->color = BLACK; //1.������ �������� � ������
                    z->p->p->color = RED; //2.������ "����" � �������
                    z->p->p->right->color = BLACK; //3.������ ������� "����" � ������
                    z = z->p->p; //4.����������� ��������� "����" � �������� ��������� ��������
                }
                else
                {
                    if (z->p->right == z)                       //A: ������ ������ 2
                    {
                        z = z->p;
                        left_rotate(z); //����� ������� ����������� ������ 2 � ������ 3
                    }                                           //A: ������ ������ 3
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    right_rotate(z->p->p);                      //����� ������� 2 � 3
                }
            }
            else  //B - �� ��, ��� A, �� � ������� ������� ����� � ��������
            { //�������� ��������� ������ �� "����"?
                if (z->p->p->left->color == RED)                 //B: ������ 1
                {
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    z->p->p->left->color = BLACK;
                    z = z->p->p;
                }
                else
                {
                    if (z->p->left == z)                         //B: ������ 2
                    {
                        z = z->p;
                        right_rotate(z);
                    }
                    z->p->color = BLACK;                        //B: ������ 3
                    z->p->p->color = RED;
                    left_rotate(z->p->p);

                }
            }
        }
        root->color = BLACK; //������ ������ ������
    }

    void _delete(const T& v)
    {
        node* z = getNode(root, v);
        if (z == nil)
            return;
        rb_delete(z); //���������� � ���������� ������
    }

    void in_order()
    {
        cout << "����� ������ ������ � ������� �����������: " << endl;
        in_order(root); //���������� � ���������� ������
    }
};