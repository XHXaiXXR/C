#include<iostream>
using namespace std;

//Ĭ��ɾ����
struct DefaultDel
{
	void operator()(void* ptr)
	{
		delete ptr;
		cout<<"delete ptr"<<endl;
	}
};

//��̬���ٿռ���ͷ�
struct Free
{
	void operator()(void* ptr)
	{
		free(ptr);
		cout<<"free(ptr)"<<endl;
	}
};

//�ļ��ر�
struct Fclose
{
	void operator()(void* ptr)
	{
		fclose((FILE*)ptr);
		cout<<"fclose((FILE*)ptr)"<<endl;
	}
};


template<class T,class D = DefaultDel>
class SharedPtr
{
public:
	SharedPtr(T* ptr,D del = DefaultDel())
		:_ptr(ptr)
		,_pCount(new int(1))
		,_del(del)
	{}

	~SharedPtr()
	{
		if (--(*_pCount) == 0)
		{
			_del(_ptr);//���ö�Ӧ��ɾ��������ɾ��
			delete _pCount;
			_ptr = NULL;
			_pCount = NULL;
		}
	}

	SharedPtr(const SharedPtr<T,D>& sp)
	{
		_ptr = sp._ptr;
		_pCount = sp._pCount;
		++(*_pCount);
	}

	SharedPtr<T,D>& operator=(SharedPtr<T,D>& sp)
	{
		swap(_ptr,sp._ptr);
		swap(_pCount,sp._pCount);
		return *this;
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
	int* _pCount;
	D _del;
};

void test()
{
	SharedPtr<int> spInt(new int);
	SharedPtr<FILE,Fclose> spFile(fopen("Max.txt","r"),Fclose());
	SharedPtr<string,Free> spFree((string*)malloc(sizeof(string)),Free());
}
int main()
{
	test();
	system("pause");
	return 0;
}