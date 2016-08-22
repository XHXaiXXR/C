#pragma once 
typedef int DataType;
struct LinkListNode
{
	LinkListNode(DataType data)
		:_data(data)
		,_next(NULL)
	{}
	DataType _data;
	LinkListNode* _next;
};

class LinkList
{
	friend ostream& operator<<(ostream& os,LinkList& list);
	typedef LinkListNode Node;
public:
	LinkList()
		:_head(NULL)
		,_tail(NULL)
	{}
	~LinkList()
	{
		Node* cur = _head;
		while (cur)
		{
			Node* tmp = cur;
			cur = cur->_next;
			delete tmp;
			tmp = NULL;
		}
	}
public:
	void PushBack(const DataType data)
	{
		if ((_head == NULL) && (_tail == NULL))
		{
			_head = new Node(data);
			_tail = _head;
		}
		else
		{
			Node* tmp = new Node(data);
			_tail->_next = tmp;
			_tail = _tail->_next;
		}
	}
	void PushFrond(const DataType data)
	{
		Node* cur = new Node(data);
		if ((_head == NULL) && (_tail == NULL))
		{
			_head = cur;
			_tail = _head;
		} 
		else
		{
			cur->_next = _head;
			_head = cur;
		}
	}
	void PopBack()
	{
		if ((_head == NULL) && (_tail == NULL))
		{
			cout<<"�����ѿ�"<<endl;
			return;
		} 
		else
		{
			Node* del = _head;
			Node* delprev = NULL;
			while (del != _tail)
			{
				delprev = del;
				del = del->_next;
			}
			_tail = delprev;
			_tail->_next = NULL;//βָ�����һ��λ��һ��Ҫ�ǵ��ÿգ���������ж�
			delete del;
			del = NULL;
		}
	}
	void PopFrond()
	{
		if ((_head == NULL) && (_tail == NULL))
		{
			cout<<"�����ѿ�"<<endl;
		} 
		else
		{
			Node* del = _head;
			_head = _head->_next;
			delete del;
			del = NULL;
		}
	}
	Node* Find(const DataType data)
	{
		if ((_head == NULL) && (_tail == NULL))
		{
			cout<<"List is Null"<<endl;
			return NULL;
		} 
		else
		{
			Node* cur = _head;
			while (cur)
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
		}
		return NULL;
	}
	//��ĳһ���ڵ�ĺ������һ���ڵ�
	void Insert(Node* cur,const DataType data)
	{
		Node* tmp = new Node(data);
		if (cur == NULL)
		{
			_head = tmp;
			_tail = _head;
		}
		//����ڵ���β�������
		if (cur == _tail)
		{
			cur->_next = tmp;
			_tail = tmp;
		} 
		else
		{
			tmp->_next = cur->_next;
			cur->_next = tmp;
		}
	}
	//ɾ����ǰ�ڵ�
	void Remove(Node* cur)
	{
		if (cur == NULL)
		{
			cout<<"no find"<<endl;
			return;
		}
		Node* tmp = _head;
		if (cur == _head)
		{
			Node* del = _head;
			_head = _head->_next;
			delete del;
			del = NULL;
		}
		else if (cur == _tail)
		{
			while (tmp->_next != cur)
			{
				tmp = tmp->_next;
			}
			_tail = tmp;
			_tail->_next = NULL;
			delete cur;
			cur = NULL;
		}
		else
		{
			//�ҵ�ɾ���ڵ��ǰһ��λ��
			while (tmp->_next == cur)
			{
				tmp = tmp->_next;
			}
			tmp->_next = cur->_next;
			delete cur;
			cur = NULL;
		}
	}
private:
	Node* _head;//ͷָ��
	Node* _tail;//βָ��
};

ostream& operator<<(ostream& os,LinkListNode& node)
{
	os<<node._data<<" ";
	return os;
}
ostream& operator<<(ostream& os,LinkList& list)
{
	LinkListNode* cur = list._head;
	while (cur)
	{
		os<<*cur<<" ";
		cur = cur->_next;
	}
	return os;
}