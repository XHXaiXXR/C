#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include "GraphLink.h"

void Test()
{
	GraphLink<char,int> g("ABCDE",5,false);
	g.AddEdge('B','C',10);
	g.AddEdge('B','D',20);
	g.AddEdge('B','E',30);
	g.AddEdge('C','E',40);
	g.AddEdge('D','A',10);
	g.AddEdge('A','E',20);

	g.Display();
}
int main()
{
	Test();
	system("pause");
	return 0;
}