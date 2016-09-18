#include<iostream>
using namespace std;
#include<stack>

template<class T>
class TwoStackFromQueue
{
public:
	TwoStackFromQueue(){}

	void Push(const T& data)
	{
		if(PushStack.empty())
		{
			if(!PopStack.empty())
			{
				while(!PopStack.empty())
				{
					PushStack.push(PopStack.top());
					PopStack.pop();
				}
				PushStack.push(data);
			}
			else
			{
				PushStack.push(data);
			}
		}
		else
		{
			PushStack.push(data);
		}
	}
	void Pop()
	{
		if(PopStack.empty())
		{
			if(!PushStack.empty())
			{
				while(!PushStack.empty())
				{
					PopStack.push(PushStack.top());
					PushStack.pop();
				}
				PopStack.pop();
			}
			else
			{
				PopStack.pop();
			}
		}
		else
		{
				PopStack.pop();
		}
	}
	T& Front()
	{
		if(!PopStack.empty())
		{
			return PopStack.top();
		}
		else
		{
			while(!PushStack.empty())
			{
				PopStack.push(PushStack.top());
				PushStack.pop();
			}
			return PopStack.top();
		}
	}
	T& Back()
	{
		if(!PushStack.empty())
		{
			return PushStack.top();
		}
		else
		{
			while(!PopStack.empty())
			{
				PushStack.push(PopStack.top());
				PopStack.pop();
			}
			return PushStack.top();
		}
	}
	size_t Size()
	{
		if(PushStack.empty())
		{
			return PopStack.size();
		}
		else
		{
			return PushStack.size();
		}
	}
	bool Empty()
	{
		if(PushStack.empty())
		{
			return PopStack.empty();
		}
		else
		{
			return PushStack.empty();
		}
	}
private:
	stack<T> PushStack;
	stack<T> PopStack;
};

void test()
{
	TwoStackFromQueue<int> q;
	q.Push(7);
	q.Push(3);
	q.Push(2);
	q.Push(4);
	q.Push(6);
	q.Push(9);
	q.Push(0);
	cout<<"end = "<<q.Back()<<endl;
	cout<<"begin = "<<q.Front()<<endl;
	cout<<"size = "<<q.Size()<<endl;
	
	cout<<endl;

	q.Pop();
	q.Pop();
	cout<<"end = "<<q.Back()<<endl;
	cout<<"begin = "<<q.Front()<<endl;
	cout<<"size = "<<q.Size()<<endl;
}


int main()
{
	test();
	return 0;
}