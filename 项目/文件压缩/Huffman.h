#pragma once
#include <iostream>
using namespace std;
#include "Heap.h"
#include <assert.h>

template<class T>
struct HuffmanTreeNode
{
	T _weight;//Ȩ��
	HuffmanTreeNode<T>* _left;//ָ����������ָ��
	HuffmanTreeNode<T>* _right;//ָ����������ָ��
	
	HuffmanTreeNode(const T& weight = T())
		:_weight(weight)
		,_left(NULL)
		,_right(NULL)
	{}
};//���HuffmanTree�ڵ�����ݽṹ

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	//���캯��
	HuffmanTree()
		:_root(NULL)
	{}
	//���캯��
	//����huffmanTree
	HuffmanTree(T* arr, size_t size, const T& invalid = T())
	{
		//ÿ�ζ�ѡȡ��С�������ڵ㣬����С����Ϊ����
		struct Less
		{
			bool operator()(Node* left, Node* right)
			{
				assert(left);
				assert(right);

				return left->_weight < right->_weight;
			}
		};

		//���������ݽ�������С�ѣ����е�ÿ��Ԫ�ص����Ͷ���Node*������Ϊ�˱������ĸ��ڵ�
		Heap<Node*, Less> MinHeap;//С��
		for (size_t i = 0;i < size;i++)
		{
			//����ַ����ֵĴ�����Ϊ0����ô�ͽ���������С����
			if (arr[i]._count != invalid._count)
			{
				Node* node = new Node(arr[i]);
				MinHeap.Push(node);
			}
		}

		//����Huffman�㷨���Ӷ���ȡ��������С�Ľڵ㹹���µĸ��ڵ㣬����С���н��������ڵ�ɾ�����ٰ��¹����ĸ��ڵ����С���м����ظ��˲���
		Node* frist = NULL;
		Node* second = NULL;
		Node* parent = NULL;
		while (MinHeap.Size() > 1)
		{
			//ѡȡ������С�Ľڵ�
			frist = MinHeap.Top();
			MinHeap.Pop();
			second = MinHeap.Top();
			MinHeap.Pop();

			//��������С�ڵ㹹�����ڵ�
			parent = new Node(frist->_weight + second->_weight);

			//ָ��ָ��Ҫ��ȷ
			parent->_left = frist;
			parent->_right = second;

			MinHeap.Push(parent);
		}

		//С����������һ���ڵ����HuffmanTree�ĸ��ڵ�
		_root = MinHeap.Top();
	}
	//��������
	~HuffmanTree()
	{
		if (_root != NULL)
		{
			//���ٺ���
			_Destory(_root);
		}
	}
public:
	//��ȡhuffmanTree
	Node* GetRoot()
	{
		return _root;
	}
protected:
	void _Destory(Node* root)
	{
		if (NULL == root)
		{
			return;
		}

		_Destory(root->_left);
		_Destory(root->_right);
		delete root;
		root = NULL;
	}
private:
	Node* _root;
};//����huffmanTree�����ݽṹ

