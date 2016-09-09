#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<assert.h>

template<class T>
struct QueueNode
{
	T _data;
	QueueNode<T>* _next;

	QueueNode(const T& data)
		:_data(data)
		,_next(NULL)
	{}
};

template<class T>
class Queue
{
	typedef QueueNode<T> Node;
public:
	Queue()
		:_head(NULL)
		,_tail(NULL)
		,_size(0)
	{}
	void Push(const T& data)
	{
		if(_head == NULL)
		{
			_head = _tail = new Node(data);
		}
		else
		{
			_tail->_next = new Node(data);
			_tail = _tail->_next;
		}
		_size++;
	}
	void Pop()
	{
		assert(_head);
		if(_size == 1)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		else
		{
			Node* del = _head;
			_head = _head->_next;
			delete del;
			del = NULL;
		}
		_size--;
		//	
		//	Node* del = _head;
		//	_head = _head->_next;
		//	delete del;
		//	del = NULL;
		//	_size--;
	}
	bool Empty()
	{
		return _size == 0;
	}
	size_t Size()
	{
		return _size;
	}
	T& Front()
	{
		return _head->_data;
	}
	T& Back()
	{
		return _tail->_data;
	}
private:
	Node* _head;
	Node* _tail;
	size_t _size;
};

void test()
{
	Queue<int> q;
	for(int i = 1;i <= 5;i++)
	{
		q.Push(i);
	}
	cout<<"size = "<<q.Size()<<endl;

	while(!q.Empty())
	{
		cout<<q.Front()<<" ";
		q.Pop();
	}
	cout<<endl;
	cout<<"size = "<<q.Size()<<endl;

}

int main()
{
	test();
	system("pause");
	return 0;
}