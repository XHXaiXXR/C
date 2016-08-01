#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include<vector>
#include <list>
#include <algorithm>

void PrintVector(vector<int> v)
{
	vector<int>::iterator it = v.begin();//iterator->������
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
	list<int>::iterator it = l.begin();//iterator->������
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

	//ɾ��һ������
	//list<int>::iterator ret = find(l.begin(),l.end(),3);
	//if (ret != l.end())
	//{
	//	cout<<"�ҵ��ˣ�"<<endl;
	//	l.erase(ret);//erast������һ��������Ҳ��������������
	//	PrintList(l);
	//}
	//else
	//{
	//	cout<<"û�ҵ�������"<<endl;
	//	PrintList(l);
	//}

	l.sort();//����
	PrintList(l);
	l.unique();//ȥ��
	PrintList(l);
	list<int>::iterator first = find(l.begin(),l.end(),1);//��ʼɾ����λ��
	list<int>::iterator last = find(l.begin(),l.end(),3);//����λ�õ���һ��λ��
	l.erase(first,last);//erast������һ��������Ҳ��������������
	PrintList(l);
}

int main()
{
	TestVector();
	//TestList();
	system("pause");
	return 0;
}