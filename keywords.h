#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED
#include<vector>
#include<iostream>

class keywords
{
    private:
    string key;
    vector<string> bklist(0);
    int bkmun;
    public:
    keywords(){bknum = 0;}//string和vector类自带构造函数
    void addbook(const string& bk){bklist.push_back(bk);bkmun++;}//增加关键字所对的图书
    void show(){for(int i = 0; i < bknum; i++)
    cout << bklist(i) << endl;}//显示含有该关键字的图书
}
#endif // KEYWORDS_H_INCLUDED
