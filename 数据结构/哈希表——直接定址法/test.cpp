#include<iostream>
using namespace std;
#include<vector>

enum Status
{
	EMPTY,
	EXIST,
	DELETE,
};

template<class K,class V>
struct HashTableNode
{
	K _key;
	V _value;
	Status _status;

	HashTableNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_status(EMPTY)
	{}
};

template<class K,class V>
class HashTable
{
	typedef HashTableNode<K,V> Node;
public:
	HashTable()
		:_size(0)
	{
		_table.resize(0);
		//_table.resize(_GetNextPrime(0));
	}

	bool Insert(const K& key,const V& value)
	{
		//检查负载因子，查看是否需要扩容
		_Check();
		int index = _HashFunc(key);
		
		while(_table[index]._status != EMPTY)
		{
			++index;
			if(index == _table.size())
			{
				index = 0;
			}		
		}

		_table[index]._key = key;
		_table[index]._value = value;
		_table[index]._status = EXIST;
		_size++;
	}
	Node* Find(const K& key)
	{
		size_t index = _HashFunc(key);
		//记录第一次查找的下标
		size_t src = index;

		while(_table[index]._status != EMPTY)
		{
			if(_table[index]._key == key)
			{
				if(_table[index]._status != DELETE)
					return &_table[index];
				else
					return NULL;
			}
			++index;

			if(index == _table.size())
				index = 0;
			
			//避免死循环操作
			if(index == src)
				return NULL;
		}

		return NULL;
	}

	bool Remove(const K& key)
	{
		Node* ret = Find(key);

		if(ret)
		{
			ret->_status = DELETE;
			--_size;
			return true;
		}

		return false;
	}

	void Display()
	{
		for(int i = 0;i < _table.size();i++)
		{
			if(_table[i]._status == DELETE)
				_table[i]._key = 0;

			cout<<"["<<i<<"] "<<_table[i]._key<<endl;
		}
		cout<<"size = "<<_size<<endl;
	}
protected:
	void _Check()
	{
		if(_table.size() != 0 &&_size*10 / _table.size() < 8)
			return;
		
		//负载因子超过或等于0.8，需要进行扩容
		size_t newsize = _GetNextPrime(_table.size());
		HashTable<K,V> hash;
		hash._table.resize(newsize);
		for(int i = 0;i < _table.size();i++)
		{
			if(_table[i]._status == EXIST)
			{
				hash.Insert(_table[i]._key,_table[i]._value);
			}
		}
		this->_Swap(hash);
	}
	void _Swap(HashTable<K,V>& ht)
	{
		_table.swap(ht._table);
		swap(_size,ht._size);
	}
	size_t _HashFunc(int key)
	{
		return key % _table.size();
	}
	size_t _GetNextPrime(int num)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =\
		{\
			53ul,97ul,193ul,389ul,769ul,1543ul,3079ul,6151ul,12289ul,24593ul,49157ul,98317ul,196613ul,393241ul,786433ul,1572869ul,3145739ul,6291469ul,12582917ul,25165843ul,50331653ul,100663319ul,201326611ul,402653189ul,805306457ul,1610612741ul,3221225473ul,4294967291ul\
		};

		for(size_t i = 0;i < _PrimeSize;i++)
		{
			if(_PrimeList[i] > num)
				return _PrimeList[i];
		}

		return _PrimeList[_PrimeSize-1];
	}
private:
	vector<Node> _table;
	size_t _size;
};

void test()
{
	HashTable<int,int> hs;
	int a[] = {89,18,49,58,9};
	for(int i = 0;i < sizeof(a)/sizeof(a[0]);i++)
	{
		hs.Insert(a[i],i);
	}
	hs.Display();
	hs.Remove(18);
	hs.Display();

}
int main()
{
	test();
	return 0;
}