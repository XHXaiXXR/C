#include<iostream>
using namespace std;
#include<stack>

struct ListNode
{
	int _data;
	ListNode* _next;

	ListNode(int data)
		:_data(data)
		,_next(NULL)
	{}
};

class List
{
	typedef ListNode Node;
public:
	List()
		:_head(NULL)
	{}
	
	void PushBack(int data)
	{
		if(_head == NULL)
		{
			_head = _BuyNode(data);
		}
		else
		{
			Node* cur = _head;
			while(cur->_next)
			{
				cur = cur->_next;
			}
			Node* node = _BuyNode(data);
			cur->_next = node;
		}
	}
	void Display()
	{
		Node* cur = _head;
		while(cur->_next)
		{
			cout<<cur->_data<<"->";
			cur = cur->_next;
		}
		cout<<cur->_data<<"->NULL"<<endl;
	}
	
	Node* AddTwoNumList(const List& l1,const List& l2)
	{
		stack<int> sd;//辅助栈 stackdata
		stack<int> sc;//进位栈 stackcarry
		int carry = 0;
		int data = 0;
		sc.push(carry);

		if(l1._head == NULL && l2._head == NULL)
		{
			return NULL;
		}
		if(l1._head == NULL)
		{
			return l2._head;
		}
		if(l2._head == NULL)
		{
			return l1._head;
		}
		
		Node* newl1 = l1._head;
		Node* newl2 = l2._head;
		while(newl1 && newl2)
		{
			sd.push(newl1->_data);
			sd.push(newl2->_data);
			
			carry = 0;
			carry = sc.top();
			sc.pop();
			data = 0;
			while(!sd.empty())
			{
				data += sd.top();
				sd.pop();
			}
			data += carry;

			carry = data / 10;
			sc.push(carry);

			data = data % 10;
			Node* tmp = _BuyNode(data);
			_PushBack(tmp);

			newl1 = newl1->_next;
			newl2 = newl2->_next;
		}	

		//l1或l2剩余的链表节点直接链接
		while(newl1)
		{
			data = newl1->_data + sc.top();
			sc.pop();
			carry = data / 10;
			sc.push(carry);
			data %= 10;
			Node* tmp = _BuyNode(data);
			_PushBack(tmp);
			newl1 = newl1->_next;
		}
		while(newl2)
		{
			data = newl2->_data + sc.top();
			sc.pop();
			carry = data / 10;
			sc.push(carry);
			data %= 10;
			Node* tmp = _BuyNode(data);
			_PushBack(tmp);
			newl2 = newl2->_next;
		}

		//进位栈里的最后一个进位不为0
		if(sc.top() != 0)
		{
			data = sc.top();
			sc.pop();
			Node* tmp = _BuyNode(data);
			_PushBack(tmp);
		}
	}
private:
	void _PushBack(Node* tmp)
	{
		if(_head == NULL)
		{
			_head = tmp;
		}
		else
		{
			Node* cur = _head;
			while(cur->_next)
			{
				cur = cur->_next;
			}
			cur->_next = tmp;
		}
	}
	Node* _BuyNode(int data)
	{
		Node* node = new Node(data);
		return node;
	}
private:
	Node* _head;
};

void test()
{
	List l1;
	l1.PushBack(2);
	l1.PushBack(4);
	l1.PushBack(3);
	l1.PushBack(18);
	l1.Display();

	List l2;
	l2.PushBack(5);
	l2.PushBack(6);
	l2.PushBack(4);
	l2.Display();

	List l3;
	l3.AddTwoNumList(l1,l2);
	l3.Display();
}
int main()
{
	test();
	return 0;
}