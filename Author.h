/*作者类，用于来进行作者的查找
 */
#ifndef AUTHOR_H_INCLUDED
#define AUTHOR_H_INCLUDED
#include"book.h"
#include<iostream>
#include<list>

using namespace std;

class Author
{
private:
    string Authorname;
    list<book*> bklist;
    int bknum;
public:
    Author();
    Author(book*& bk);
    void addbook(book*& bk);//加入图书后的处理
    void  show();//显示图书
    void delbook(book*& bk);//删除图书
    int getbknum();
    string getauthor() const;
};

Author::Author()//string和list类自带构造函数
{
    bknum = 0;
}

Author::Author(book*& bk)
{
    Authorname = bk->getauthor();
    bknum = 1;
    bklist.push_back(bk);
}

void Author::addbook(book*& bk)
{
    bklist.push_back(bk);
    bknum++;
}

void Author::delbook(book*& bk)
{
    for(list<book*>::iterator iter = bklist.begin(); iter != bklist.end(); ++ iter)
    {
        if(*iter == bk)
        {
            bklist.erase(iter);//delete the deleted book
            iter = bklist.begin();
            bknum --;
        }
    }
}

void  Author::show()
{
    for(list<book*>::iterator iter = bklist.begin(); iter != bklist.end(); ++ iter)
        cout << (*iter)->getbkname() << endl;
}

int Author::getbknum()
{
    return bknum;
}

string Author::getauthor() const
{
	return Authorname;
}
#endif // AUTHOR_H_INCLUDED
