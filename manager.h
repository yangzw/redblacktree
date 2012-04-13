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
		redblacktree<book> booktree;//用户的红黑树
		redblacktree<user> usrtree;//图书的红黑树
		bool searchbook(const string& bookname) const;//搜索图书，按照书名搜索
		bool searchuser(const string& usrname) const;//搜寻用户
		bool iskeyright(const string& inputkey) const;//匹配密码
		bool returnbook(const string& bookname) const;//还书
		bool loadfile(const string& filename) const;//加载数据
		bool delbook(const string& bookname) const;//从书库中删除书
		bool writetofile(const string& filename) const;//保存书库的变化
	public:
		manager();
		manager(const string& filename);
		void loadfiel();//加载数据
		void setdefualtfile();//设置数据默认存取的文件
		void getuserinfo();//得到用户的信息
		void addusr();//加入用户
		void deluser();//用户注销账号
		void addbook();//往书库里添书
		void delbook();//从书库里面删除书
		void borrowbook();//借书
		void pre_borrowbook();//预借图书
		void returnbook();//还书
		void getlibraryinfo();//得到图书馆的信息
		void savechanges();//保存库的变化
}


manager::manager():booknum(0),usernum(0){};

manager::manager(const string& filename)
{
	loadfile();
}

void manager::loadfile()
{
	cout << "输入文件名字: " << endl;
	string filename;
	cin >> filename;
	if(loadfile(filename))
		cout << "数据读入成功!" << endl;
	else
		cout << "文件读取失败= =" << endl;
}

bool manager::loadfile(const string& filename) const
{

}

//设置数据文件默认保存的位置
void manager::setdefaultfile()
{
	loadfile();
}


bool searchbook(const string& bookname) const
{
	booktree.search(bookname);
}
#endif // MANAGER_H_INCLUDED
