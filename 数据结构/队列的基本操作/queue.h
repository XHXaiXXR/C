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
	Queue()//���캯��
		:_head(NULL)
		,_tail(NULL)
		,_size(0)
	{}

	~Queue()//��������
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

	void Push(const T& data)//���
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

	void Pop()//����
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

	void PrintQueue()//��ӡ����
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

	T& Front()//���ض��еĶ�ͷԪ��
	{
		//assert(_head);
		return _head->_data;
	}

	T& Back()//���ض��еĶ�βԪ��
	{
		//assert(_tail);
		return _tail->_data;
	}

protected:
	bool Empty()//�ж϶����Ƿ�Ϊ��
	{
		return _size == 0;
	}

	size_t Size()//���еĳ���
	{
		return _size;
	}

private:
	Node<T>* _head;//��ͷָ��
	Node<T>* _tail;//��βָ��
	size_t _size;//���г���
};

