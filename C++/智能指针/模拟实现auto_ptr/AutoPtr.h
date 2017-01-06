#pragma once

template<class T>
class AutoPtr
{
public:
	//���캯��
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	//�������캯��
	AutoPtr(AutoPtr<T>& ap)
	{
		_ptr = ap._ptr;
		ap._ptr = NULL;	//Ȩ��ת�ƣ�ap._ptr�����������ڴ�������_ptr������һ��
						//�ռ䲻��������ָ��ָ�������ڴ潻��_ptr�����ap._ptr
						//�Ͳ����ٹ�������ڴ��ˣ���Ҫ��ap._ptr�ÿ�
	}

	//��ֵ��������أ�=��
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		delete _ptr;
		_ptr = ap._ptr;
		ap._ptr = NULL;	//Ȩ��ת��
		return *this;
	}

	//��������
	~AutoPtr()
	{
		if (NULL != _ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	//�õ����ָ��
	T* Get()
	{
		return _ptr;
	}

	//����ָ���к�ָ�����ƵĹ��ܣ�����Ҫʵ�֣�*�������úͣ�->��ָ��
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};