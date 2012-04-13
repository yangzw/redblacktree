/*用户类的实现
 * by ya
 */
#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include<string>
#include"book.h"
#include"manager.h"
#include<iostream>
#define BORROWBOOKLIMIT 12

using namespace std;

class user
{
	friend class manager
	private:
		string name;//姓名
		string number;//学号
		string email;//邮箱
		book* mybook[BORROWBOOKLIMIT];//借的书
		int booknum;//借书的数量
		string key;//密码
		bool isbookfull() const;//判断是否已经借满了书
	public:
		user();
		user(const string& name);
		user(const string& name, const string& number, const string& email const string& key);
		user(const user &usr);//复制构造函数
		operator=(const user &usr);//赋值操作符
		void getinfor();
		string getname() const;
		string getnumber() const;
		string getemail() const;
		void getbookinfor();
		void setname(const string& name);
		void setnumber(const string& number);
		void setemail(const string& email);
		bool addbook(book* newbook);//用户借书
		int getbooknumb() const;
		void returnbook(book* rbook);//用户还书
};

user::user()
{
	for(int i = 0; i < BORROWBOOKLIMIT; ++i)
		mybook[i] = NULL;
}

user::user(const string& name)
{
	this->name = name;
	for(int i = 0; i < BORROWBOOKLIMIT; ++i)
		mybook[i] = NULL;
}

user::user(const string& name, const string* number, const tring& email, const string& key)
{
	this->name = name;
	this->number = number;
	this->email = email;
	this->key = key;
	for(int i = 0; i < BORROWBOOKLIMIT; ++i)
		mybook[i] = NULL;
}

//复制构造函数
user::user(const user &usr)
{
	name = usr.name;
	number = usr.number;
	email = usr.email;
	key = usr.key;
	for(int i = 0; i < BORROWBOOKLIMIT; ++i)
		mybook[i] = usr.mybook[i];
}
user::operator=(const user &usr)
{
	name = usr.name;
	number = usr.number;
	email = usr.email;
	key = usr.key;
	for(int i = 0; i < BORROWBOOKLIMIT; ++i)
		mybook[i] = usr.mybook[i];
	return *this;
}

bool user::isbookfull() const
{
	return booknum == BORROWBOOKLIMIT;
}

void user::getinfo()
{
	cout << "Name: " << endl;
	cout << "Xuehao: " << endl;
	cout << "Email: " << endl;
	cout << "Borrowed BookNumber: " << endl;
}

string user::getname() const
{
	return name;
}

string user::getnumber() const
{
	return number;
}

string user::getemail() const
{
	return email;
}

void user::getbookinfo()
{

}

void setname(const string& name)
{
	 this->name = name;
}

void  setnumber(const string& number)
{
	this->number = number;
}

void setemail(const string& email)
{
	this->email = email;
}

bool addbook(book* newbook)
{
	if(ibookful())
		return false;
	else
	{
		mybook*[booknum++] = newbook;
		return true;
	}
}

int getbooknumb() const
{
	return booknum;
}

void returnbook(book* rbook)
{
	int i(0);
	for(; i < BORROWBOOKLIMIT, mybook[i] != rbook; ++i);
	mybook[i] = NULL;
	booknum --;
}
#endif // USER_H_INCLUDED
