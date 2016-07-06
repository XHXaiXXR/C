#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include "BBinaryTree.h";

void TestBinaryTree()
{
	int arr[10] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	size_t size = sizeof(arr)/sizeof(arr[0]);
	BinaryTree<int> b(arr,size,'#');
	cout<<"递归实现："<<endl;
	cout<<"前序遍历：";
	b.PrevOrder();
	cout<<"中序遍历：";
	b.InOrder();
	cout<<"后序遍历：";
	b.PostOrder();
	cout<<"非递归实现："<<endl;
	cout<<"层序遍历：";
	b.QueueLevelOrder();
	cout<<"前序遍历：";
	b.StackPrevOrder();
	cout<<"中序遍历：";
	b.StackInOrder();
	cout<<"后序遍历：";
	b.StackPostOrder();
}

int main()
{
	TestBinaryTree();
	system("pause");
	return 0;
}