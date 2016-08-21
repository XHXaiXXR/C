#define _CRT_SECURE_NO_WARNINGS 1

class String
{
public:
	//���캯��
	String(const char* str)
		:_str(new char[strlen(str)+1+4])
	{
		_str += 4;//ʹ_strָ�����ݿռ�
		_GetCount() = 1;
		strcpy(_str,str);
	}
	//��������
	~String()
	{
		//����ռ䱻һ��ռ���ָ�������ü���Ϊ1��ʱ
		//���ʱ����ͷſռ�
		if (--_GetCount() == 0)
		{
			delete[] (_str-4);
		}
	}
	//��������
	String(const String& s)
		:_str(s._str)//ֱ�Ӹ�ֵ��ʹ���ռ��ֱ�ָһ��
	{
		//��ʱ�����ü����Ӽ�
		++_GetCount();
	}
	String& operator=(String& s)//�����ڲ��ܼ�const����Ϊ��Ķ���_GetCount()
	{
		//��ֹ���������ֵ
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
		//����������ռ��Ǳ�����ָ����ָ
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