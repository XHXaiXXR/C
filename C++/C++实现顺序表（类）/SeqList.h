#pragma once
#include <assert.h>
typedef int DataType;
class SeqList
{
	friend ostream& operator<<(ostream& os,SeqList seq);
public:
	SeqList()
		:_size(0)
		,_capacity(0)
		,_data(NULL)
	{}
	~SeqList()
	{
		if (_data)
		{
			delete[] _data;
			_data = NULL;
		}
		_size = 0;
		_capacity = 0;
	}
	//拷贝构造
	SeqList(const SeqList& seq)
	{
		_data = new DataType[seq._capacity];
		//内存拷贝
		memcpy(_data,seq._data,sizeof(DataType)*seq._size);
		_size = seq._size;
		_capacity = seq._capacity;
	}
public:
	bool Empty()
	{
		return _size==0;
	}
	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}
	void PushBack(const DataType& data)
	{
		CheckCapacity();
		_data[_size++] = data;
	}
	void PushFront(const DataType& data)
	{
		CheckCapacity();
		for (int i = _size;i > 0;i--)
		{
			_data[i] = _data[i-1];
		}
		_data[0] = data;
		_size++;
	}
	void PopBack()
	{
		if (Empty())
		{
			return;
		}
		else
		{
			_size--;
		}
	}
	void PopFront()
	{
		for (int i = 1;i < _size;i++)
		{
			_data[i-1] = _data[i];
		}
		_size--;
	}
	int Find(const DataType& data)
	{
		for (int i = 0;i < _size;i++)
		{
			if (_data[i] == data)
			{
				//如果找到了，返回当前位置的下标
				return i;
			}
		}
		return -1;
	}
	DataType FindData(const DataType& data)
	{
		for (int i = 0;i < _size;i++)
		{
			if (_data[i] == data)
			{
				//如果找到了，返回当前位置的下标
				return _data[i];
			}
		}
		return NULL;
	}
	//找到某一个位置，在这个位置后面插入数据
	void Insert(int pos,const DataType& data)
	{
		assert(pos != -1);
		CheckCapacity();
		for (int i = _size;i > pos;i--)
		{
			_data[i] = _data[i-1];
		}
		_data[pos+1] = data;
		_size++;
	}
	//找到要删除的位置，删除该位置上的数据
	void Remove(int pos)
	{
		if (_size != 0)
		{
			assert(pos != -1);
			for (int i = pos;i < _size-1;i++)
			{
				_data[i] = _data[i+1];
			}
			_size--;
		}
	}
	void RemoveAll(const DataType& data)
	{
		if (_size != 0)
		{
			int i = 0;
			while (i < _size)
			{
				if (_data[i] == data)
				{
					for (int j = i;j < _size-1;j++)
					{
						_data[j] = _data[j+1];
					}
					_size--;
				}
				else
				{
					i++;
				}
			}
		}
	}
	void Sort(SeqList seq)
	{
		int i = 0;
		int j = 0;
		for (i = 0;i < _size-1;i++)
		{
			for (j = i;j < _size-1-i;j++)
			{
				if (seq._data[j] > seq._data[j+1])
				{
					swap(seq._data[j],seq._data[j+1]);
				}
			}
		}
	}
private:
	void CheckCapacity()
	{
		if (_size >= _capacity)
		{
			int newcapacity = 2*_capacity+5;
			DataType* tmp = new DataType[newcapacity];
			memcpy(tmp,_data,sizeof(DataType)*_size);
			delete[] _data;
			_data = tmp;
			_capacity = newcapacity;
		}
	}
private:
	int _size;
	int _capacity;
	DataType* _data;
};

//重载输出运算符
ostream& operator<<(ostream& os,SeqList seq)
{
	for (int i = 0;i < seq._size;i++)
	{
		os<<seq._data[i]<<" ";
	}
	return os;
}