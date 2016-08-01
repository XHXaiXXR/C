#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include<vector>
#include <list>
#include <algorithm>

void PrintVector(vector<int> v)
{
	vector<int>::iterator it = v.begin();//iterator->迭代器
	while (it != v.end())
	{
		cout<<(*it)<<" ";
		++it;
	}
	cout<<endl;
}
void TestVector()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(3);
	v.push_back(1);

	PrintVector(v);
}

void PrintList(list<int> l)
{
	list<int>::iterator it = l.begin();//iterator->迭代器
	while (it != l.end())
	{
		cout<<(*it)<<" ";
		++it;
	}
	cout<<endl;
}
void TestList()
{
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(1);
	l.push_back(5);
	l.push_back(3);
	l.push_back(2);

	PrintList(l);

	//删除一个数据
	//list<int>::iterator ret = find(l.begin(),l.end(),3);
	//if (ret != l.end())
	//{
	//	cout<<"找到了！"<<endl;
	//	l.erase(ret);//erast可以有一个参数。也可以有两个参数
	//	PrintList(l);
	//}
	//else
	//{
	//	cout<<"没找到。。。"<<endl;
	//	PrintList(l);
	//}

	l.sort();//排序
	PrintList(l);
	l.unique();//去重
	PrintList(l);
	list<int>::iterator first = find(l.begin(),l.end(),1);//开始删除的位置
	list<int>::iterator last = find(l.begin(),l.end(),3);//结束位置的下一个位置
	l.erase(first,last);//erast可以有一个参数。也可以有两个参数
	PrintList(l);
}

int main()
{
	TestVector();
	//TestList();
	system("pause");
	return 0;
}