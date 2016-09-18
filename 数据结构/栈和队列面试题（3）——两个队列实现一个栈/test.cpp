#include<iostream>
using namespace std;
#include<queue>

template<class T>
class TwoQueueFromStack
{
public:
	TwoQueueFromStack(){}

	void Push(const T& data)
	{
		if(FirstQueue.empty())
		{
			ScondQueue.push(data);
		}
		else
		{
			FirstQueue.push(data);
		}
	}
	void Pop()
	{
		if(FirstQueue.empty())
		{
			while(ScondQueue.size() != 1)
			{
				FirstQueue.push(ScondQueue.front());
				ScondQueue.pop();
			}
			ScondQueue.pop();
		}
		else
		{
			while(FirstQueue.size() != 1)
			{
				ScondQueue.push(FirstQueue.front());
				FirstQueue.pop();
			}
			FirstQueue.pop();
		}
	}
	T& Top()
	{
		if(FirstQueue.empty())
		{
			return ScondQueue.back(); 
		}
		else
		{
			return FirstQueue.back();
		}
	}
	size_t Size()
	{
		if(FirstQueue.empty())
		{
			return ScondQueue.size();
		}
		else
		{
			return FirstQueue.size();
		}
	}
	bool Empty()
	{
		return FirstQueue.empty() && ScondQueue.empty();
	}
private:
	queue<T> FirstQueue;
	queue<T> ScondQueue;
};

void test()
{
	TwoQueueFromStack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	cout<<"top = "<<s.Top()<<endl;
	cout<<"size = "<<s.Size()<<endl;
	cout<<"empty = "<<s.Empty()<<endl;

	s.Pop();
	s.Pop();
	s.Pop();
	cout<<"top = "<<s.Top()<<endl;
	cout<<"size = "<<s.Size()<<endl;
	cout<<"empty = "<<s.Empty()<<endl;

	s.Pop();
	s.Pop();
	s.Pop();
	cout<<"empty = "<<s.Empty()<<endl;
}
int main()
{
	test();
	return 0;
}