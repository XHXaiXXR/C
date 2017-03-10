#pragma once

template<class T>
struct ListNode
{
	T _data;
	ListNode* _next;

	ListNode(T data)
		:_data(data)
		,_next(NULL)
	{}
};

template<class T>
class List
{
	typedef ListNode<T> Node;
public:
	//构造函数
	List()
		:_head(new Node(0))
		,_tail(NULL)
		,_size(0)
	{}

	//析构函数
	~List()
	{
		Destroy();
	}

	void Destroy()
	{
		if (_head != NULL)
		{
			Node* cur = _head->_next;

			while (cur && cur != _head)
			{
				Node* del = cur;
				_head->_next = cur->_next;
				delete del;
				del = NULL;

				cur = _head->_next;
				_size--;
			}

			delete _head;
			_head = NULL;
		}
	}

	void PrintList()
	{
		if (_head == NULL)
		{
			cout<<"链表已经为空"<<endl;
		} 
		else
		{
			Node* cur = _head->_next;

			while(cur && cur != _head)
			{
				cout<<cur->_data<<" ";
				cur = cur->_next;
			}
			cout<<endl;
		}
	}
	//尾插法
	void PushBack(T data)
	{
		Node* cur = new Node(data);
		
		if (_head->_next == NULL)
		{
			_head->_next = cur;
			_tail = cur;
		} 
		else
		{
			_tail->_next = cur;
			_tail = cur;
		}
		_size++;
	}

	//尾删法
	void PopBack()
	{
		Node* cur = _head->_next;

		if (cur == NULL)
		{
			cout<<"链表已经为空"<<endl;
			return;
		} 
		else if (cur == _tail)
		{
			delete _tail;
			_tail = NULL;
			_head->_next = NULL;
		}
		else
		{
			while (cur->_next != _tail)
			{
				cur = cur->_next;
			}

			delete _tail;
			_tail = cur;
			_tail->_next = NULL;
		}
		_size--;
	}

	//头插法
	void PushFrond(T data)
	{
		Node* cur = new Node(data);
		if (_head->_next == NULL)
		{
			_head->_next = cur;
			_tail = cur;
		} 
		else
		{
			cur->_next = _head->_next;
			_head->_next = cur;
		}
		_size++;
	}

	//头删
	void PopFrond()
	{
		if (_head->_next == NULL)
		{
			cout<<"链表已经为空"<<endl;
		} 
		else if (_head->_next == _tail)
		{
			delete _tail;
			_tail = NULL;
			_head->_next = NULL;
		}
		else
		{
			Node* del = _head->_next;
			_head->_next = del->_next;

			delete del;
			del = NULL;
		}
		_size--;
	}
	//在链表中查找元素data
	Node* FindNode(T data)
	{
		if (_head->_next == NULL)
		{
			cout<<"该链表中没有数据"<<endl;
		} 
		else
		{
			Node* cur = _head->_next;

			while (cur && cur != _head)
			{
				if (cur->_data == data)
				{
					return cur;
				} 
				else
				{
					cur = cur->_next;
				}
			}

			return NULL;
		}
	}

	//删除pos位置的节点
	void Erase(Node* pos)
	{
		if (_head->_next == NULL)
		{
			cout<<"该链表中已经没有数据"<<endl;
		} 
		else
		{
			//删除的节点是第一个节点
			if (_head->_next == pos)
			{
				_head->_next = pos->_next;
				delete pos;
				pos = NULL;
			}
			//删除的节点是最后一个节点
			else if (_tail == pos)
			{
				Node* cur = _head->_next;

				while (cur->_next != _tail)
				{
					cur = cur->_next;
				}

				delete _tail;
				_tail = cur;
				_tail->_next = NULL;
			}
			//删除的节点既不是头结点，也不是尾结点
			else
			{
				Node* cur = _head->_next;

				while (cur && cur->_next != pos && cur != _head)
				{
					cur = cur->_next;
				}

				//出了while循环有可能是遍历了一遍链表都没有找到，我们要解决这种问题
				if (cur == NULL)
				{
					cout<<"找不到你所要删除的节点"<<endl;
					return;
				}

				//开始删除
				cur->_next = pos->_next;
				delete pos;
				pos = NULL;
			}
			_size--;
		}
	}

	size_t SizeNode()
	{
		return _size;
	}
private:
	Node* _head;
	Node* _tail;
	int _size;
};