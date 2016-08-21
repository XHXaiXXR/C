#define _CRT_SECURE_NO_WARNINGS 1

class String
{
public:
	//构造函数
	String(const char* str)
		:_str(new char[strlen(str)+1+4])
	{
		_str += 4;//使_str指向数据空间
		_GetCount() = 1;
		strcpy(_str,str);
	}
	//析构函数
	~String()
	{
		//如果空间被一块空间所指（即引用计数为1）时
		//这个时候才释放空间
		if (--_GetCount() == 0)
		{
			delete[] (_str-4);
		}
	}
	//拷贝构造
	String(const String& s)
		:_str(s._str)//直接赋值，使这块空间又被指一次
	{
		//这时候引用计数加加
		++_GetCount();
	}
	String& operator=(String& s)//括号内不能加const，因为会改动到_GetCount()
	{
		//防止自身给自身赋值
		if (this != &s)
		{
			if (--_GetCount() == 0)
			{
				delete[] (_str-4);
			}
			++(s._GetCount());
			_str = s._str;
		}
		return *this;
	}
	char& operator[](int index)
	{
		//先屡清楚这块空间是被多少指针所指
		if (_GetCount() != 1)
		{
			--_GetCount();
			char* tmp = new char[strlen(_str)+1+4];
			strcpy(tmp+4,_str);
			_str = tmp+4;
			++_GetCount();
		}
		return _str[index];
	}
private:
	int& _GetCount()
	{
		return *((int *)_str-1);
	}
private:
	char* _str;
};