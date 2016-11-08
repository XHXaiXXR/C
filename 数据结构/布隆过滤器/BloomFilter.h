#pragma  once
#include "BitMap.h"


struct _HashFunc1
{
	size_t BKDRHash(const char* str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{         
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..         
		}  
		return hash;  
	}  
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

struct _HashFunc2
{
	size_t SDBMHash(const char *str)  
	{  
		register size_t hash = 0;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash = 65599 * hash + ch;         
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}  
		return hash;  
	}  
	size_t operator()(const string& str)
	{
		return SDBMHash(str.c_str());
	}
};

struct _HashFunc3
{
	size_t RSHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t magic = 63689;     
		while (size_t ch = (size_t)*str++)  
		{  
			hash = hash * magic + ch;  
			magic *= 378551;  
		}  
		return hash;  
	}  
	size_t operator()(const string& str)
	{
		return RSHash(str.c_str());
	}
};

struct _HashFunc4
{
	size_t APHash(const char *str)  
	{  
		register size_t hash = 0;  
		size_t ch;  
		for (long i = 0; ch = (size_t)*str++; i++)  
		{  
			if ((i & 1) == 0)  
			{  
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));  
			}  
			else  
			{  
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));  
			}  
		}  
		return hash;  
	}  
	size_t operator()(const string& str)
	{
		return APHash(str.c_str());
	}
};


struct _HashFunc5
{
	size_t JSHash(const char *str)  
	{  
		if(!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;  
		register size_t hash = 1315423911;  
		while (size_t ch = (size_t)*str++)  
		{  
			hash ^= ((hash << 5) + ch + (hash >> 2));  
		}  
		return hash;  
	}  
	size_t operator()(const string& str)
	{
		return JSHash(str.c_str());
	}
};

template<class K = string,
class HashFunc1 = _HashFunc1,
class HashFunc2 = _HashFunc2,
class HashFunc3 = _HashFunc3,
class HashFunc4 = _HashFunc4,
class HashFunc5 = _HashFunc5
>
class BloomFiter
{
public:
	BloomFiter(int num)
		:_map(num * 5)
		,_range(num * 5)
	{}
	void SetBloom(const K& key)
	{
		//映射五个位置，将五个位置全都置成1

		size_t Hash1 = HashFunc1()(key) % _range;
		_map.Set(Hash1);

		size_t Hash2 = HashFunc2()(key) % _range;
		_map.Set(Hash2);

		size_t Hash3 = HashFunc3()(key) % _range;
		_map.Set(Hash3);

		size_t Hash4 = HashFunc4()(key) % _range;
		_map.Set(Hash4);

		size_t Hash5 = HashFunc5()(key) % _range;
		_map.Set(Hash5);

		cout<<Hash1<<" ";
		cout<<Hash2<<" ";
		cout<<Hash3<<" ";
		cout<<Hash4<<" ";
		cout<<Hash5<<endl;;
	}
	bool TestBloom(const K& key)
	{
		HashFunc1 hf1;
		if (_map.Test(hf1(key) % _range) == false)
		{
			return false;
		}
		HashFunc2 hf2;
		if (_map.Test(hf2(key) % _range) == false)
		{
			return false;
		}
		HashFunc3 hf3;
		if (_map.Test(hf3(key) % _range) == false)
		{
			return false;
		}
		HashFunc4 hf4;
		if (_map.Test(hf4(key) % _range) == false)
		{
			return false;
		}
		HashFunc5 hf5;
		if (_map.Test(hf5(key) % _range) == false)
		{
			return false;
		}

		return true;
	}
private:
	BitMap _map;
	size_t _range;
};