#include <iostream>
#include "redblacktree.h"
#include "manager.h"

using namespace std;
void start(manager& mmanager);//开始
void printuserwindow();//打印用户窗口
void printmanagerwindow();//打印管理员窗口
void userprocess(manager& mmanager);//用户处理
void managerprocess(manager& mmanager);//管理员处理

int main()
{
    manager Mainmanager;
    start(Mainmanager);
    return 0;
}

void printuserwindow()
{
    cout << "		------------------------------------------------" << endl;
    cout << "		*	  Welcome to the libaray	        *" << endl;
    cout << "		------------------------------------------------" << endl;
    cout << "		* 1.注册   		2.查看用户信息		*" << endl;
    cout << "		* 3.查找书籍(精确匹配)  4.查找书（模糊匹配）	*" << endl;
    cout << "		* 5.借书   		6.还书			*" << endl;
    cout << "		* 7.查找作者		    		        *" << endl;
    cout << "		* 8.注销用户            0.退出		        *" << endl;
    cout << "		-------------------------------------------------" << endl;
}

void printmanagerwindow()
{
    cout << "		------------------------------------------------" << endl;
    cout << "		*	  Welcome to the libaray	        *" << endl;
    cout << "		------------------------------------------------" << endl;
    cout << "		* 1.添加图书		 2.删除图书		*" << endl;
    cout << "		* 3.查找书籍(精确匹配)   4.查找书（模糊匹配）	*" << endl;
    cout << "		* 5.查看图书馆信息       6.保存修改		*" << endl;
    cout << "		* 7.查找作者		 0.退出			*" << endl;
    cout << "		------------------------------------------------" << endl;
}

void start(manager& mmanager)
{
    cout << "		------------------------------------------------" << endl;
    cout << "		*	  Welcome to the libaray	        *" << endl;
    cout << "		------------------------------------------------" << endl;
    cout << "		* 	    which user are you?			*" << endl;
    cout << "		* 1.user			2.manager	*" << endl;
    cout << "		* 	                        press 0 to quit *" << endl;
    cout << "		------------------------------------------------" << endl;
    int choice(0);
    cin >> choice;
    getchar();
    if(choice == 1)
        userprocess(mmanager);
    else if(choice == 2)
        managerprocess(mmanager);
    else
        return;
}

void userprocess(manager& mmanager)
{
    mmanager.load();
    printuserwindow();
    cout << endl;
    cout << "< < < < < < < < < < < < < "<< endl;
    int choice(0);
    int flag = 1;
    while(cin >> choice && getchar())
    {
        switch(choice)
        {
        case(0):
        {
            cout << "save changs?y/n" << endl;
            char cho(0);
            cin >> cho;
            getchar();
            if(cho == 'y')
                mmanager.savechanges();
            flag = 0;
            break;
        }
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
            mmanager.searchbykey();
            break;
        case(5):
            mmanager.borrowbook();
            break;
        case(6):
            mmanager.returnbook();
            break;
        case(7):
            mmanager.searchAuthor();
            break;
        case(8):
            mmanager.deluser();
            break;
        default:
            cout << "Wrong input!" << endl;
        }
        if(flag == 0)
            break;
        cout << "< < < < < < < < < < < < < "<< endl;
        cout << endl;
        printuserwindow();
    }
    start(mmanager);
}

void managerprocess(manager& mmanager)
{
    if(mmanager.ismanagerkey())
    {
        cout << "load file? y/n" << endl;
        char choice1(0);
        cin >> choice1;
        getchar();
        if(choice1 == 'y')
            mmanager.loadfile();
        printmanagerwindow();
        cout << endl;
        cout << "< < < < < < < < < < < < < "<< endl;
        int choice(0);
        int flag = 1;
        while(cin >> choice && getchar())
        {
            switch(choice)
            {
            case(0):
            {
                cout << "save changs?y/n" << endl;
                char cho(0);
                cin >> cho;
                getchar();
                if(cho == 'y')
                    mmanager.savechanges();
                flag = 0;
                break;
            }
            case(1):
                mmanager.addbook();
                break;
            case(2):
                mmanager.delbook();
                break;
            case(3):
                mmanager.searchbook();
                break;
            case(4):
                mmanager.searchbykey();
                break;
            case(5):
                mmanager.getlibraryinfo();
                break;
            case(6):
                mmanager.savechanges();
                break;
            case(7):
                mmanager.searchAuthor();
                break;
            default:
                cout << "Wrong input!" << endl;
            }
            if(flag == 0)
                break;
            cout << "< < < < < < < < < < < < < "<< endl;
            cout << endl;
            printmanagerwindow();
        }
    }
    start(mmanager);
}
