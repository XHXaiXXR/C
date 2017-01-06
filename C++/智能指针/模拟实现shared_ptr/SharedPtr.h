#pragma once

template<class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		,_pCount(new int(1))
	{}

	SharedPtr(const SharedPtr<T>& sp)
	{
		_ptr = sp._ptr;
		_pCount = sp._pCount;
		++(*_pCount);
	}

	SharedPtr<T>& operator=(SharedPtr<T>& sp)
	{
		swap(_ptr,sp._ptr);
		swap(_pCount,sp._pCount);
	}

	~SharedPtr()
	{
		if (--(*_pCount) == 0)
		{
			delete _ptr;
			delete _pCount;
			_ptr = NULL;
			_pCount = NULL;
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
private:
	T* _ptr;
	int* _pCount;//引用计数也通过一块空间去管理它
};