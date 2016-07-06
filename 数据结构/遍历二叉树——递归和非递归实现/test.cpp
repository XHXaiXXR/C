#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include "BBinaryTree.h";

void TestBinaryTree()
{
	int arr[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	BinaryTree<int> b(arr,size,'#');
	cout<<"�ݹ�ʵ�֣�"<<endl;
	cout<<"ǰ�������";
	b.PrevOrder();
	cout<<"���������";
	b.InOrder();
	cout<<"���������";
	b.PostOrder();
	cout<<"�ǵݹ�ʵ�֣�"<<endl;
	cout<<"���������";
	b.QueueLevelOrder();
	cout<<"ǰ�������";
	b.StackPrevOrder();
	cout<<"���������";
	b.StackInOrder();
	cout<<"���������";
	b.StackPostOrder();
}

int main()
{
	TestBinaryTree();
	system("pause");
	return 0;
}