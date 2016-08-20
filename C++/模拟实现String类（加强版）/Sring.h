#pragma once
#include <assert.h>
#include <string>
class String
{
	friend ostream& operator<<(ostream& os,String& str);
public:
	//构造函数
	String(const char* str = "")//缺省给一个空字符串，使求长度的时候，不会出现错误
		:_size(strlen(str))
		,_capacity(strlen(str)+1)//容量多加一个是放'\0'
		,_str(new char[_capacity])
	{
		strcpy(_str,str);
	}
	//析构函数
	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
	//拷贝构造函数
	String(const String& s)
		:_size(s._size)
		,_capacity(s._capacity)
		,_str(new char[_capacity])
	{
		//深拷贝，给_str一块自己的空间，使两个指针分别指向两个不同的空间
		strcpy(_str,s._str);
	}
	////传统写法
	//String& operator=(const String& s)
	//{
	//	//防止自身给自身赋值
	//	if (this != &str)
	//	{
	//		delete[] _str;
	//		_str = new char[strlen(s._str)+1];
	//		strcpy(_str,s._str);

	//		//错误示范
	//		//刚开始最后一句写成了_str = s._str
	//		//造成了浅拷贝的错误
	//		//同一块空间被释放两次导致程序错误
	//	}
	//	return *this;
	//}

	//现代写法，强盗式逻辑
	String& operator=(String s)
	{
		swap(_size,s._size);
		swap(_capacity,s._capacity);
		swap(_str,s._str);
		return *this;
	}
	char* c_str()
	{
		return _str;
	}
	char& operator[](int index)
	{
		return _str[index];
	}
	void PushBack(char ch)
	{
		CheckCapacity(1);
		//_str[_size] = ch;
		//_size++;
		//_str[_size] = '\0';
		_str[_size++] = ch;
		_str[_size] = '\0';//最后一个字符一定要记得放入一个'\0'
	}
	void PushBack(char* str)
	{
		CheckCapacity(strlen(str));
		char* tmp1 = _str;
		while (*tmp1)
		{
			tmp1++;
		}
		char* tmp2 = str;
		while (*tmp2)
		{
			*tmp1++ = *tmp2++;
		}
		*tmp1 = '\0';
		_size += strlen(str);
	}
	size_t Size()
	{
		return _size;
	}
	size_t Capacity()
	{
		return _capacity;
	}
	bool Empty()
	{
		if (_str)
		{
			return false;
		} 
		else
		{
			return true;
		}
	}
	String& Insert(size_t pos, const String& s)
	{
		CheckCapacity(strlen(s._str));
		int size1 = _size;
		int newsize1 = _size;
		int size2 = s._size;
		int newsize2 = s._size;
		int count = size2;
		while (size2--)
		{
			_str[size1-1+count] = _str[size1-1];
			size1--;
		}
		char* tmp = s._str;
		while (count--)
		{
			_str[pos++] = *tmp++;
		}
		_size = newsize1+newsize2;
		_str[_size] = '\0';
		return *this;
	}
	String& Erase(size_t pos,size_t len)
	{
		int newlen = strlen(_str);
		assert((pos >= 0) && (pos < newlen));
		assert((len > 0) && (len <= newlen));
		int size = strlen(_str) - len;
		int count = len;

		for (int i = pos;i < newlen;i++)
		{
			_str[i] = _str[i + len];
		}
		_str[size] = '\0';
		_size -= count;
		return *this;
	}
protected:
	void CheckCapacity(int count)
	{
		if ((_size+count) >= _capacity)
		{
			int _newcapacity = 
				(_size+count)>(2*_capacity)?
				(_size+count):(2*_capacity);
			_capacity = _newcapacity;
			char* tmp = new char[_newcapacity];
			strcpy(tmp,_str);
			delete[] _str;
			_str = tmp;
		}
	}
private:
	size_t _size;
	size_t _capacity;
	char* _str;
};

ostream& operator<<(ostream& os,String& str)
{
	os<<str._str;
	return os;
}