#pragma once
#include <vector>
#include <assert.h>
template<class T>
class Heap
{
public:
	Heap(){}//无参的构造函数
	Heap(const T* arr,size_t size)//构造函数
	{
		for (size_t i = 0;i < size;i++)
		{
			_arr.push_back(arr[i]);
		}

		//建堆  找到非叶子结点，向下调整
		for (int i = (_arr.size()-2)/2;i >= 0;i--)
		{
			AdjustDown(i);
		}
	}
	void Cout()
	{
		for (int i = 0;i < _arr.size();i++)
		{
			cout<<_arr[i]<<" ";
		}
		cout<<endl;
	}
	bool Empty()
	{
		return _arr.empty();
	}
	int Size()
	{
		return _arr.size();
	}
	void Push(const T& data)
	{
		_arr.push_back(data);
		AdjustUp(_arr.size()-1);
	}
	void Pop()//删除根节点
	{
		//交换根节点和最后一个叶子结点，然后删除最后一个叶子结点
		//然后根节点向上调整
		assert(_arr.empty() != true);
		swap(_arr[0],_arr[_arr.size() - 1]);
		_arr.pop_back();
		AdjustDown(0);
	}
private:
	void AdjustDown(int parent)
	{
		int child = 2 * parent + 1;//左孩子

		while (child < _arr.size())
		{
			//找出左右孩子里较大的一个
			if (((child + 1) < _arr.size())
				&&(_arr[child+1] > _arr[child]))
			{
				child++;
			}
			//比较孩子和父亲
			if (_arr[child] > _arr[parent])
			{
				swap(_arr[child],_arr[parent]);
				parent = child;
				child = 2 * parent + 1;
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

		while (child > 0)
		{
			if (_arr[child] > _arr[parent])
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
protected:
	vector<T> _arr;
};


