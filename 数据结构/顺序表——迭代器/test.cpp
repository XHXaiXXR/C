#include<iostream>
using namespace std;

template<class T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
	Vector()
		:_start(NULL)
		,_finish(NULL)
		,_endofstorage(NULL)
	{}

	Vector(const Vector<T>& v)
		:_start(new T[v.Size()])
	{
		for(int i = 0;i < v.Size();i++)
		{
			_start[i] = v._start[i];
		}

		_finish = _start + v.Size();
		_endofstorage = _start + v.Size();
	}

	~Vector()
	{
		if(_start)
		{
			delete[] _start;
		}
	}
public:
	size_t Size()
	{
		return _finish - _start;
	}
	bool Empty()
	{
		return Size() == 0;
	}
	void PushBack(const T& data)
	{
		Check();
		*_finish = data;
		_finish++;
	}
	void PopBack()
	{
		if (Size() == 0)
		{
			cout<<"empty"<<endl;
		}
		_finish--;
	}

	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}
	ConstIterator Begin()const
	{
		return _start;
	}
	ConstIterator End()const
	{
		return _finish;
	}

private:
	void Check()
	{
		if(_finish == _endofstorage)
		{
			size_t size = Size();
			size_t newsize = 2 * size + 3;
			T* tmp = new T[newsize];

			for(size_t i = 0;i < size;i++)
			{
				tmp[i] = _start[i];
			}

			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + newsize;
		}
	}
private:
	Iterator _start;
	Iterator _finish;
	Iterator _endofstorage;
};

template<class T>
void PrintVector(const Vector<T>& v)
{
	Vector<T>::ConstIterator it = v.Begin();
	while(it != v.End())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}

void test()
{
	Vector<int> v;
	for(int i = 0;i < 5;i++)
	{
		v.PushBack(i);
	}
	PrintVector(v);
	v.PopBack();
	v.PopBack();
	v.PopBack();
	PrintVector(v);
}
int main()
{
	test();
	system("pause");
	return 0;
}