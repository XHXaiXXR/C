#pragma once

template<class T>
class AutoPtr
{
public:
	//构造函数
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	//拷贝构造函数
	AutoPtr(AutoPtr<T>& ap)
	{
		_ptr = ap._ptr;
		ap._ptr = NULL;	//权限转移，ap._ptr所管理的这块内存现在由_ptr来管理，一块
						//空间不能有两个指针指向，所以内存交由_ptr管理后，ap._ptr
						//就不能再管理这块内存了，需要把ap._ptr置空
	}

	//赋值运算符重载（=）
	AutoPtr<T>& operator=(AutoPtr<T>& ap)
	{
		delete _ptr;
		_ptr = ap._ptr;
		ap._ptr = NULL;	//权限转移
		return *this;
	}

	//析构函数
	~AutoPtr()
	{
		if (NULL != _ptr)
		{
			delete _ptr;
			_ptr = NULL;
		}
	}

	//得到这个指针
	T* Get()
	{
		return _ptr;
	}

	//智能指针有和指针相似的功能，所以要实现（*）解引用和（->）指向
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