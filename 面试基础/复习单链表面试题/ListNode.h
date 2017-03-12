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
	//���캯��
	List()
		:_head(new Node(0))
		,_tail(NULL)
		,_size(0)
	{}

	//��������
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
			cout<<"�����Ѿ�Ϊ��"<<endl;
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
	//β�巨
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

	//βɾ��
	void PopBack()
	{
		Node* cur = _head->_next;

		if (cur == NULL)
		{
			cout<<"�����Ѿ�Ϊ��"<<endl;
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

	//ͷ�巨
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

	//ͷɾ
	void PopFront()
	{
		if (_head->_next == NULL)
		{
			cout<<"�����Ѿ�Ϊ��"<<endl;
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
	//�������в���Ԫ��data
	Node* FindNode(T data)
	{
		if (_head->_next == NULL)
		{
			cout<<"��������û������"<<endl;
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

	//��posλ��ǰ����һ���ڵ�
	void Insert(Node* pos,T data)
	{
		Node* newNode = new Node(data);

		if (_head->_next == NULL)
		{
			cout<<"����Ϊ��,û��pos�ڵ�"<<endl;
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
				cout<<"û���ҵ���Ӧ��λ��"<<endl;
				return;
			}

			newNode->_next = pos;
			cur->_next = newNode;
		}

		_size++;
	}

	//ɾ��posλ�õĽڵ�
	void Erase(Node* pos)
	{
		if (_head->_next == NULL)
		{
			cout<<"���������Ѿ�û������"<<endl;
		} 
		else
		{
			//ɾ���Ľڵ��ǵ�һ���ڵ�
			if (_head->_next == pos)
			{
				_head->_next = pos->_next;
				delete pos;
				pos = NULL;
			}
			//ɾ���Ľڵ������һ���ڵ�
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
			//ɾ���Ľڵ�Ȳ���ͷ��㣬Ҳ����β���
			else
			{
				Node* cur = _head->_next;

				while (cur && cur->_next != pos && cur != _head)
				{
					cur = cur->_next;
				}

				//����whileѭ���п����Ǳ�����һ������û���ҵ�������Ҫ�����������
				if (cur == NULL)
				{
					cout<<"�Ҳ�������Ҫɾ���Ľڵ�"<<endl;
					return;
				}

				//��ʼɾ��
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

	//�����ð������
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

	//ɾ��һ����ͷ����ķ�β���
	void EraseNotHead(Node* pos)
	{
		Node* del = pos->_next;
		pos->_data = del->_data;
		pos->_next = del->_next;

		delete del;
		del = NULL;

		_size--;
	}

	//��������
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

	//(��ͷ����)�ڵ�ǰ�ڵ�ǰ����һ���ڵ�
	void InsertFrontNode(Node* pos, T data)
	{
		Node* newNode = new Node(data);

		newNode->_next = pos->_next;
		pos->_next = newNode;
		swap(pos->_data, newNode->_data);

		_size++;
	}

	//ֻ����һ�飬�ҵ�������м���
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

	//ɾ��������K���ڵ�
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

	//Լɪ������
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

			cout<<"ɾ���ڵ�Ϊ: "<<cur->_data<<endl;
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

	//�ж������Ƿ����
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

	//�󻷵ĳ���
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

	//�󻷵����
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

	//�ж����������Ƿ��ཻ
	bool CheckCroo(List<T> l2)
	{
		//����������ֻҪ����һ�������������ô����������Բ������ཻ
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