#pragma once

enum State
{
	EMPTY,//空状态
	EXIST,//存在状态
	DELETE,//删除状态
};

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<class K,class HashFunc = __HashFunc<K>>
class HashTable
{
public:
	HashTable(const size_t capacity)
		:_size(0)
		,_capacity(capacity)
		,_table(new K[capacity])
		,_state(new State[capacity])
	{}
	~HashTable()
	{
		if (_table)
		{
			delete[] _table;
			_table = NULL;
		}
		if (_state)
		{
			delete[] _state;
			_state = NULL;
		}
		_size = 0;
		_capacity = 0;
	}
public:
	int Find(const K& key)
	{
		size_t index = _HashFunc(key);
		while (_state[index] != EMPTY)
		{
			if (_table[index] == key)
			{
				if (_state[index] == DELETE)
				{
					return -1;
				}
				return index;
			}
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}
		return -1;
	}
	bool Insert(const K& key)
	{
		_CheckCapacity();
		size_t index = _HashFunc(key);

		while (_state[index] == EXIST)
		{
			if (_table[index] == key)
			{
				return false;
			}
			++index;
			if (index == _capacity)
			{
				index = 0;
			}
		}

		_table[index] = key;
		_state[index] = EXIST;
		_size++;
		return true;
	}
	bool Remove(const K& key)
	{
		size_t index = Find(key);
		if (index == -1)
		{
			return false;
		} 
		else
		{
			_state[index] = DELETE;
			_size--;
			return true;
		}
	}
	void Print()
	{
		for (int i = 0;i < _capacity;i++)
		{
			cout<<"["<<_state[i]<<"]: "<<_table[i]<<endl;
		}
	}
	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}
protected:
	size_t _HashFunc(const K& key)
	{
		HashFunc hashfunc;
		return hashfunc(key) % _capacity;
	}
	void _CheckCapacity()
	{
		//负载因子大于等于0.7时，增容
		//负载因子 = 元素个数/数组长度
		if (_size*10/_capacity >= 7)
		{
			HashTable<K,HashFunc> tmp(2*_capacity);
			for (int i = 0;i < _capacity;i++)
			{
				if (_state[i] == EXIST)
				{
					tmp.Insert(_table[i]);
				}
			}
			this->_Swap(tmp);
		}
	}
	void _Swap(HashTable<K,HashFunc>& ht)
	{
		swap(_size,ht._size);
		swap(_capacity,ht._capacity);
		swap(_table,ht._table);
		swap(_state,ht._state);
	}
private:
	size_t _size;
	size_t _capacity;
	K* _table;
	State* _state;
};