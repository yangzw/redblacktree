#include <iostream>
#include "redblacktree.h"

using namespace std;

int main()
{
    redblacktree<int> test;
    int i(0);
    cout << "try for brach" << endl;
    for(; i < 10; ++i)
    {
        test.RB_insert(i);
    }
    test.pre_tree_walk();
    return 0;
}
