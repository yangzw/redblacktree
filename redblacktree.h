#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED
#include <iostream>
#include"manager.h"

using namespace std;

enum Color {black = 0, red};
template<class T> class redblacktree;//先声明类，以便于在node类中声明友元
//节点
template<class T>
class node
{
    friend class redblacktree<T>;//模板的友元声明
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
        cout << value;    //测试用
    }
    node<T>& operator = (const node<T>& Node)//重载赋值操作
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
        nill->rightchild = nill;//nill的各种指针都指向自己
        root = nill;
        size = 0;
    }
    ~redblacktree()
    {
        tree_destroy(root);
    }
    node<T>* rbsearch(T key);//查找
    void pre_tree_walk();//前序遍历
    void mid_tree_walk();//中序遍历，测试用
    node<T>* tree_max(node<T>* rt);//树的最大最小
    node<T>* tree_min(node<T>* rt);
    bool search(const T& value) const;
    void RB_insert(T value);//插入算法
    bool RB_DELETE(T value);//删除算法
    void RB_DELETE(node<T>* x);//删除某个节点
    bool empty() const;
    int getsize();
private:
    node<T>* root;
    node<T>* nill;//代替NULL
    int size;
    void pre_tree_walk(node<T>* root);
    void mid_tree_walk(node<T>* root);
    void tree_destroy(node<T>* current);
    node<T>* tree_successor(node<T>* x);//求节点的后继
    void left_rotate(node<T>* key);//左旋
    void right_rotate(node<T>* key);//右旋
    void RB_insert_fixup(node<T>* x);//插入调整
    void RB_DELETE_fixup(node<T>* x);//删除调整
};

//将树删除
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

//查找
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

//前序遍历
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
//中序遍历
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


//最大最小
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

//求后继结点
template<class T>
node<T>* redblacktree<T>::tree_successor(node<T>* x)
{
    if(x->rightchild != nill)//x有右孩子时，后继就是右孩子的最小节点
        return tree_min(x->rightchild);
    node<T>* y = x->parent;//向上求后继
    while(y!= nill && x == y->rightchild)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

//左旋
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

//右旋
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
void redblacktree<T>::RB_insert(T value)//插入算法
{
    /*测试用
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
    if(y == nill)//当插入节点正好是根时
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
    RB_insert_fixup(x);//插入调整，使之满足红黑树性质
    ++ size;//节点加一
}
//插入调整
template<class T>
void redblacktree<T>::RB_insert_fixup(node<T>* x)
{
    /*测试用
    if(!x->parent)
        return;
    */
    while(x != root && x->parent->color == red)
    {
        if(x->parent == x->parent->parent->leftchild)//父亲是左支的情况
        {
            node<T>* ly = x->parent->parent->rightchild;
            if(ly->color == red)//叔叔是红色
            {
                x->parent->color = black;
                x->parent->parent->color = red;
                ly->color = black;
                x = x->parent->parent;//x上推
            }
            else//叔叔是黑色
            {
                if(x == x->parent->rightchild)//是父亲的右支，先旋转成左支，再调整
                {
                    x = x->parent;
                    left_rotate(x);
                }
                x->parent->color = black;
                x->parent->parent->color = red;
                right_rotate(x->parent->parent);
            }
        }
        else//父亲是右支
        {
            node<T>* ry = x->parent->parent->leftchild;
            if(ry->color == red)//叔叔是红色
            {
                x->parent->color = black;
                x->parent->parent->color = red;
                ry->color = black;
                x = x->parent->parent;//x上推
            }
            else//叔叔是黑色
            {
                if(x == x->parent->leftchild)//是父亲的左支时，先旋转，再调整
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

//删除某个元素
template <class T>
bool redblacktree<T>::RB_DELETE(T value)
{
    node<T>* x = rbsearch(value);//找该节点
    if(x == nill)//未找到
    {
        cout << "can't find the key to be deleted" << endl;
        return false;
    }
    else
    {
        RB_DELETE(x);//找到后进行删除操作
        size --;
    }
    return true;
}

//删除某个节点
template <class T>
void redblacktree<T>::RB_DELETE(node<T>* x)
{
    node<T>* z = NULL;
    if(x->rightchild == nill || x->leftchild == nill)
        z = x;
    else
        z = tree_successor(x);//如果x节点有两个儿子，则设z为其后继
    node<T>* y = NULL;
    if(z->leftchild != nill)
        y = z->leftchild;
    else
        y = z->rightchild;
    y->parent = z->parent;
    if(z->parent == nill)//当删除的是根时
        root = y;
    else if(z == z->parent->leftchild)
        z->parent->leftchild = y;
    else
        z->parent->rightchild = y;
    if(x != z)
        x->value = z->value;
    if(z->color ==  black)//当删除的节点时黑色时，则需要对树进行调整
        RB_DELETE_fixup(y);
    delete z;
    nill->parent = nill;
}

//删除调整
template<class T>
void redblacktree<T>::RB_DELETE_fixup(node<T>* x)
{
    while(x != root && x->color == black)
    {
        node<T>* w = NULL;
        if(x == x->parent->leftchild)//x是左孩子时
        {
            w = x->parent->rightchild;
            if(w->color == red)//当x的兄弟是红色的时候，通过旋转将其兄弟转换为黑色
            {
                w->color = black;
                x->parent->color = red;
                left_rotate(x->parent);
            }
            //当x的兄弟是黑色时
            //当w的两个儿子都是黑色时
            if(w->leftchild->color == black && w->rightchild->color == black)
            {
                w->color = red;//w颜色减去黑色
                x = x->parent;//x上移
            }
            //当w的左儿子是红色，右儿子是黑色时,把右儿子转换为红色
            else if(w->leftchild->color == red && w->rightchild->color == black)
            {
                w->leftchild->color = black;
                w->color = red;
                right_rotate(w);
                w = w->parent;
            }
            //w的右儿子是红色
            else
            {
                w->color = x->parent->color;
                x->parent->color = black;
                w->rightchild->color = black;
                left_rotate(x->parent);
                x = root;
            }
        }//if(x == x->parent->leftchild)
        else//x是右孩子时
        {
            w = x->parent->leftchild;
            if(w->color == red)//当x的兄弟是红色的时候，通过旋转将其兄弟转换为黑色
            {
                w->color = black;
                x->parent->color = red;
                right_rotate(x->parent);
            }
            //当x的兄弟是黑色时
            //当w的两个儿子都是黑色时
            if(w->leftchild->color == black && w->rightchild->color == black)
            {
                w->color = red;//w颜色减去黑色
                x = x->parent;//x上移
            }
            //当w的右儿子是红色，左儿子是黑色时,把左儿子转换为红色
            else if(w->leftchild->color == red && w->rightchild->color == black)
            {
                w->rightchild->color = black;
                w->color = red;
                left_rotate(w);
                w = w->parent;
            }
            //w的左儿子是红色
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
    nill->color = black;//一开始x为nill时，会在第一次上移前把nill颜色设置为红色
}

#endif // REDBLACKTREE_H_INCLUDED
