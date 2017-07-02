#pragma once
#include <iostream>
using namespace std;
#include "Heap.h"
#include <assert.h>

template<class T>
struct HuffmanTreeNode
{
	T _weight;//权重
	HuffmanTreeNode<T>* _left;//指向左子树的指针
	HuffmanTreeNode<T>* _right;//指向右子树的指针
	
	HuffmanTreeNode(const T& weight = T())
		:_weight(weight)
		,_left(NULL)
		,_right(NULL)
	{}
};//存放HuffmanTree节点的数据结构

template<class T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	//构造函数
	HuffmanTree()
		:_root(NULL)
	{}
	//构造函数
	//构建huffmanTree
	HuffmanTree(T* arr, size_t size, const T& invalid = T())
	{
		//每次都选取最小的两个节点，用最小堆最为合适
		struct Less
		{
			bool operator()(Node* left, Node* right)
			{
				assert(left);
				assert(right);

				return left->_weight < right->_weight;
			}
		};

		//将这组数据建立成最小堆，堆中的每个元素的类型都是Node*，这是为了保存后面的父节点
		Heap<Node*, Less> MinHeap;//小堆
		for (size_t i = 0;i < size;i++)
		{
			//如果字符出现的次数不为0，那么就将他加入最小堆中
			if (arr[i]._count != invalid._count)
			{
				Node* node = new Node(arr[i]);
				MinHeap.Push(node);
			}
		}

		//运用Huffman算法，从堆中取出两个最小的节点构建新的父节点，并在小堆中将这两个节点删除，再把新构建的父节点插入小堆中继续重复此步骤
		Node* frist = NULL;
		Node* second = NULL;
		Node* parent = NULL;
		while (MinHeap.Size() > 1)
		{
			//选取两个最小的节点
			frist = MinHeap.Top();
			MinHeap.Pop();
			second = MinHeap.Top();
			MinHeap.Pop();

			//利用两个小节点构建父节点
			parent = new Node(frist->_weight + second->_weight);

			//指针指向要明确
			parent->_left = frist;
			parent->_right = second;

			MinHeap.Push(parent);
		}

		//小堆里面的最后一个节点就是HuffmanTree的根节点
		_root = MinHeap.Top();
	}
	//析构函数
	~HuffmanTree()
	{
		if (_root != NULL)
		{
			//销毁函数
			_Destory(_root);
		}
	}
public:
	//获取huffmanTree
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
};//构件huffmanTree的数据结构

