#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

#include <stack>
#include <queue>

template<class T>
class TwoStack
{
public:
	void Push(const T& data)
	{
		if (MinDataStack.empty()==true || MinDataStack.top() > data)
		{
			MinDataStack.push(data);
			DataStack.push(data);
		} 
		else
		{
			DataStack.push(data);
		}
	}

	void Pop()
	{
		assert(!DataStack.empty());
		if (MinDataStack.top() == DataStack.top())
		{
			MinDataStack.pop();
			DataStack.pop();
		} 
		else
		{
			DataStack.pop();
		}
	}

	T& MinData()
	{
		assert(!DataStack.empty());
		return MinDataStack.top();
	}

	T& Top()
	{
		assert(!DataStack.empty());
		return DataStack.top();
	}

	bool Empty()
	{
		return DataStack.empty();
	}

	size_t Size()
	{
		return DataStack.size();
	}


private:
	stack<T> DataStack;
	stack<T> MinDataStack;
};



template<class T>
class TwoStackForQueue
{
public:
	void Push(const T& data)
	{
		InStack.push(data);
	}

	void Pop()
	{
		assert(InStack.empty() == false || OutStack.empty() == false);//如果全为空，那么则是空队列，不进行操作
		while (InStack.empty() == false)
		{
			OutStack.push(InStack.top());
			InStack.pop();
		}
		OutStack.pop();
	}

	T& Front()
	{
		assert(InStack.empty() == false || OutStack.empty() == false);//如果全为空，那么则是空队列，不进行操作
		while (InStack.empty() == false)
		{
			OutStack.push(InStack.top());
			InStack.pop();
		}
		return OutStack.top();
	}

	T& Back()
	{
		assert(InStack.empty() == false || OutStack.empty() == false);//如果全为空，那么则是空队列，不进行操作
		while(OutStack.empty() == false)
		{
			InStack.push(OutStack.top());
			OutStack.pop();
		}
		return InStack.top();
	}

	bool Empty()
	{
		return (InStack.empty() == true && OutStack.empty() == true);
	}

	size_t Size()
	{
		return InStack.size()+OutStack.size();
	}
	//友元函数
	template<typename T>
	friend ostream& operator<<(ostream& os, const TwoStackForQueue<T>& queue);
private:
	stack<T> InStack;
	stack<T> OutStack;
};

//输出运算符重载
template<class T>
ostream& operator<<(ostream& os,const TwoStackForQueue<T>& queue)
{
	TwoStackForQueue<T> coutqueue(queue);

	while(coutqueue.OutStack.size() > 0)
	{
		os<<coutqueue.OutStack.top()<<" ";
		coutqueue.OutStack.pop();
	}
	while (coutqueue.InStack.size() > 0)
	{
		coutqueue.OutStack.push(coutqueue.InStack.top());
		coutqueue.InStack.pop();
	}
	while(coutqueue.OutStack.size() > 0)
	{
		os<<coutqueue.OutStack.top()<<" ";
		coutqueue.OutStack.pop();
	}
	return os;
}


template<class T>
class TwoQueueForStack
{
public:
	void Push(const T& data)
	{
		//每次push数据，总能保证一个队列为空
		if (_Queue2.empty() == true)
		{
			_Queue1.push(data);
		} 
		else//_Queue1.empty() == true
		{
			_Queue2.push(data);
		}
	}

	void pop()
	{
		assert(_Queue1.empty() == false || _Queue2.empty() == false);
		if (_Queue1.empty() == false)
		{
			while (_Queue1.front() != _Queue1.back())
			{
				_Queue2.push(_Queue1.front());
				_Queue1.pop();
			}
			_Queue1.pop();
		} 
		else//_Queue2.empty() == false
		{
			while (_Queue2.front() != _Queue2.back())
			{
				_Queue1.push(_Queue2.front());
				_Queue2.pop();
			}
			_Queue2.pop();
		}
	}

	T& Top()
	{
		assert(_Queue1.empty() == false || _Queue2.empty() == false);
		if (_Queue1.empty() == false)
		{
			return _Queue1.back();
		} 
		else
		{
			return _Queue2.back();
		}
	}

	bool Empty()
	{
		return _Queue1.empty() == true && _Queue2.empty() == true;
	}

	size_t Size()
	{
		return _Queue1.size()+_Queue2.size();
	}

	//template<typename T>
	//friend ostream& operator<<(ostream& os,const TwoQueueForStack<T>& stack);
private:
	queue<T> _Queue1;
	queue<T> _Queue2;
};

//template<class T>
//ostream& operator<<(ostream& os,const TwoQueueForStack<T>& stack)
//{
//	TwoQueueForStack<T> countstack(stack);
//
//	while (countstack._Queue1.size() > 0)
//	{
//		cout<<countstack._Queue1.front()<<" ";
//		countstack._Queue1.pop();
//	}
//
//	while (countstack._Queue2.size() > 0)
//	{
//		count<<countstack._Queue2.front()<<" ";
//		countstack._Queue2.pop();
//	}
//
//	while (countstack._Queue1.size() > 0)
//	{
//		cout<<countstack._Queue1.front()<<" ";
//		countstack._Queue1.pop();
//	}
//	return os;
//}

template<class T>
class LegalCheck
{
public:
	bool IsLegalCheck(T* array1,T* array2,size_t size1,size_t size2)
	{
		assert(array1);
		assert(array2);
		size_t j = 0;
		if (size1 != size2)
		{
			return false;
		} 
		else
		{
			for (size_t i = 0;i < size1; ++i)
			{
				_instack.push(array1[i]);
				if (_instack.top() == array2[j])
				{
					_instack.pop();
					j++;
					while (_instack.empty() == false && _instack.top() == array2[j])
					{
						_instack.pop();
						j++;
					}
				}
			}

			while (_instack.empty() == false)
			{
				if (_instack.top() == array2[j])
				{
					_instack.pop();
					j++;
				}
				else
				{
					return false;
				}
			}

			if (j == size1)
			{
				return true;
			} 
			else
			{
				return false;
			}
		}
	}
private:
	stack<T> _instack;
};



template<class T>
class ArrayForTwoStack
{
public:
	ArrayForTwoStack()
		:_array(NULL)
		,_capacity(0)
		,top1(-2)
		,top2(-1)
	{}

	ArrayForTwoStack(const ArrayForTwoStack& stack)
	{
		_array = new T[stack._capacity];
		_capacity = stack._capacity;
		top1 = stack.top1;
		top2 = stack.top2;
		int count = top1 > top2 ? top1 : top2;

		for (size_t index = 0;index < count; ++index)
		{
			_array[index] = stack._array[index];
		}
	}

	~ArrayForTwoStack()
	{
		if (_array)
		{
			delete[] _array;
			_array = NULL;
		}
	}

	void Push(size_t flag,const T& data)
	{
		CheckCapacity();
		//用flag来判断是哪一个栈中存放数据
		if (flag == 1)//flag为1时，下标为偶数存放栈1的数据
		{
			top1 += 2;
			_array[top1] = data;
		} 
		else//当flag不为1时，下标为奇数存放栈2的数据
		{
			top2 += 2;
			_array[top2] = data;
		}
	}

	void Pop(size_t flag)
	{
		if (flag == 1)
		{
			assert(top1 != -2);
			top1 -= 2;
		} 
		else
		{
			assert(top2 != -1);
			top2 -= 2;
		}
	}

	T& Top(size_t flag)
	{
		if (flag == 1)
		{
			assert(top1 != -2);
			return _array[top1];
		} 
		else
		{
			assert(top2 != -1);
			return _array[top2];
		}
	}

	bool Empty(size_t flag)
	{
		if (flag == 1)
		{
			if (top1 == -2)
			{
				return true;
			} 
			else
			{
				return false;
			}
		} 
		else
		{
			if (top2 == -1)
			{
				return true;
			} 
			else
			{
				return false;
			}
		}
	}

	size_t Size(size_t flag)
	{
		if (flag == 1)
		{
			assert(top1 != -2);
			return top1/2 + 1;
		} 
		else
		{
			assert(top2 != -1);
			return (top2 + 1)/2;
		}
	}
protected:
	void CheckCapacity()
	{
		if (((top1 + 2) >= _capacity) || ((top2 + 2) >= _capacity))
		{
			_capacity = _capacity * 2 + 3;
			T* tmp = new T[_capacity];

			int count = top1 > top2 ? top1 : top2;
			for (int index = 0;index <= count; ++index)
			{
				tmp[index] = _array[index];
			}

			delete[] _array;
			_array = tmp;
		}
	}
private:
	T* _array;
	size_t _capacity;
	int top1;//stack1的栈顶下标
	int top2;//stack2的栈顶下标
};
