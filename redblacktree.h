#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED
#include <iostream>
#include"manager.h"

using namespace std;

enum Color {black = 0, red};
template<class T> class redblacktree;//�������࣬�Ա�����node����������Ԫ
//�ڵ�
template<class T>
class node
{
    friend class redblacktree<T>;//ģ�����Ԫ����
private:
    T value;
    Color color;
    node<T>* rightchild;
    node<T>* leftchild;
    node<T>* parent;
    node()
    {
        color = red;
        rightchild = leftchild = parent = NULL;
    }
    node(const T& value)
    {
        this->value = value;
        color = red;
        rightchild = leftchild = parent = NULL;
    }
    node(const Color& color)
    {
        this->color = color;
        rightchild = leftchild = parent = NULL;
    }
    node(const T& value,const Color& color)
    {
        this->value = value;
        this->color = color;
        rightchild = leftchild = parent = NULL;
    }

    void visit()
    {
        cout << value;    //������
    }
    node<T>& operator = (const node<T>& Node)//���ظ�ֵ����
    {
        this->color = Node.color;
        this->rightchild = Node.rightchild;
        this->leftchild = Node.leftchild;
        this->parent = Node.parent;
        this->value = Node.value;
    }
};



template<class T>
class redblacktree
{
	friend class manager;
public:
    redblacktree()
    {
        nill = new node<T>(black) ;
        nill->parent = nill;
        nill->leftchild = nill;
        nill->rightchild = nill;//nill�ĸ���ָ�붼ָ���Լ�
        root = nill;
        size = 0;
    }
    ~redblacktree()
    {
        tree_destroy(root);
    }
    node<T>* rbsearch(T key);//����
    void pre_tree_walk();//ǰ�����
    void mid_tree_walk();//���������������
    node<T>* tree_max(node<T>* rt);//���������С
    node<T>* tree_min(node<T>* rt);
    bool search(const T& value) const;
    void RB_insert(T value);//�����㷨
    bool RB_DELETE(T value);//ɾ���㷨
    void RB_DELETE(node<T>* x);//ɾ��ĳ���ڵ�
    bool empty() const;
    int getsize();
private:
    node<T>* root;
    node<T>* nill;//����NULL
    int size;
    void pre_tree_walk(node<T>* root);
    void mid_tree_walk(node<T>* root);
    void tree_destroy(node<T>* current);
    node<T>* tree_successor(node<T>* x);//��ڵ�ĺ��
    void left_rotate(node<T>* key);//����
    void right_rotate(node<T>* key);//����
    void RB_insert_fixup(node<T>* x);//�������
    void RB_DELETE_fixup(node<T>* x);//ɾ������
};

//����ɾ��
template<class T>
void redblacktree<T>::tree_destroy(node<T>* current)
{
    if(current != nill)
    {
        tree_destroy(current->leftchild);
        tree_destroy(current->rightchild);
        delete current;
    }
}

template<class T>
bool redblacktree<T>::empty() const
{
    return size == 0;
}

template<class T>
int redblacktree<T>::getsize()
{
    return size;
}

//����
template<class T>
bool redblacktree<T>::search(const T& key) const
{
	node<T>* x = rbsearch(key);
	if(x == nill)
		return false;
	else
		return true;
}

template<class T>
node<T>* redblacktree<T>::rbsearch(T key)
{
    node<T>* x = root;
    while(x!= nill && key != x->value)
    {
        if(key > x->value)
            x = x ->rightchild;
        else
            x= x ->leftchild;
    }
    return x;
}

//ǰ�����
template<class T>
void redblacktree<T>::pre_tree_walk(node<T>* root)
{
    if(root != nill)
    {
        pre_tree_walk(root->leftchild);
        root->visit();
        pre_tree_walk(root->rightchild);
    }
}
template<class T>
void redblacktree<T>::pre_tree_walk()
{
    pre_tree_walk(root);
    cout << endl;
}
//�������
template<class T>
void redblacktree<T>::mid_tree_walk(node<T>* root)
{
    if(root != nill)
    {
        root->visit();
        mid_tree_walk(root->leftchild);
        mid_tree_walk(root->rightchild);
    }
}
template<class T>
void redblacktree<T>::mid_tree_walk()
{
    mid_tree_walk(root);
    cout << endl;
}


//�����С
template<class T>
node<T>*  redblacktree<T>::tree_max(node<T>* rt)
{
    node<T>* current = rt;
    while(current->rightchild != nill)
        current = current->rightchild;
    return current;
}
template<class T>
node<T>* redblacktree<T>::tree_min(node<T>* rt)
{
    node<T>* current = rt;
    while(current->leftchild != nill)
        current = current->leftchild;
    return current;
}

//���̽��
template<class T>
node<T>* redblacktree<T>::tree_successor(node<T>* x)
{
    if(x->rightchild != nill)//x���Һ���ʱ����̾����Һ��ӵ���С�ڵ�
        return tree_min(x->rightchild);
    node<T>* y = x->parent;//��������
    while(y!= nill && x == y->rightchild)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

//����
template<class T>
void redblacktree<T>::left_rotate(node<T>* key)
{
    node<T>* y = key->rightchild;
    key->rightchild = y->leftchild;
    y->leftchild->parent = key;
    y->parent = key->parent;
    y->leftchild = key;
    if(key->parent == nill)
        root = y;
    else if(key == key->parent->leftchild)
        key->parent->leftchild = y;
    else
        key->parent->rightchild = y;
    key->parent = y;
}

//����
template<class T>
void redblacktree<T>::right_rotate(node<T>* key)
{
    node<T>* y = key->leftchild;
    key->leftchild = y->rightchild;
    y->rightchild->parent = key;
    y->parent = key->parent;
    y->rightchild = key;
    if(key->parent == nill)
        root = y;
    else if(key == key->parent->leftchild)
        key->parent->leftchild = y;
    else
        key->parent->rightchild = y;
    key->parent = y;
}

template<class T>
void redblacktree<T>::RB_insert(T value)//�����㷨
{
    /*������
    cout << value << "hel" << endl;
    */
    node<T>* x = new node<T>(value, red);
    x->parent = x->rightchild = x->leftchild = nill;
    node<T>* current = root;
    node<T>* y = nill;
    while(current != nill)
    {
//        cout << "aaa" << endl;
        y = current;
        if(value > current->value)
            current = current->rightchild;
        else
            current = current ->leftchild;
    }
    x->parent = y;
    if(y == nill)//������ڵ������Ǹ�ʱ
    {
        root = x;
        x->color = black;
    }
    else
    {
        if(x->value > y->value)
            y->rightchild = x;
        else
            y->rightchild = x;
    }
    RB_insert_fixup(x);//���������ʹ֮������������
    ++ size;//�ڵ��һ
}
//�������
template<class T>
void redblacktree<T>::RB_insert_fixup(node<T>* x)
{
    /*������
    if(!x->parent)
        return;
    */
    while(x != root && x->parent->color == red)
    {
        if(x->parent == x->parent->parent->leftchild)//��������֧�����
        {
            node<T>* ly = x->parent->parent->rightchild;
            if(ly->color == red)//�����Ǻ�ɫ
            {
                x->parent->color = black;
                x->parent->parent->color = red;
                ly->color = black;
                x = x->parent->parent;//x����
            }
            else//�����Ǻ�ɫ
            {
                if(x == x->parent->rightchild)//�Ǹ��׵���֧������ת����֧���ٵ���
                {
                    x = x->parent;
                    left_rotate(x);
                }
                x->parent->color = black;
                x->parent->parent->color = red;
                right_rotate(x->parent->parent);
            }
        }
        else//��������֧
        {
            node<T>* ry = x->parent->parent->leftchild;
            if(ry->color == red)//�����Ǻ�ɫ
            {
                x->parent->color = black;
                x->parent->parent->color = red;
                ry->color = black;
                x = x->parent->parent;//x����
            }
            else//�����Ǻ�ɫ
            {
                if(x == x->parent->leftchild)//�Ǹ��׵���֧ʱ������ת���ٵ���
                {
                    x = x->parent;
                    right_rotate(x);
                }
                x->parent->color = black;
                x->parent->parent->color = red;
                left_rotate(x->parent->parent);
            }
        }
    }
    root->color = black;
}

//ɾ��ĳ��Ԫ��
template <class T>
bool redblacktree<T>::RB_DELETE(T value)
{
    node<T>* x = rbsearch(value);//�Ҹýڵ�
    if(x == nill)//δ�ҵ�
    {
        cout << "can't find the key to be deleted" << endl;
        return false;
    }
    else
    {
        RB_DELETE(x);//�ҵ������ɾ������
        size --;
    }
    return true;
}

//ɾ��ĳ���ڵ�
template <class T>
void redblacktree<T>::RB_DELETE(node<T>* x)
{
    node<T>* z = NULL;
    if(x->rightchild == nill || x->leftchild == nill)
        z = x;
    else
        z = tree_successor(x);//���x�ڵ����������ӣ�����zΪ����
    node<T>* y = NULL;
    if(z->leftchild != nill)
        y = z->leftchild;
    else
        y = z->rightchild;
    y->parent = z->parent;
    if(z->parent == nill)//��ɾ�����Ǹ�ʱ
        root = y;
    else if(z == z->parent->leftchild)
        z->parent->leftchild = y;
    else
        z->parent->rightchild = y;
    if(x != z)
        x->value = z->value;
    if(z->color ==  black)//��ɾ���Ľڵ�ʱ��ɫʱ������Ҫ�������е���
        RB_DELETE_fixup(y);
    delete z;
    nill->parent = nill;
}

//ɾ������
template<class T>
void redblacktree<T>::RB_DELETE_fixup(node<T>* x)
{
    while(x != root && x->color == black)
    {
        node<T>* w = NULL;
        if(x == x->parent->leftchild)//x������ʱ
        {
            w = x->parent->rightchild;
            if(w->color == red)//��x���ֵ��Ǻ�ɫ��ʱ��ͨ����ת�����ֵ�ת��Ϊ��ɫ
            {
                w->color = black;
                x->parent->color = red;
                left_rotate(x->parent);
            }
            //��x���ֵ��Ǻ�ɫʱ
            //��w���������Ӷ��Ǻ�ɫʱ
            if(w->leftchild->color == black && w->rightchild->color == black)
            {
                w->color = red;//w��ɫ��ȥ��ɫ
                x = x->parent;//x����
            }
            //��w��������Ǻ�ɫ���Ҷ����Ǻ�ɫʱ,���Ҷ���ת��Ϊ��ɫ
            else if(w->leftchild->color == red && w->rightchild->color == black)
            {
                w->leftchild->color = black;
                w->color = red;
                right_rotate(w);
                w = w->parent;
            }
            //w���Ҷ����Ǻ�ɫ
            else
            {
                w->color = x->parent->color;
                x->parent->color = black;
                w->rightchild->color = black;
                left_rotate(x->parent);
                x = root;
            }
        }//if(x == x->parent->leftchild)
        else//x���Һ���ʱ
        {
            w = x->parent->leftchild;
            if(w->color == red)//��x���ֵ��Ǻ�ɫ��ʱ��ͨ����ת�����ֵ�ת��Ϊ��ɫ
            {
                w->color = black;
                x->parent->color = red;
                right_rotate(x->parent);
            }
            //��x���ֵ��Ǻ�ɫʱ
            //��w���������Ӷ��Ǻ�ɫʱ
            if(w->leftchild->color == black && w->rightchild->color == black)
            {
                w->color = red;//w��ɫ��ȥ��ɫ
                x = x->parent;//x����
            }
            //��w���Ҷ����Ǻ�ɫ��������Ǻ�ɫʱ,�������ת��Ϊ��ɫ
            else if(w->leftchild->color == red && w->rightchild->color == black)
            {
                w->rightchild->color = black;
                w->color = red;
                left_rotate(w);
                w = w->parent;
            }
            //w��������Ǻ�ɫ
            else
            {
                w->color = x->parent->color;
                x->parent->color = black;
                w->leftchild->color = black;
                right_rotate(x->parent);
                x = root;
            }
        }//else
    }//while
    x->color = black;
    nill->color = black;//һ��ʼxΪnillʱ�����ڵ�һ������ǰ��nill��ɫ����Ϊ��ɫ
}

#endif // REDBLACKTREE_H_INCLUDED
