class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str)+1+4])//+1表示字符串后面要放一个'\0'，+4表示多开辟一个空间存放引用计数
	{
		_str += 4;//_str指向数据存放区
		strcpy(_str, str);
		_GetCount() = 1;//刚开始这里写成了_GetCount++,其实是不对的，因为引用计数所指向的这块空间并没有初始化，他的值并不是0，是一个随机值，随机值++还是随机值
	}
	String(const String& s)
		:_str(s._str)
	{
		_GetCount()++;
	}
	String& operator=(String& s)
	{
		if (this != &s)
		{
			if (--_GetCount() == 0)
			{
				delete[] (_str-4);
			}
			++s._GetCount();
			_str = s._str;
		}
		return *this;
	}
	~String()
	{
		if (--_GetCount() == 0)
		{
			delete[] (_str-4);
		}
	}
public:
	int& _GetCount()
	{
		return *((int*)_str-1);
	}
private:
	char* _str;
};