class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str)+1+4])//+1��ʾ�ַ�������Ҫ��һ��'\0'��+4��ʾ�࿪��һ���ռ������ü���
	{
		_str += 4;//_strָ�����ݴ����
		strcpy(_str, str);
		_GetCount() = 1;//�տ�ʼ����д����_GetCount++,��ʵ�ǲ��Եģ���Ϊ���ü�����ָ������ռ䲢û�г�ʼ��������ֵ������0����һ�����ֵ�����ֵ++�������ֵ
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