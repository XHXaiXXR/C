#pragma once
#include<vector>
#include<string>

template<class K,class V>
struct KVNode
{
	K _key;
	V _value;
	KVNode<K,V>* _next;

	KVNode(const K& key = K(),const V& value = V())
		:_key(key)
		,_value(value)
		,_next(NULL)
	{}
};

template<class K>
struct __HashFunc
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//模板的特化
template<>
struct __HashFunc<string>
{
	static size_t BKDRHash(const char* str)
	{
		unsigned int seed = 131;
		unsigned int hash = 0;
		while(*str)
		{
			hash = hash*seed + (*str++);
		}

		return (hash & 0x7FFFFFFF);
	}
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

template<class K,class V,class HashFunc = __HashFunc<K>>
class HashList
{
	typedef KVNode<K,V> Node;
public:
	HashList()
		:_size(0)
	{}

	~HashList()
	{
		for(int i = 0; i < _table.size();i++)
		{
			Node* cur = _table[i];

			while(cur)
			{
				Node* next = cur->_next;

				delete cur;

				cur = next;
			}
		}

		_size = 0;
		_table.clear();
	}
public:
	Node* Find(const K& key)
	{
		for (int i = 0;i < _table.size();i++)
		{
			Node* cur = _table[i];

			while (cur)
			{
				if (cur->_key == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
		}
		return NULL;
	}
	bool Remove(const K& key)
	{
		//繁琐啰嗦的解法
		//Node* prev = NULL;
		//for (int i = 0;i < _table.size();i++)
		//{
		//	Node* cur = _table[i];

		//	while (cur)
		//	{
		//		if (cur->_key == key)
		//		{
		//			//判断删除的是否为头结点
		//			if (prev == NULL)
		//				_table[i] = cur->_next;
		//			else
		//				//删除节点不是头结点
		//				prev->_next = cur->_next;
		//			
		//			delete cur;
		//			return true;
		//		}

		//		prev = cur;
		//		cur = cur->_next;
		//	}
		//}
		//return false;

		size_t index = _HashFunc(key,_table.size());
		Node* cur = _table[index];
		Node* prev = NULL;

		while (cur)
		{
			if (cur->_key == key)
			{
				//判断删除的是否为头结点
				if (prev == NULL)
					_table[index] = cur->_next;
				else
					//删除节点不是头结点
					prev->_next = cur->_next;

				delete cur;
				return true;
			}

			prev = cur;
			cur = cur->_next;
		}

		return false;
	}
	bool Insert(const K& key,const V& value)
	{
		_Check();

		if (Find(key))
		{
			return false;
		}
		size_t index = _HashFunc(key,_table.size());
		Node* cur = new Node(key,value);

		//头插法
		cur->_next = _table[index];
		_table[index] = cur;

		_size++;

		return true;
	}
	void Display()
	{
		for (int i = 0;i < _table.size();i++)
		{
			Node* cur = _table[i];

			cout<<"table["<<i<<"]  = ";
			while (cur)
			{
				//cout<<"_table["<<i<<"] = "<<cur->_key<<"->";
				cout<<cur->_key<<"->";
				cur = cur->_next;
			}

			cout<<"NULL"<<endl;
		}
	}
protected:
	void _Check()
	{
		//第一次进来时，和当负载因子为1时
		if (_table.size() == 0 || _size == _table.size())
		{
			int size = _GetPrimeNum(_table.size());
			//HashList<K,V,HashFunc> tmp;
			vector<Node*> tmp;
			tmp.resize(size);

			for (int i = 0;i < _table.size();i++)
			{
				Node* cur = _table[i];

				while (cur)
				{
					//从旧表中取下节点
					Node* next = cur->_next;
					_table[i] = next;

					//取出的节点重新插入
					size_t index = _HashFunc(cur->_key,tmp.size());
					cur->_next = tmp[index];
					tmp[index] = cur;

					cur = next;
				}
			}
			tmp.swap(_table);
		}
	}

	size_t _HashFunc(const K& key,size_t size)
	{
		HashFunc hf;
		return hf(key)%size;
	}

	size_t _GetPrimeNum(int num)
	{
		// 使用素数表对齐做哈希表的容量，降低哈希冲突
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList [_PrimeSize] =\
		{\
		53ul, 97ul, 193ul, 389ul, 769ul,1543ul, 3079ul, 6151ul, 12289ul, 24593ul,49157ul, 98317ul, 196613ul, 393241ul,786433ul,1572869ul, 3145739ul, 6291469ul, 12582917ul,25165843ul,50331653ul, 100663319ul, 201326611ul, 402653189ul,805306457ul,1610612741ul, 3221225473ul, 4294967291ul\
		};

		for(int i = 0;i < _PrimeSize;i++)
		{
			if(num < _PrimeList[i])
				return _PrimeList[i];
		}

		return _PrimeList[_PrimeSize - 1];
	}
private:
	vector<Node*> _table;
	size_t _size;
};