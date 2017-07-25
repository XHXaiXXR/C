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
		//�ڴ�Ŀ�����Ҫ������һ���ڴ�
		_str = new char[strlen(s._str)+1];
		//Ȼ��ָ����ָ������ݿ���һ��
		strcpy(_str, s._str);
	}
	//��ֵ�����������
	String& operator=(const String& s)
	{
		//��ֹ���������ֵ����Ϊ��delete��ԭ�����ڴ�ռ䣬������Լ����Լ���ֵ����ôdelete�Ժ���Ҳ����ˣ�
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