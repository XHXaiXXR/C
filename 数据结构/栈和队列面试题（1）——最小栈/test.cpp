#include<iostream>
using namespace std;
#include<stack>
#include<assert.h>

template<class T>
class Stack
{
public:
	Stack(){}

	void Push(const T& data)
	{
		if(MinStack.empty() || MinStack.top() >= data)
		{
			DataStack.push(data);
			MinStack.push(data);
		}
		else
		{
			DataStack.push(data);
		}		
	}
	void Pop()
	{
		if(MinStack.top() == DataStack.top())
		{
			DataStack.pop();
			MinStack.pop();
		}
		else
		{
			DataStack.pop();
		}
	}
	T& Min()
	{
		return MinStack.top();
	}
	size_t Size()
	{
		return DataStack.size();
	}
	bool Empty()
	{
		return DataStack.empty();
	}
	T& Top()
	{
		return DataStack.top();
	}
private:
	stack<T> DataStack;
	stack<T> MinStack;
};
void test()
{
	Stack<int> s;
	s.Push(3);
	s.Push(7);
	s.Push(2);
	s.Push(8);
	s.Push(1);
	s.Push(6);
	cout<<"Min = "<<s.Min()<<endl;
	cout<<"s.top() = "<<s.Top()<<endl;
	cout<<"size = "<<s.Size()<<endl;

	s.Pop();
	s.Pop();
	cout<<"Min = "<<s.Min()<<endl;
	cout<<"s.top() = "<<s.Top()<<endl;
	cout<<"size = "<<s.Size()<<endl;
}
int main()
{
	test();
	return 0;
}