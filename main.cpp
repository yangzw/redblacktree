#include <iostream>
#include "redblacktree.h"

using namespace std;

int main()
{
    redblacktree<int> test;
    int i(0);
    cout << "try for brach" << endl;
    for(; i < 5; ++i)
    {
        test.RB_insert(i);
    }
    test.pre_tree_walk();
    test.mid_tree_walk();
    test.RB_DELETE(3);
    cout << test.getsize() << endl;
    test.pre_tree_walk();
    test.mid_tree_walk();
    test.search(6);
    return 0;
}
