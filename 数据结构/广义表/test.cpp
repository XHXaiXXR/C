#include<iostream>
using namespace std;
#include<assert.h>

enum Type
{
	HEAD,
	SUB,
	VALUE,
};

struct GeneralizedListNode
{
	Type _type;
	GeneralizedListNode* _next;
	//union
	//{
		char _value;
		GeneralizedListNode* _sublist;
	//}

	GeneralizedListNode(Type type,char value = 0)
		:_type(type)
		,_next(NULL)
	{
		if(type == VALUE)
		{
			_value = value;
		}
		else
		{
			_sublist = NULL;
		}
	}
};

class GeneralizedList
{
	typedef GeneralizedListNode Node;
public:
	GeneralizedList(){}
	GeneralizedList(char* str)
	{
		_head = _GreateList(str);
	}
	GeneralizedList(const GeneralizedList& g)
	{
		_head = _Copy(g._head);
	}
	~GeneralizedList()
	{
		_Dostory(_head);
	}
	
	GeneralizedList& operator=(GeneralizedList& g)
	{
		if(this != &g)
		{
			Node* head = _Copy(g._head);
			_Dostory(g._head);
			_head = head;
		}
		return *this;
	}
	void Print()
	{
		_Print(_head);
		cout<<endl;
	}
	size_t Size()
	{
		return _Size(_head);
	}
	size_t Depth()
	{
		return _Depth(_head);
	}
	

private:
	void _Dostory(Node* head)
	{
		Node* cur = head;

		while(cur)
		{
			Node* del = cur;
			cur = cur->_next;

			if(del->_type == SUB)
			{
				_Dostory(del->_sublist);
			}

			delete del;
		}
	}
	Node* _Copy(Node* head)
	{
		assert(head);
		Node* newhead = new Node(*head);
		Node* cur = head;
		cur = cur->_next;
		Node* newcur = newhead;

		while(cur)
		{
			Node* tmp = new Node(*cur);
			if(cur->_type == SUB)
			{
				tmp->_sublist = _Copy(cur->_sublist);
			}

			newcur->_next = tmp;
			newcur = newcur->_next;

			cur = cur->_next;
		}

		return newhead;
	}
	size_t _Depth(Node* head)
	{
		size_t MaxDepth = 1;
		Node* cur = head;

		while(cur)
		{
			if(cur->_type == SUB)
			{
				size_t depth = _Depth(cur->_sublist) + 1;//nowdepth
				if(MaxDepth < depth)
				{
					MaxDepth = depth;
				}
			}
			cur = cur->_next;
		}
		return MaxDepth;
	}
	size_t _Size(Node* head)
	{
		assert(head);

		size_t count = 0;
		Node* cur = head;

		while(cur)
		{
			if(cur->_type == VALUE)
			{
				count++;
			}
			else if(cur->_type == SUB)
			{
				count += _Size(cur->_sublist);
			}
			cur = cur->_next;
		}
		return count;
	}
	void _Print(Node* head)
	{
		assert(head);
		Node* cur = head;

		while(cur)
		{
			if(cur->_type == HEAD)
			{
				cout<<'(';
			}
			else if(cur->_type == VALUE)
			{
				cout<<cur->_value;
				if(cur->_next)
				{
					cout<<",";
				}
			}
			else//sub
			{
				_Print(cur->_sublist);
				if(cur->_next)
				{
					cout<<",";
				}
			}
			cur = cur->_next;
		}
		cout<<")";
	}
 	bool _IsValue(char c)
	{
		if((c >= 'a' && c <= 'z')\
			|| (c >= 'A' && c <= 'Z')\
			|| (c >= '0' && c <= '9'))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Node* _GreateList(char*& str)
	{
		assert(*str == '(');
		++str;
		Node* head = new Node(HEAD);
		Node* prev = head;

		while(*str)
		{
			if(*str == '(')
			{
				//sub
				Node* sub = new Node(SUB);
				sub->_sublist = _GreateList(str);
				prev->_next = sub;
				prev = prev->_next;
			}
			else if(*str == ')')
			{
				//end
				++str;
				prev->_next = NULL;
				return head;
			}
			else if(_IsValue(*str))
			{
				Node* valuenode = new Node(VALUE,*str);
				prev->_next = valuenode;
				prev = prev->_next;
				++str;
			}
			else
			{
				++str;
			}
		}
		return head;
	}
private:
	Node* _head;
};
void test()
{
	char arr1[] = "(2,(0,(5,4,3)),7)";
	GeneralizedList g(arr1);
	g.Print();
	cout<<"size = "<<g.Size()<<endl;
	cout<<"Depth = "<<g.Depth()<<endl;
	
	GeneralizedList g2(g);
	g2.Print();
	
	GeneralizedList g3;
	g3 = g2;
	g3.Print();
}
int main()
{
	test();
	return 0;
}