#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED
#include <iostream>
//#include"manager.h"

using namespace std;

enum Color {black = 0, red};

/*�������࣬�Ա�����node����������Ԫ
 * T Ϊ�洢���࣬KΪ�Ƚ�ʱ�ļ�ֵ
 */
template<class K, class T> class redblacktree;
//�ڵ�
template<class K, class T>
class node
{
    friend class redblacktree<K,T>;//ģ�����Ԫ����
private:
    K key;
    T data;
    Color color;
    node<K,T>* rightchild;
    node<K,T>* leftchild;
    node<K,T>* parent;
    node()
    {
        color = red;
        rightchild = leftchild = parent = NULL;
    }
    node(const T& data, const K& key)
    {
        this->data = data;
        this->key = key;
        color = red;
        rightchild = leftchild = parent = NULL;
    }
    node(const Color& color)
    {
        this->color = color;
        rightchild = leftchild = parent = NULL;
    }
    node(const T& data, const K& key, const Color& color)
    {
        this->data = data;
        this->key = key;
        this->color = color;
        rightchild = leftchild = parent = NULL;
    }

    void visit()
    {
        cout << key;    //������
    }
    node<K,T>& operator = (const node<K,T>& Node)//���ظ�ֵ����
    {
        this->color = Node.color;
        this->rightchild = Node.rightchild;
        this->leftchild = Node.leftchild;
        this->parent = Node.parent;
        this->key = Node.key;
        this->data = Node.data;
    }
};



template<class K, class T>
class redblacktree
{
    friend class manager;
public:
    redblacktree()
    {
        nill = new node<K,T>(black) ;
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
    void pre_tree_walk();//ǰ�����
    void mid_tree_walk();//���������������
    node<K,T>* tree_max(node<K,T>* rt);//���������С
    node<K,T>* tree_min(node<K,T>* rt);
    bool search(const K& srkey, T*& data) const;
    bool search(const K& srkey) const;
    void RB_insert(const T& data,const K& insrtkey);//�����㷨
    bool RB_DELETE(const K& dkey);//ɾ���㷨
    void RB_DELETE(node<K,T>* x);//ɾ��ĳ���ڵ�
    bool empty() const;
    int getsize() const;
private:
    node<K,T>* root;
    node<K,T>* nill;//����NULL
    int size;
    void pre_tree_walk(node<K,T>* root);
    void mid_tree_walk(node<K,T>* root);
    void tree_destroy(node<K,T>* current);
    node<K,T>* tree_successor(node<K,T>* x);//��ڵ�ĺ��
    node<K,T>* rbsearch(const K& srkey) const;//����
    void left_rotate(node<K,T>* x);//����
    void right_rotate(node<K,T>* x);//����
    void RB_insert_fixup(node<K,T>* x);//�������
    void RB_DELETE_fixup(node<K,T>* x);//ɾ������
};

//����ɾ��
template<class K, class T>
void redblacktree<K,T>::tree_destroy(node<K,T>* current)
{
    if(current != nill)
    {
        tree_destroy(current->leftchild);
        tree_destroy(current->rightchild);
        delete current;
    }
}

template<class K, class T>
bool redblacktree<K,T>::empty() const
{
    return size == 0;
}

template<class K, class T>
int redblacktree<K,T>::getsize() const
{
    return size;
}

//����
template<class K, class T>
bool redblacktree<K,T>::search(const K& srkey) const
{
    node<K,T>* x = rbsearch(srkey);
    if(x == nill)
        return false;
    else
        return true;
}

//����2
template<class K, class T>
bool redblacktree<K,T>::search(const K& srkey,  T*& datapoint) const
{
    node<K,T>* x = rbsearch(srkey);
    if(x == nill)
    {
        datapoint = NULL;
        return false;
    }
    else
    {
        datapoint = &x->data;
        return true;
    }
}

template<class K, class T>
node<K,T>* redblacktree<K,T>::rbsearch(const K& srkey) const
{
    node<K,T>* x = root;
    while(x != nill && srkey != x->key)
    {
        if(srkey > x->key)
            x = x ->rightchild;
        else
            x= x ->leftchild;
    }
    return x;
}

//ǰ�����
template<class K, class T>
void redblacktree<K,T>::pre_tree_walk(node<K,T>* root)
{
    if(root != nill)
    {
        pre_tree_walk(root->leftchild);
        root->visit();
        pre_tree_walk(root->rightchild);
    }
}
template<class K, class T>
void redblacktree<K,T>::pre_tree_walk()
{
    pre_tree_walk(root);
    cout << endl;
}
//�������
template<class K, class T>
void redblacktree<K,T>::mid_tree_walk(node<K,T>* root)
{
    if(root != nill)
    {
        root->visit();
        mid_tree_walk(root->leftchild);
        mid_tree_walk(root->rightchild);
    }
}
template<class K, class T>
void redblacktree<K,T>::mid_tree_walk()
{
    mid_tree_walk(root);
    cout << endl;
}


//�����С
template<class K, class T>
node<K,T>*  redblacktree<K,T>::tree_max(node<K,T>* rt)
{
    node<K,T>* current = rt;
    while(current->rightchild != nill)
        current = current->rightchild;
    return current;
}
template<class K, class T>
node<K,T>* redblacktree<K,T>::tree_min(node<K,T>* rt)
{
    node<K,T>* current = rt;
    while(current->leftchild != nill)
        current = current->leftchild;
    return current;
}

//���̽��
template<class K, class T>
node<K,T>* redblacktree<K,T>::tree_successor(node<K,T>* x)
{
    if(x->rightchild != nill)//x���Һ���ʱ����̾����Һ��ӵ���С�ڵ�
        return tree_min(x->rightchild);
    node<K,T>* y = x->parent;//��������
    while(y!= nill && x == y->rightchild)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

//����
template<class K, class T>
void redblacktree<K,T>::left_rotate(node<K,T>* x)
{
    node<K,T>* y = x->rightchild;
    x->rightchild = y->leftchild;
    y->leftchild->parent = x;
    y->parent = x->parent;
    y->leftchild = x;
    if(x->parent == nill)
        root = y;
    else if(x == x->parent->leftchild)
        x->parent->leftchild = y;
    else
        x->parent->rightchild = y;
    x->parent = y;
    nill->parent = nill;
}

//����
template<class K, class T>
void redblacktree<K,T>::right_rotate(node<K,T>* x)
{
    node<K,T>* y = x->leftchild;
    x->leftchild = y->rightchild;
    y->rightchild->parent = x;
    y->parent = x->parent;
    y->rightchild = x;
    if(x->parent == nill)
        root = y;
    else if(x == x->parent->leftchild)
        x->parent->leftchild = y;
    else
        x->parent->rightchild = y;
    x->parent = y;
    nill->parent = nill;
}

template<class K, class T>
void redblacktree<K,T>::RB_insert(const T& data, const K& insrtkey)//�����㷨
{
    /*������
    cout << key << "hel" << endl;
    */
    node<K,T>* x = new node<K,T>(data, insrtkey, red);
    x->parent = x->rightchild = x->leftchild = nill;
    node<K,T>* current = root;
    node<K,T>* y = nill;
    while(current != nill)
    {
//        cout << "aaa" << endl;
        y = current;
        if(insrtkey > current->key)
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
        if(x->key > y->key)
            y->rightchild = x;
        else
            y->leftchild = x;
    }
    RB_insert_fixup(x);//���������ʹ֮������������
    ++ size;//�ڵ��һ
}
//�������
template<class K, class T>
void redblacktree<K,T>::RB_insert_fixup(node<K,T>* x)
{
    while(x != root && x->parent->color == red)
    {
        if(x->parent == x->parent->parent->leftchild)//��������֧�����
        {
            node<K,T>* ly = x->parent->parent->rightchild;
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
            node<K,T>* ry = x->parent->parent->leftchild;
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
template <class K, class T>
bool redblacktree<K,T>::RB_DELETE(const K& dkey)
{
    node<K,T>* x = rbsearch(dkey);//�Ҹýڵ�
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
template <class K, class T>
void redblacktree<K,T>::RB_DELETE(node<K,T>* x)
{
    node<K,T>* z = NULL;
    if(x->rightchild == nill || x->leftchild == nill)
        z = x;
    else
        z = tree_successor(x);//���x�ڵ����������ӣ�����zΪ����
    node<K,T>* y = NULL;
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
    {
        x->key = z->key;
        x->data = z->data;
    }
    if(z->color ==  black)//��ɾ���Ľڵ�ʱ��ɫʱ������Ҫ�������е���
        RB_DELETE_fixup(y);
    delete z;
    nill->parent = nill;//����yΪnillʱ����nill�ĸ��׵���
}

//ɾ������
template<class K, class T>
void redblacktree<K,T>::RB_DELETE_fixup(node<K,T>* x)
{
    while(x != root && x->color == black)
    {
        node<K,T>* w = NULL;
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
                x = w->parent;//x����
            }
            //��w��������Ǻ�ɫ���Ҷ����Ǻ�ɫʱ,���Ҷ���ת��Ϊ��ɫ
            else if(w->rightchild->color == black && w->leftchild->color == red)
            {
                w->leftchild->color = black;
                w->color = red;
                right_rotate(w);
                w = w->parent;
            }
            //w���Ҷ����Ǻ�ɫ
            if(w->rightchild->color == red)
            {
                w->color = w->parent->color;
                w->parent->color = black;
                w->rightchild->color = black;
                left_rotate(w->parent);
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
                x = w->parent;//x����
            }
            //��w���Ҷ����Ǻ�ɫ��������Ǻ�ɫʱ,�������ת��Ϊ��ɫ
            else if(w->leftchild->color == black && w->rightchild->color == red)
            {
                w->rightchild->color = black;
                w->color = red;
                left_rotate(w);
                w = w->parent;
            }
            //w��������Ǻ�ɫ
            if(w->leftchild->color == red)
            {
                w->color = w->parent->color;
                w->parent->color = black;
                w->leftchild->color = black;
                right_rotate(w->parent);
                x = root;
            }
        }//else
    }//while
    x->color = black;
    nill->color = black;//һ��ʼxΪnillʱ�����ڵ�һ������ǰ��nill��ɫ����Ϊ��ɫ
}

#endif // REDBLACKTREE_H_INCLUDED
