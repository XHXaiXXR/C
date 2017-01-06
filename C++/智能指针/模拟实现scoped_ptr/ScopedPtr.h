#pragma once

template<class T>
class ScopedPtr
{
public:
	//explicit�͹��캯��һ��ʹ��,ָ�����캯��ֻ����ʾʹ��,Ŀ����Ϊ�˷�ֹ����Ҫ����ʽת��
	explicit ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}

	//��������
	~ScopedPtr()
	{
		if (NULL != _ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	T* Get()const
	{
		return _ptr;
	}

	void Swap(ScopedPtr<T>& sp)
	{
		swap(_ptr,sp._ptr);
	}
protected:
	//�ſ�������ֵ��ֻ���������壬������������˽�л򱣻���������
	ScopedPtr(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& sp);
private:
	T* _ptr;
};