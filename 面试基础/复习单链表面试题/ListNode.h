#pragma once

#include <assert.h>

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
				_size--;

				if(_size == 0)
				{
					break;
				}

				cur = _head->_next;
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
	void PushFront(T data)
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
	void PopFront()
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

	//在pos位置前插入一个节点
	void Insert(Node* pos,T data)
	{
		Node* newNode = new Node(data);

		if (_head->_next == NULL)
		{
			cout<<"链表为空,没有pos节点"<<endl;
			return;
		} 
		else if(_head->_next == pos)
		{
			newNode->_next = pos;
			_head->_next = newNode;
		}
		else
		{
			Node* cur = _head->_next;

			while (cur->_next != pos && cur != _head)
			{
				cur = cur->_next;
			}
			
			if(cur == NULL || cur == _head)
			{
				cout<<"没有找到对应的位置"<<endl;
				return;
			}

			newNode->_next = pos;
			cur->_next = newNode;
		}

		_size++;
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

	//链表的冒泡排序
	void BubbingSortList(List<T>& l)
	{
		Node* cur = l._head->_next;

		for (int i = 0;i < _size - 1;i++)
		{
			for (int j = 0;j < _size - 1 - i;j++)
			{
				if (cur->_data > cur->_next->_data)
				{
					swap(cur->_data,cur->_next->_data);
				}
				cur = cur->_next;
			}
			cur = l._head->_next;
		}
	}

	//删除一个无头链表的非尾结点
	void EraseNotHead(Node* pos)
	{
		Node* del = pos->_next;
		pos->_data = del->_data;
		pos->_next = del->_next;

		delete del;
		del = NULL;

		_size--;
	}

	//逆置链表
	void ReverseList()
	{
		Node* newNode = NULL;
		Node* cur = NULL;
		Node* head = _head->_next;
		
		Node* newtail = head;
		while (head != _tail)
		{
			newNode = head;
			head = head->_next;
			newNode->_next = cur;
			cur = newNode;
		}

		head->_next = cur;
		_head->_next = head;
		_tail = newtail;
	}

	//(无头链表)在当前节点前插入一个节点
	void InsertFrontNode(Node* pos, T data)
	{
		Node* newNode = new Node(data);

		newNode->_next = pos->_next;
		pos->_next = newNode;
		swap(pos->_data, newNode->_data);

		_size++;
	}

	//只遍历一遍，找到链表的中间结点
	Node* FindMidNode()
	{
		Node* slowNode = _head->_next;
		Node* fastNode = _head->_next;

		while (fastNode->_next != NULL && fastNode->_next->_next != NULL)
		{
			slowNode = slowNode->_next;
			fastNode = fastNode->_next->_next;
		}

		return slowNode;
	}

	//删除倒数第K个节点
	void DelKNode(int K)
	{
		assert(K > 1 && K < _size);

		Node* KNode = _head->_next;
		Node* cur = _head->_next;
		Node* prev = NULL;

		while (--K)
		{
			KNode = KNode->_next;
		}

		while (KNode->_next != NULL)
		{
			prev = cur;
			cur = cur->_next;
			KNode = KNode->_next;
		}

		prev->_next = cur->_next;
		delete cur;
		cur = NULL;

		_size--;
	}

	//约瑟夫环问题
	Node* JosephCycle(int num)
	{
		Node* cur = _head->_next;
		Node* del = NULL;
		int k = 0;

		while (cur->_next != cur)
		{
			k = num;
			while(--k)
			{
				cur = cur->_next;
			}

			cout<<"删除节点为: "<<cur->_data<<endl;
			del = cur->_next;
			cur->_data = del->_data;
			cur->_next = del->_next;

			delete del;
			del = NULL;
		}

		_head->_next = cur;
		cur->_next = NULL;

		return cur;
	}

	//判断链表是否带环
	Node* CheckCycle()
	{
		Node* slowNode = _head->_next;
		Node* fastNode = _head->_next;

		while (fastNode && fastNode->_next)
		{
			slowNode = slowNode->_next;
			fastNode = fastNode->_next->_next;

			if (slowNode == fastNode)
			{
				return fastNode;
			}
		}

		return NULL;
	}

	//求环的长度
	int GetCycleLenght(Node* meet)
	{
		Node* cur = meet;
		Node* newcur = cur;

		int count = 1;
		do 
		{
			++count;
			cur = cur->_next;
		} while (cur->_next != newcur);

		return count;
	}

	//求环的入口
	Node* GetCycleEntryNode(Node* meet)
	{
		Node* cur = _head->_next;
		
		while (cur != meet)
		{
			cur = cur->_next;
			meet = meet->_next;
		}

		return cur;
	}

	//判断两个链表是否相交
	bool CheckCroo(List<T> l2)
	{
		//两个量表中只要其中一个链表带环，那么两条链表绝对不可能相交
		if (CheckCycle() || l2.CheckCycle())
		{
			return false;
		}

		Node* node1 = _head->_next;
		Node* node2 = l2._head->_next;

		while (node1->_next)
		{
			node1 = node1->_next;
		}
		while (node2->_next)
		{
			node2 = node2->_next;
		}

		if (node1 == node2)
		{
			return true;
		}

		return false;
	}
private:
	Node* _head;
	Node* _tail;
	int _size;
};