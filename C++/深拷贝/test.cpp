class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
	{
		strcpy(_str, str);
	}
	String(const String& s)
	{
		//内存的拷贝先要创建出一块内存
		_str = new char[strlen(s._str)+1];
		//然后将指针所指向的内容拷贝一份
		strcpy(_str, s._str);
	}
	//赋值运算符的重载
	String& operator=(const String& s)
	{
		//防止自身对自身赋值（因为会delete掉原来的内存空间，如果是自己给自己赋值，那么delete以后就找不到了）
		if (this != &s)
		{
			delete[] _str;
			_str = new char[strlen(s._str) + 1];
			strcpy(_str, s._str);
		}
		return *this;
	}
	~String()
	{
		if (_str)
		{
			delete[] _str;
		}
	}
private:
	char* _str;
};