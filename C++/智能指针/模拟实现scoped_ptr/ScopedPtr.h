#pragma once

template<class T>
class ScopedPtr
{
public:
	//explicit和构造函数一起使用,指明构造函数只能显示使用,目的是为了防止不必要的隐式转化
	explicit ScopedPtr(T* ptr)
		:_ptr(ptr)
	{}

	//析构函数
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
	//放拷贝防赋值，只声明不定义，并把声明放在私有或保护作用域内
	ScopedPtr(const ScopedPtr<T>& sp);
	ScopedPtr<T>& operator=(const ScopedPtr<T>& sp);
private:
	T* _ptr;
};