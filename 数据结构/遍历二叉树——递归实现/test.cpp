#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "BinaryTree.h"

void TestBinaryTree()
{
	int arr[] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int size = sizeof(arr)/sizeof(arr[0]);
	BinaryTree<int> T(arr,size,'#');

	cout<<"ǰ������� ";
	T.PrevOrder();
	cout<<"��������� ";
	T.InOrder();
	cout<<"��������� ";
	T.PostOrder();

	cout<<"�ж��ٸ��ڵ㣿 "<<T.Size()<<endl;
	cout<<"�ж��ٸ�Ҷ�ӽڵ㣿 "<<T.LeafSize()<<endl;
	cout<<"�������ĸ߶��Ƕ��٣� "<<T.Depth()<<endl;
	cout<<"��������Ҫ��ĵ�k�㣺"<<endl;
	int k = 0;
	cin>>k;
	cout<<"��k��ڵ�ĸ����� "<<T.GetKLevel(k)<<endl;

	typedef BinaryTreeNode<int> Node;
	Node* ret = T.Find(2);
	if (ret == NULL)
	{
		cout<<"û�ҵ�"<<endl;
	} 
	else
	{
		cout<<ret->_data<<" ";
		cout<<"�ҵ���"<<endl;
	}
}

int main()
{
	TestBinaryTree();
	system("pause");
	return 0;
}