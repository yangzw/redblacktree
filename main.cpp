#include <iostream>
#include "redblacktree.h"
#include "manager.h"

using namespace std;
void printhead();//打印表头
void start(manager& mmanager);//开始

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
    start(Mainmanager);
    return 0;
}

void printhead()
{
    cout << "		--------------------------------------------" << endl;
    cout << "		*	Welcome to the libaray		   *" << endl;
    cout << "		--------------------------------------------" << endl;
    cout << "		* 1.注册 2.查看用户信息 3.按照书名查找书籍 *" << endl;
    cout << "		* 4.借书    5.还书   	6.注销用户         *" << endl;
    cout << "		* 7.添加图书（管理员）8.删除图书（管理员） *" << endl;
    cout << "		* 9.查看图书馆信息   0.退出  	 	   *" << endl;
    cout << "		---------------------------------------------" << endl;
}

void start(manager& mmanager)
{
    mmanger.loadfile();
    printhead();
    cout << endl;
    cout << "< < < < < < < < < < < < < "<< endl;
    int choice(0);
    while(cin >> choice && choice != 0)
    {
        switch(choice)
        {
        case(0):
            return;
        case(1):
            mmanager.addusr();
            break;
        case(2):
            mmanager.getuserinfo();
            break;
        case(3):
            mmanager.searchbook();
            break;
        case(4):
            mmanager.borrowbook();
            break;
        case(5):
            mmanager.returnbook();
            break;
        case(6):
            mmanager.deluser();
            break;
        case(7):
            mmanager.addbook();
            break;
        case(8):
            mmanager.delbook();
            break;
        case(9):
            mmanager.getlibraryinfo();
            break;
        default:
            cout << "Wrong input!" << endl;
        }
        cout << "< < < < < < < < < < < < < "<< endl;
        cout << endl;
        printhead();
    }
}
