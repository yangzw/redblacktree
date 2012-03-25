#ifndef REDBLACKTREE_H_INCLUDED
#define REDBLACKTREE_H_INCLUDED

enum Color {black = 0, red};
//节点
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

    visit(){}
};

node<T> nill(black);


template<typename T>
class redblacktree
{
public:
    redblacktree()
    {
        root = NULL;
    }
    node<T>* rbsearch(T key);//查找
    void pre_tree_walk();//前序遍历
    node<T>* tree_max();//树的最大最小
    node<T>* tree_min();
    void RB_insert(T value);//插入算法
    void RB_DELETE(T value);//删除算法
private:
    node<T>* root;
    void pre_tree_walk(node<T>* root);
    node<T>* tree_successor(node<T>* x);//求节点的后继
    void left_rotate(node<T>* key);//左旋
    void right_rotate(node<T>* key);//右旋
    void RB_insert_fixup(node<T>* x);//插入调整
    void RB_DELETE_fixup(node<T>* x);//删除调整
}

//查找
template<typename T>
node<T>* redblacktree<T>::rbsearch(T key)
{
    node<T>* x = root;
    while(x!= NULL && key != x->value)
    {
        if(key > x->value)
            x = x ->rightchild;
        else
            x= x ->leftchild;
    }
    return x;
}

//前序遍历
template<typename T>
void redblacktree<T>::pre_tree_walk(node<T>* root)
{
    if(root)
    {
        pre_tree_walk(root->leftchild);
        root->visit();
        pre_tree_walk(root->rightchild);
    }
}
template<typename T>
void redblacktree<T>::re-tree-walk()
{
    pre_tree_walk(root);
}

//最大最小
template<typename T>
node<T>*  redblacktree<T>::tree_max()
{
    node<T>* current = root;
    while(current)
        current = current->rightchild;
    return current;
}
template<typename T>
node<T>* redblacktree<T>::tree_min()
{
    node<T>* current = root;
    while(current)
        current = current->leftchild;
    return current;
}

//求后继结点
template<typename T>
node<T>* redblacktree<T>::tree_successor(node<T>* x)
{
    if(!x->rightchild)//x有右孩子时，后继就是右孩子的最小节点
        return tree_min(x->leftchild);
    node<T>* y = x->parent;//向上求后继
    while(y && x = y->rightchild)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

//左旋
template<typename T>
void redblacktree<T>::left_rotate(node<T>* key)
{
    node<T>* y = key->rightchild;
    key->rightchild = y->leftchild;
    y->leftchild->parent = key;
    key->parent = y->parent;
    if(!key->parnt)
        root = y;
    y->leftchild = key;
    if(key = key->parent->leftchild)
        y->leftchild = key;
    else
        y->rightchild = key;
    key->parent = y;
}

//右旋
template<typename T>
void redblacktree<T>::right_rotate(node<T>* key)
{
    node<T>* y = key->leftchild;
    key->leftchild = y->rightchild;
    y->rightchild->parent = key;
    key->parent = y->parent;
    if(!key->parnt)
        root = y;
    y->rightchild = key;
    if(key = key->parent->leftchild)
        y->leftchild = key;
    else
        y->rightchild = key;
    key->parent = y;
}

template<typename T>
void redblacktree<T>::RB_insert(T value)//插入算法
{
    node<T> x(value, red);
    node<T>* current = root;
    node<T>* y;
    while(current)
    {
        y = current;
        if(value > current->key)
            current = current->rightchild;
        else
        current = current ->leftchild;
    }
    x->parent = y;
    if(!y)//当插入节点正好是根时
        root = x;
    else
    {
        if(x->value > y->value)
            x = y->rightchild;
        else
            x = y->rightchild;
    }
    RB_insert_fixup(x);//插入调整，使之满足红黑树性质
}

template<typename T>
void redblacktree<T>::RB_insert_fixup(node<T>* x)
{
}
#endif // REDBLACKTREE_H_INCLUDED
