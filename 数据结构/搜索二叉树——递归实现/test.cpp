#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "BSTreeR.h"

void TestBSTreeR()
{
	BSTreeR<int,int> bsr;
	int arr[] = {5,9,3,7,2,4,0,8,6,1};
	int size = sizeof(arr)/sizeof(arr[0]);

	for (int i = 0;i < size;i++)
	{
		bsr.Insert(arr[i],i+1);
	}
	bsr.IrOrder();
	cout<<endl;

	cout<<bsr.Find(6)->_key<<" "<<bsr.Find(6)->_value<<endl;

	bsr.ReMove(5);
	bsr.ReMove(9);
	bsr.ReMove(1);
	bsr.ReMove(55);
	bsr.IrOrder();
	cout<<endl;

	bsr.ReMove(0);
	bsr.ReMove(1);
	bsr.ReMove(2);
	bsr.ReMove(3);
	bsr.ReMove(4);
	bsr.ReMove(5);
	bsr.ReMove(6);
	bsr.ReMove(7);
	bsr.ReMove(8);
	bsr.ReMove(9);
	bsr.IrOrder();
	cout<<endl;
}
int main()
{
	TestBSTreeR();
	system("pause");
	return 0;
}