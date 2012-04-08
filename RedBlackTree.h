#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED
#include <iostream>

using namespace std;

enum Color {black = 0, red};
//�ڵ�
template<typename T>
class node
{
public:
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
    node(T value)
    {
        this->value = value;
        color = red;
        rightchild = leftchild = parent = NULL;
    }
    node(Color color)
    {
        this->color = color;
        rightchild = leftchild = parent = NULL;
    }
    node(T value, Color color)
    {
        this->value = value;
        this->color = color;
        rightchild = leftchild = parent = NULL;
    }

    void visit() {cout << value;}//������
};



template<typename T>
class redblacktree
{
public:
    redblacktree()
    {
	nill = new node<T>(black) ;
	nill->parent = nill;
	nill->leftchild = nill;
       	nill->rightchild = nill;//nill�ĸ���ָ�붼ָ���Լ�
        root = nill;
    }
    ~redblacktree(){tree_destroy(root);}
    node<T>* rbsearch(T key);//����
    void pre_tree_walk();//ǰ�����
    node<T>* tree_max();//���������С
    node<T>* tree_min();
    void RB_insert(T value);//�����㷨
    bool RB_DELETE(T value);//ɾ���㷨
    void RB_DELETE(node<T>* x);//ɾ��ĳ���ڵ�
private:
    node<T>* root;
    node<T>* nill;//����NULL
    void pre_tree_walk(node<T>* root);
    void tree_destroy(node<T>* current);
    node<T>* tree_successor(node<T>* x);//��ڵ�ĺ��
    void left_rotate(node<T>* key);//����
    void right_rotate(node<T>* key);//����
    void RB_insert_fixup(node<T>* x);//�������
    void RB_DELETE_fixup(node<T>* x);//ɾ������
};

//����ɾ��
template<typename T>
void redblacktree<T>::tree_destroy(node<T>* current)
{
    if(current != nill)
    {
        tree_destroy(current->leftchild);
        tree_destroy(current->rightchild);
    	delete current;
    }
}

//����
template<typename T>
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
template<typename T>
void redblacktree<T>::pre_tree_walk(node<T>* root)
{
    if(root != nill)
    {
        pre_tree_walk(root->leftchild);
        root->visit();
        pre_tree_walk(root->rightchild);
    }
}
template<typename T>
void redblacktree<T>::pre_tree_walk()
{
    pre_tree_walk(root);
}

//�����С
template<typename T>
node<T>*  redblacktree<T>::tree_max()
{
    node<T>* current = root;
    while(current != nill)
        current = current->rightchild;
    return current;
}
template<typename T>
node<T>* redblacktree<T>::tree_min()
{
    node<T>* current = root;
    while(current != nill)
        current = current->leftchild;
    return current;
}

//���̽��
template<typename T>
node<T>* redblacktree<T>::tree_successor(node<T>* x)
{
    if(x->rightchild == nill)//x���Һ���ʱ����̾����Һ��ӵ���С�ڵ�
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
template<typename T>
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
template<typename T>
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

template<typename T>
void redblacktree<T>::RB_insert(T value)//�����㷨
{
    /*������*/
    cout << value;
    /**/
    node<T>* x = new node<T>(value, red);
    x->parent = x->rightchild = x->leftchild = nill;
    node<T>* current = root;
    node<T>* y = NULL;
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
}
//�������
template<typename T>
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
template <typename T>
bool redblacktree<T>::RB_DELETE(T value)
{
    node<T>* x = rbsearch(value);//�Ҹýڵ�
    if(x == nill)//δ�ҵ�
        {cout << "can't find the key to be deleted" << endl;return false;}
    else
        RB_DELETE(x);//�ҵ������ɾ������
    return true;
}

//ɾ��ĳ���ڵ�
template <typename T>
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
        y = z->parent->leftchild;
    else
        y = z->parent->rightchild;
    if(x != z)
            x->value = z->value;
    if(z->color ==  black)//��ɾ���Ľڵ�ʱ��ɫʱ������Ҫ�������е���
        RB_DELETE_fixup(y);
    delete z;
}

//ɾ������
template<typename T>
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
    nill.color = black;//һ��ʼxΪnillʱ�����ڵ�һ������ǰ��nill��ɫ����Ϊ��ɫ
}

#endif // REDBLACKTREE_H_INCLUDED
