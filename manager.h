/* manager是整个程序的控制类，通过该类对读者和书籍进行控制管理
 * 本系统提供从文件中读取数据进行初始化
 * 也能够将变化写入文件中
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

class manage
{
	private:
		int booknum;//书的数目
		int usernum;//用户数量
		string managerkey;//管理员密码
		redblacktree<book,string> booktree;//用户的红黑树
		redblacktree<user,string> usrtree;//图书的红黑树
		bool searchbook(const string& bookname,book* srbook) const;//搜索图书，按照书名搜索
		bool searchbook(const string& bookname) const;
		bool searchuser(const string& usrname,user* srusr) const;//搜寻用户
		bool searchuser(const string& usrname) const;
		bool userkey(user* ur) const;//验证用户的密码
		bool managerkey() const;//验证管理员密码
		bool loadfile(const string& filename) const;//加载数据
		bool writetofile(const string& filename) const;//保存书库的变化
	public:
		manager();
		manager(const string& filename);
		void loadfile();//加载数据
		void setdefualtfile();//设置数据默认存取的文件
		void searchbook();//查找书籍
		void getuserinfo(const string& usrname);//得到用户的信息
		void addusr();//加入用户
		void deluser();//用户注销账号
		void addbook();//往书库里添书
		void delbook();//从书库里面删除书
		void borrowbook();//借书
		void returnbook();//还书
		void getlibraryinfo();//得到图书馆的信息
		void savechanges();//保存库的变化
}


manager::manager():booknum(0),usernum(0){};

manager::manager(const string& filename)
{
	loadfile(filename);
}

void manager::loadfile()
{
	cout << "Input the file's name: " << endl;
	string filename;
	cin >> filename;
	if(loadfile(filename))
		cout << "Data load sucessfully!" << endl;
	else
		cout << "Faile to load file" << endl;
}

bool manager::loadfile(const string& filename) const
{

}

//设置数据文件默认保存的位置
void manager::setdefaultfile()
{
	loadfile();
}


bool manager::searchbook(const string& bookname,book* srbook) const
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


bool manager::searchuser(const string& usrname, user* sruser) const
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
		cout << "Here is your information" << endl;
		sruser->getinfo();
	}
	else
		cout << "The name is not registed yet!" << endl;	
}

void manager::addusr()
{
	user* usr = new user;
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
	usr->setname(tmp);
	cout << "Input your student number: ";
	cin >> tmp;
	usr->setnumber(tmp);
	cout << "Input your email: ";
	cin >> tmp;
	usr->setemail(tmp);
	cout <<"Input your key: ";
	cin >> usr->key;
	cout << "Congratulations! you finish the register!" << endl;
	usernum++;
	usertree.RB_insert(user,user.name);
}

//用户的密码验证
bool manager::userkey(user* ur) const
{
		cout << "input your key:" << endl;
		string ukey;
		cin >> ukey;
		while(ukey != usr->key)
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
	user* usr;
	if(!searchuser(delusr,usr))
		cout << "can't find your name" << endl;
	else
	{
		if(userkey(usr))
		usertree.RB_DELETE(delusr);
		usrernum--;
	}
}

//验证管理员密码
bool manager::managerkey(const string& mkay) const
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
	if(managerkey()){
	book* bk = new book;
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
	bk->setbkname(tmp);
	cout << "Input isbn: ";
	cin >> tmp;
	bk->setisbn(tmp);
	cout << "Input the author: ";
	cin >> tmp;
	bk->setauthor(tmp);
	cout << "Done" << endl;
	booknum++;
	booktree.RB_insert(book,book.name);
	}
}

//管理员删除图书
void manager::delbook()
{
	if(managerkey())
	{
	string delbk;
	cout << "Input the book's name:";
	cin >> delbk;
	book* bk;
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
	book* bk;
	if(!searchuser(bbk,bk))
		cout << "can't find the book" << endl;
	else
	{
	string busr;
	cout << "Input your name:";
	cin >> busr;
	user* usr;
	if(!searchuser(busr,usr))
		cout << "can't find your name" << endl;
	else
	{
		if(!usr->isbookfull())
		{
			if(userkey(usr))
			{
			usr->addbook(bk);
			bk->setstatus(borrowed);
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
	book* bk;
	if(!searchuser(rbk,bk))
		cout << "can't find the book" << endl;
	else
	{
	string rusr;
	cout << "Input your name:";
	cin >> rusr;
	user* usr;
	if(!searchuser(rusr,usr))
		cout << "can't find user name" << endl;
	else
	{
			usr->returnbook(bk);
			bk->setstatus(clean);
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

void manager::savechanges()
{
}
#endif // MANAGER_H_INCLUDED
