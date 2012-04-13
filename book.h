/*图书类的实现
 * by ya
 */
#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include<string>
#include<iostream>
#include"manager.h"

using namespace std;

enum State{clean=0, borrowed, advanced-borrowed};

class book
{
priate:
	friend class manager
	string bkname;
	string author;
	string isbn;
	State state;
	public:
	book(){ state = clean;}
	book(const string& name);
	book(const string& name, const string& ibn, const string& ath)
	book(const book& bk);//复制构造函数
	operator=(const book& bk);//赋值操作符
	void getinfor();
	string getbkname() const;
	string getauthor() const;
	string getisbn() const;
	void getstate();
	void setstate(const State& state);
	void setbkname(const string& name);
	void setauthor(const string& author);
	void setisbn(const string& isbn);
};

book::book(const string& name):bkname(name),state(clean){};

book::book(const string& name, const string& ibn, const string& ath):bkname(name),isbn(ibn),author(ath),state(clean){};

book::book(const book& bk):bkname(bk.bkname),isbn(bk.isbn),author(bk.author),state(bk.state){};

book::operator=(const book& bk)
{
	bkname = bk.bkname;
	isbn = bk.isbn;
	author = bk.author;
	state = bk.state;
	return *this;
}

void book::getinfor()
{
	cout << "Bookname: " << bkname << endl;
	cout << "Author: " << author << endl;
	cout << "Isbn: " << isbn << endl;
	cout << "State: " << state << endl;
}

string book::getbkname() const
{
	return bkname;
}

string book::getauthor() const
{
	return author;
}

string book::getisbn() const
{
	return isbn;
}

void book::getstate()
{
	cout << "State: " << state << endl;
}

void book::setstate(const State& state)
{
	this->state = state;
}

void book::setbkname(const string& bkname)
{
	this->bkname = bkname;
}

void book::setauthor(const string& author)
{
	this->author = author;
}

void book::setisbn(const string& isbn)
{
	this->isbn = isbn;
}
#endif // BOOK_H_INCLUDED
