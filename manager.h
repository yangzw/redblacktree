/* manager是整个程序的控制类，通过该类对读者和书籍进行控制管理
 * by ya
 */
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include<iostream>
#include<string>
#include "user.h"
#include "book.h"
#include "redblacktree.h"

using namespace std;

class manager
{
private:
    int booknum;//书的数目
    int usernum;//用户数量
    string managerkey;//管理员密码
    redblacktree<string,book> booktree;//用户的红黑树
    redblacktree<string,user> usertree;//图书的红黑树
    bool searchbook(const string& bookname,book*& srbook) const;//搜索图书，按照书名搜索
    bool searchbook(const string& bookname) const;
    bool searchuser(const string& usrname,user*& srusr) const;//搜寻用户
    bool searchuser(const string& usrname) const;
    bool userkey(user* ur) const;//验证用户的密码
    bool ismanagerkey() const;//验证管理员密码
    //bool loadfile(const string& bookfile, const string& userfile) const;//加载数据
    //bool writetofile(const string& bookfile, const string& usergfile) const;//保存书库的变化
public:
    manager();
    //manager(const string& filename);
    //void loadfile();//加载数据
    //void setdefaultfile();//设置数据默认存取的文件
    void searchbook();//查找书籍
    void getuserinfo();//得到用户的信息
    void addusr();//加入用户
    void deluser();//用户注销账号
    void addbook();//往书库里添书
    void delbook();//从书库里面删除书
    void borrowbook();//借书
    void returnbook();//还书
    void getlibraryinfo();//得到图书馆的信息
    void savechanges();//保存库的变化
};


manager::manager()
{
    usernum = 0;
    booknum = 0;
    managerkey = "manager";
};
/*
manager::manager(const string& bookfile, const string& userfile)
{
    loadfile(bookfile, userfile);
}


void manager::loadfile()
{
    cout << "Input the bookfile's name: " << endl;
    string bookfilename;
    cin >> filename;
    cout << "Input the userfile's name: " << endl;
    string userfilename;
    cin >> userfilename;
    if(loadfile(bookfilename, userfilename))
        cout << "Data load sucessfully!" << endl;
    else
        cout << "Faile to load file" << endl;
}

bool manager::loadfile(const string& bookfile, const string& userfile) const
{
    ifstream inbkfile;
    inbkfile.open(bookfile);
    if(!inbkfile)
    {
        cerr << "error:unable to open bookfile!" << endl;
    }
    else
    {
        string
        inbkfile >>
    }
}

//设置数据文件默认保存的位置
void manager::setdefaultfile()
{
    loadfile();
}
*/

bool manager::searchbook(const string& bookname,book*& srbook) const
{
    return booktree.search(bookname,srbook);
}

bool manager::searchbook(const string& bookname) const
{
    return booktree.search(bookname);
}

void manager::searchbook()
{
    cout << "Input the book' name： ";
    string bookname;
    cin >> bookname;
    book* srbook = NULL;
    if(searchbook(bookname,srbook))
        srbook->getinfor();
    else
        cout << "Can't find such book!" << endl;
}


bool manager::searchuser(const string& usrname, user*& sruser) const
{
    return usertree.search(usrname, sruser);
}

bool manager::searchuser(const string& usrname) const
{
    return usertree.search(usrname);
}

void manager::getuserinfo()
{
    cout << "Please input your name: " << endl;
    string usrname;
    cin >> usrname;
    user* sruser = NULL;
    if(searchuser(usrname, sruser))
    {
        if(userkey(sruser))
        {
            cout << "Here is your information" << endl;
            sruser->showinfo();
        }
    }
    else
        cout << "The name is not registed yet!" << endl;
}

void manager::addusr()
{
    user usr;
    cout << "Input your name: ";
    string tmp;
    cin >> tmp;
    while(searchuser(tmp))
    {
        cout << "Sorry, the name is already token" << endl;
        cout << "Input again? input y or n " << endl;
        char choice;
        cin >> choice;
        if(choice == 'y')
        {
            cout << "Input your name: ";
            cin >> tmp;
        }
        else
            return;
    }
    usr.setname(tmp);
    cout << "Input your student number: ";
    cin >> tmp;
    usr.setnumber(tmp);
    cout << "Input your email: ";
    cin >> tmp;
    usr.setemail(tmp);
    cout <<"Input your key: ";
    cin >> usr.key;
    cout << "Congratulations! you finish the register!" << endl;
    usernum++;
    usertree.RB_insert(usr,usr.name);
}

//用户的密码验证
bool manager::userkey(user* ur) const
{
    cout << "input your key:" << endl;
    string ukey;
    cin >> ukey;
    while(ukey != ur->key)
    {
        cout << "wrong key!" << endl;
        cout << "Input again? input y or n " << endl;
        char choice;
        cin >> choice;
        if(choice == 'y')
        {
            cout << "Input your key: ";
            cin >> ukey;
        }
        else
            return false;
    }
    return true;
}

//用户的注销
void manager::deluser()
{
    string delusr;
    cout << "Input your name:";
    cin >> delusr;
    user* usr(0);
    if(!searchuser(delusr,usr))
        cout << "can't find your name" << endl;
    else
    {
        if(userkey(usr))
            usertree.RB_DELETE(delusr);
        usernum--;
    }
}

//验证管理员密码
bool manager::ismanagerkey() const
{
    cout << "Please input manager key: ";
    string inkey;
    cin >> inkey;
    while(inkey != managerkey)
    {
        cout << "wrong key!" << endl;
        cout << "Input again? input y or n " << endl;
        char choice;
        cin >> choice;
        if(choice == 'y')
        {
            cout << "Input your key: ";
            cin >> inkey;
        }
        else
            return false;
    }
    return true;
}

//管理员增加图书
void manager::addbook()
{
    if(ismanagerkey())
    {
        book bk;
        cout << "Input the book's name: ";
        string tmp;
        cin >> tmp;
        while(searchbook(tmp))
        {
            cout << "Sorry, the book is already in the library" << endl;
            cout << "Input again? input y or n " << endl;
            char choice;
            cin >> choice;
            if(choice == 'y')
            {
                cout << "Input the book's name: ";
                cin >> tmp;
            }
            else
                return;
        }
        bk.setbkname(tmp);
        cout << "Input isbn: ";
        cin >> tmp;
        bk.setisbn(tmp);
        cout << "Input the author: ";
        cin >> tmp;
        bk.setauthor(tmp);
        cout << "Done" << endl;
        booknum++;
        booktree.RB_insert(bk, bk.bkname);
    }
}

//管理员删除图书
void manager::delbook()
{
    if(ismanagerkey())
    {
        string delbk;
        cout << "Input the book's name:";
        cin >> delbk;
        book* bk(0);
        if(!searchbook(delbk,bk))
            cout << "can't find the book" << endl;
        else
        {
            booktree.RB_DELETE(delbk);
            booknum--;
        }
    }
}

//借书
void manager::borrowbook()
{
    string bbk;
    cout << "Input the book's name:";
    cin >> bbk;
    book* bk(0);
    if(!searchbook(bbk,bk))
        cout << "can't find the book" << endl;
    else
    {
        string busr;
        cout << "Input your name:";
        cin >> busr;
        user* usr(0);
        if(!searchuser(busr,usr))
            cout << "can't find your name" << endl;
        else
        {
            if(!usr->isbookfull())
            {
                if(userkey(usr))
                {
                    usr->addbook(bk);
                    bk->setstate(borrowed);
                }
            }
            else
                cout << "You have borrowed enough book" << endl;
        }
    }
}

//还书
void manager::returnbook()
{
    string rbk;
    cout << "Input the book's name:";
    cin >> rbk;
    book* bk(0);
    if(!searchbook(rbk,bk))
        cout << "can't find the book" << endl;
    else
    {
        string rusr;
        cout << "Input your name:";
        cin >> rusr;
        user* usr(0);
        if(!searchuser(rusr,usr))
            cout << "can't find user name" << endl;
        else
        {
            usr->returnbook(bk);
            bk->setstate(clean);
        }
    }
}

//得到图书馆的信息
void manager::getlibraryinfo()
{
    cout << "The whole library has "<< endl;
    cout << booknum << " books and" << endl;
    cout << usernum << " users" << endl;
}
/*
void manager::savechanges()
{
}
*/
#endif // MANAGER_H_INCLUDED
