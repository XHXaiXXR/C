#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include "BinaryTree.h"

void TestBinaryTree()
{
	int arr[] = {1, 2, 3, '#', '#', 4, '#' , '#', 5, 6};
	int size = sizeof(arr)/sizeof(arr[0]);
	BinaryTree<int> T(arr,size,'#');

	cout<<"前序遍历： ";
	T.PrevOrder();
	cout<<"中序遍历： ";
	T.InOrder();
	cout<<"后序遍历： ";
	T.PostOrder();

	cout<<"有多少个节点？ "<<T.Size()<<endl;
	cout<<"有多少个叶子节点？ "<<T.LeafSize()<<endl;
	cout<<"二叉树的高度是多少？ "<<T.Depth()<<endl;
	cout<<"输入你想要求的第k层："<<endl;
	int k = 0;
	cin>>k;
	cout<<"第k层节点的个数？ "<<T.GetKLevel(k)<<endl;

	typedef BinaryTreeNode<int> Node;
	Node* ret = T.Find(2);
	if (ret == NULL)
	{
		cout<<"没找到"<<endl;
	} 
	else
	{
		cout<<ret->_data<<" ";
		cout<<"找到了"<<endl;
	}
}

int main()
{
	TestBinaryTree();
	system("pause");
	return 0;
}