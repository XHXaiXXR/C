#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "Heap.h"

void Test()
{
	int arr[] = {10,16,18,12,11,13,15,17,14,19};
	int size = sizeof(arr)/sizeof(arr[0]);
	Heap<int,Less<int>> h(arr,size);//Ð¡¶Ñ
	//Heap<int> h(arr,size);//´ó¶Ñ
	h.Cout();

	h.Push(20);
	h.Push(5);
	h.Cout();

	h.Pop();
	h.Pop();
	h.Cout();
}
int main()
{
	Test();
	system("pause");
	return 0;
}