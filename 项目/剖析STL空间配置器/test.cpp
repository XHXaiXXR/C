#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include "MallocAllocTemplate.h"
#include "DefaultAllocTemplate.h"

void test()
{
	DefaultAllocTemplate<true,0> d;
	char* p = (char*)d.Allocate(100);
	int* q = (int*)d.Allocate(129);
	d.DeAllocate(q,129);
	d.DeAllocate(p,100);
}

int main()
{
	test();
	system("pause");
	return 0;
}