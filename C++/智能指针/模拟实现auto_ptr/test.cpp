#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "AutoPtr.h"

struct A  
{  
	int b;  
};  

void TestAutoPtr()
{
	  AutoPtr<int> p(new int);  
	  
	  *p.Get() = 100;  
	  *p = 6; 
	  cout<<*p.Get()<<endl;  
	  cout<<*p<<endl; 
	  
	  AutoPtr <A> p2(new A);  
	  p2->b = 6;  
	  cout<<p2->b <<endl; 

	  AutoPtr<A> p3(p2);
	  p3->b = 8;
	  cout<<p3->b<<endl;
	  //cout<<p2->b<<endl; //通过权限转移，p2已经被释放掉了，你不能通过一个释放掉的对象去访问他的成员
}

int main()
{
	TestAutoPtr();
	system("pause");
	return 0;
}