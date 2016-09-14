#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

template<class T>
struct ListNode
{
	ListNode<T>* _prev;
	ListNode<T>* _next;
	T _data;

	ListNode(const T& data)
		:_prev(NULL)
		,_next(NULL)
		,_data(data)
	{}
};

template<class T,class Ref,class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T,Ref,Ptr> Self;

	Node* _node;

	ListIterator(){}
	ListIterator(Node* node)
		:_node(node)
	{}

	bool operator==(const Self& s) const
	{
		return _node == s._node;
	}
	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}
	Self& operator++() 
	{
		_node = _node->_next;
		return *this;
	}
	Self operator++(int) 
	{
		Self tmp(_node);
		_node = _node->_next;
		return tmp;
	}
	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	Self operator--(int)
	{
		Self tmp(_node);
		_node = _node->_prev;
		return tmp;
	}

	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		return &(*_node->_data);
	}
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	typedef ListIterator<T,T&,T*> Iterator;
public:
	Node* BuyNode(const T& data)
	{
		Node* tmp = new Node(data);
		return tmp;
	}

	List()
	{
		_head = BuyNode(T());
		_head->_prev = _head;
		_head->_next = _head;
	}

	//void PushBack(const T& data)
	//{
	//	Node* tail = _head->_prev;
	//	Node* node = BuyNode(data);

	//	node->_prev = tail;
	//	node->_next = tail->_next;

	//	tail->_next = node;
	//	_head->_prev = node;
	//}

	void PushBack(const T& data)
	{
		Insert(End(),data);
	}
	void PushFront(const T& data)
	{
		Insert(Begin(),data);
	}
	//在指定位置前的一个位置插入
	void Insert(Iterator pos,const T& data)
	{
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* tmp = BuyNode(data);

		tmp->_prev = prev;
		tmp->_next = cur;

		prev->_next = tmp;
		cur->_prev = tmp;
	}
	void PopBack()
	{
		//Erase(Iterator(_head->_prev));
		Erase(--End());
	}
	void PopFront()
	{
		//Erase(Iterator(_head->_next));
		Erase(Begin());
	}
	//指定位置删除
	void Erase(Iterator pos)
	{
		Node* del = pos._node;
		Node* prev = del->_prev;
		Node* cur = del->_next;

		prev->_next = cur;
		cur->_prev = prev;

		delete del;
		del = NULL;
	}
	Iterator Begin()
	{
		return Iterator(_head->_next);
	}
	Iterator End()
	{
		return Iterator(_head);
	}
private:
	Node* _head;
};

void test()
{
	List<int> l;

	for(int i = 0;i < 5;i++)
	{
		l.PushBack(i);
	}
	for (int i = 5;i < 10;i++)
	{
		l.PushFront(i);
	}
	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;

	l.PopBack();
	l.PopBack();
	l.PopFront();
	l.PopFront();
	it = l.Begin();
	while (it != l.End())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}
int main()
{
	test();
	system("pause");
	return 0;
}