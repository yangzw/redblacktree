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

    visit() {}
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
    bool RB_DELETE(T value);//删除算法
private:
    node<T>* root;
    void pre_tree_walk(node<T>* root);
    node<T>* tree_successor(node<T>* x);//求节点的后继
    void left_rotate(node<T>* key);//左旋
    void right_rotate(node<T>* key);//右旋
    void RB_insert_fixup(node<T>* x);//插入调整
    void RB_DELETE(node<T>* x);//删除某个节点
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
//插入调整
template<typename T>
void redblacktree<T>::RB_insert_fixup(node<T>* x)
{
    while(x->parent->color == red)
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
                if(ly == ly->parent->rightchild)//是父亲的右支，先旋转成左支，再调整
                {
                    x = x->parent;
                    left_rotate(x);
                }
                x->parent->color = black;
                x->parent->parent->color = red;
                right_rotate(x->parent);
            }
        }
        else//父亲是左支
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
                if(ry == ry->parent->leftchild)//是父亲的左支时，先旋转，再调整
                {
                    x = x->parent;
                    right_rotate(x);
                }
                x->parent->color = black;
                x->parent->parent->color = red;
                left_rotate(x->parent);
            }
        }
    }
}


template <typename T>
bool redblacktree<T>::RB_DELETE(T value)
{
    node<T>* x = rbsearch(value);//找该节点
    if(!x)//未找到
        {cout << "can't find the key to be deleted" << endl;return false;}
    else
        RB_DELETE(x);//找到后进行删除操作
    return true;
}


template <typename T>
void redblacktree<T>::RB_DELETE(node<T>* x)
{
    node<T>* z = NULL;
    if(!x->rightchild || !x->leftchild)
        z = x;
    else
        z = tree_successor(x);//如果x节点有两个儿子，则设z为其后继
    node<T>* y = NULL;
    if(z->leftchild)
        y = z->leftchild;
    else
        y = z->rightchild;
    y->parent = z->parent;
    if(!z->parent)//当删除的是根时
        root = y;
    else if(z = z->parent->leftchild)
        y = z->parent->leftchild;
    else
        y = z->parent->rightchild;
    if(x != z)
            x->value = z->value;
    if(z->color =  black)//当删除的节点时黑色时，则需要对树进行调整
        RB_DELETE_fixup(y);
}
#endif // REDBLACKTREE_H_INCLUDED
