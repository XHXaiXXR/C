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

	//ͷɾ
	void PopFrond()
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
private:
	Node* _head;
	Node* _tail;
	int _size;
};