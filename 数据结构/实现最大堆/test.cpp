#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include "Heap.h"

void Test()
{
	int arr[] = {10,11,13,12,16,18,15,17,14,19};
	int size = sizeof(arr) / sizeof(arr[0]);
	Heap<int> h(arr,size);
	h.Cout();

	h.Pop();
	h.Cout();

	h.Push(20);
	h.Cout();
	h.Push(20);
	h.Cout();
}

int main()
{
	Test();
	system("pause");
	return 0;
}