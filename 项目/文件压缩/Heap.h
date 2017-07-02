#pragma once
#include <vector>
#include <assert.h>

template<class T>  
struct Less  
{  
	bool operator()(const T& left,const T& Right)  
	{  
		return left < Right;  
	}  
};  

template<class T>  
struct Greater  
{  
	bool operator()(const T& left,const T& Right)  
	{  
		return left > Right;  
	}  
};  

template<class T,class Compare = Greater<T>>//缺省值给大堆  
class Heap  
{  
public:  
	Heap()
	{}
	Heap(const T* arr,const size_t size)  
	{  
		for (int i = 0;i < size;i++)  
		{  
			_arr.push_back(arr[i]);  
		}  

		//建堆  
		for (int i = (_arr.size() - 2) / 2;i >= 0;i--)  
		{  
			//寻找非叶子结点，向下调整；  
			AdjustDown(i);  
		}  
	}  
	void Push(const T& data)  
	{  
		_arr.push_back(data);  
		AdjustUp(_arr.size()-1);  
	}  
	void Pop()  
	{  
		assert(_arr.empty() != true);  
		swap(_arr[0],_arr[_arr.size()-1]);  
		_arr.pop_back();  
		AdjustDown(0);  
	}  
	const T& Top()  
	{  
		return _arr[0];  
	}  
	bool Empty()  
	{  
		return _arr.empty();  
	}  
	int Size()  
	{  
		return _arr.size();  
	}  
	void Cout()  
	{  
		for (int i = 0; i < _arr.size();i++)  
		{  
			cout<<_arr[i]<<" ";  
		}  
		cout<<endl;  
	}  
private:  
	void AdjustDown(int parent)  
	{  
		int child = 2 * parent + 1;//左孩子  
		Compare com;  
		while (child < _arr.size())  
		{  
			if (((child+1) < _arr.size())&&(com(_arr[child + 1],_arr[child])))  
			{  
				++child;  
			}  
			if (com(_arr[child],_arr[parent]))  
			{  
				swap(_arr[child],_arr[parent]);  
				parent = child;  
				child = parent * 2 + 1;  
			}   
			else  
			{  
				break;  
			}  
		}  
	}  
	void AdjustUp(int child)  
	{  
		int parent = (child - 1) / 2;  
		Compare com;  
		while (child > 0)  
		{  
			if (com(_arr[child],_arr[parent]))  
			{  
				swap(_arr[child],_arr[parent]);  
				child = parent;  
				parent = (child - 1) / 2;  
			}   
			else  
			{  
				break;  
			}  
		}  
	}  
private:
	vector<T> _arr;  
};  