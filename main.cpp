#include <iostream>
#include "redblacktree.h"
#include "manager.h"

using namespace std;

int main()
{
	/*
    redblacktree<int,int> test;
    int i(0);
    cout << "try for brach" << endl;
    for(; i < 5; ++i)
    {
        test.RB_insert(i,i);
    }
    test.pre_tree_walk();
    test.mid_tree_walk();
    test.RB_DELETE(3);
    cout << test.getsize() << endl;
    test.pre_tree_walk();
    test.mid_tree_walk();
    test.RB_insert(7,7);
    test.RB_insert(3,3);
    test.pre_tree_walk();
    test.mid_tree_walk();
   // test.RB_insert(6,6);
    cout << test.search(5) << endl;
    test.RB_DELETE(7);
    test.pre_tree_walk();
    test.mid_tree_walk();
    */
    manager Mainmanager;
    Mainmanager.addusr();
    Mainmanager.getuserinfo();
    Mainmanager.getlibraryinfo();
    Mainmanager.addbook();
    Mainmanager.getlibraryinfo();
    Mainmanager.borrowbook();
    Mainmanager.getuserinfo();
    return 0;
}
