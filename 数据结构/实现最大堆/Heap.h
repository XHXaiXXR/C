#pragma once
#include <vector>
#include <assert.h>
template<class T>
class Heap
{
public:
	Heap(){}//�޲εĹ��캯��
	Heap(const T* arr,size_t size)//���캯��
	{
		for (size_t i = 0;i < size;i++)
		{
			_arr.push_back(arr[i]);
		}

		//����  �ҵ���Ҷ�ӽ�㣬���µ���
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
	void Pop()//ɾ�����ڵ�
	{
		//�������ڵ�����һ��Ҷ�ӽ�㣬Ȼ��ɾ�����һ��Ҷ�ӽ��
		//Ȼ����ڵ����ϵ���
		assert(_arr.empty() != true);
		swap(_arr[0],_arr[_arr.size() - 1]);
		_arr.pop_back();
		AdjustDown(0);
	}
private:
	void AdjustDown(int parent)
	{
		int child = 2 * parent + 1;//����

		while (child < _arr.size())
		{
			//�ҳ����Һ�����ϴ��һ��
			if (((child + 1) < _arr.size())
				&&(_arr[child+1] > _arr[child]))
			{
				child++;
			}
			//�ȽϺ��Ӻ͸���
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


