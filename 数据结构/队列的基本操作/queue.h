#pragma once
#include <iostream>
using namespace std;
#include "assert.h"

typedef int DataType;

template<class T>
struct Node
{
	DataType _data;
	struct Node<T>* _next;

	Node(const T& data)
		:_data(data)
		,_next(NULL)
	{}
};

template<class T>
class Queue
{
public:
	Queue()//构造函数
		:_head(NULL)
		,_tail(NULL)
		,_size(0)
	{}

	~Queue()//析构函数
	{
		if (_head)
		{
			delete _head;
		}
		if (_tail)
		{
			delete _tail;
		}
	}

	void Push(const T& data)//入队
	{
		if (_head == NULL)
		{
			_head = _tail = new Node<T> (data);
		} 
		else
		{
			_tail->_next = new Node<T> (data);
			_tail = _tail->_next;
		}
		++_size;
	}

	void Pop()//出队
	{
		if (Empty() == true)
		{
			printf("Queue is Empty\n");
			return;
		} 
		else
		{
			Node<T>* del = _head;
			_head = _head->_next;
			delete del;
		}
		--_size;
	}

	void PrintQueue()//打印队列
	{
		if (Empty() == true)
		{
			return;
		}
		Node<T>* pNode = NULL;
		pNode = _head;

		while(pNode != _tail)
		{
			cout<<pNode->_data<<" ";
			pNode = pNode->_next;
		}
		cout<<pNode->_data<<endl;
	}

	T& Front()//返回队列的对头元素
	{
		//assert(_head);
		return _head->_data;
	}

	T& Back()//返回队列的队尾元素
	{
		//assert(_tail);
		return _tail->_data;
	}

protected:
	bool Empty()//判断队列是否为空
	{
		return _size == 0;
	}

	size_t Size()//队列的长度
	{
		return _size;
	}

private:
	Node<T>* _head;//队头指针
	Node<T>* _tail;//队尾指针
	size_t _size;//队列长度
};

