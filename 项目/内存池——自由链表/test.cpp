#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <stdio.h>

template<class T>
class OBJectPool
{
	//ÿһ���ڵ����һ���ڴ�
	struct BlockNode
	{
		void* _memory;		//ָ��һ���Ѿ�����õ��ڴ��
		BlockNode* _next;	//ָ����һ������ָ��
		size_t _objNum;		//�ڴ�����ڴ����ĸ���

		BlockNode(size_t objNum)
			:_next(NULL)
			,_objNum(objNum)
		{
			//malloc( ����ĸ��� * sizeof(T) )     
			//malloc( ����ĸ��� * ��������Ĵ�С )
			_memory = malloc(_objNum * _itemSize);
		}

		~BlockNode()
		{
			free(_memory);
			_memory = NULL;
			_next = NULL;
			_objNum = 0;
		}
	};
public:
	OBJectPool(size_t initSize = 32,size_t maxNum = 1000000)//����initSize�����ֽڴ�С�����Ƕ������
		:_lastDelete(NULL)
		,_countIn(0)
		,_maxNum(maxNum)
	{
		_first = _last = new BlockNode(initSize);
	}
	~OBJectPool()
	{
		Destory();
	}
public:
	//���ڴ����ֱ��ȡ�ѿ��ٵĿռ䣬������ֱ�����ڴ�new����ռ���������Ŀ���
	T* New()
	{
		//����ʹ����ǰ�ͷŵĿռ�
		if (_lastDelete)
		{
			T* obj = _lastDelete;				//�Ȱ�_lastDelete��������
			
			//T** = ָ������ĵ�ַ		*(T**) = T* = ָ��
			_lastDelete = *((T**)_lastDelete);	//ȡ������ͷŵ�һ���ַ�ռ䣬��_lastDeleteָ�����ڶ����ͷŵĿռ�
			
			//new�Ķ�λ���ʽ���൱�ڵ������Ĺ��캯��
			return new(obj) T();				//������ڴ��ö�λnew����ʼ��
		}

		//���û���ڴ���󣬾�Ҫ�����µĽڵ����
		if (_countIn >= _last->_objNum)
		{
			//�Ѿ�û�����ڴ�������·����ڴ�	
			AllocateNewNode();
		}

		//������ڴ���󣬾�ֱ�����ڴ��������
		T* obj = (T*)_last->_memory + _countIn;//�ڴ��ת��ָ�������ڼ��ϵ�ǰ�ڵ����õļ������൱��ָ��ƫ�ƣ����ھ�ֱ��ָ��һ��û�б�ʹ�õ��ڴ����
		++_countIn;//ʹ��һ���ڴ���󣬵�ǰ�ڵ����õļ�����Ҫ��һ���Ա����ʹ��
		return new(obj) T();
	}

	//�ͷ��ڴ�
	void Delete(T* ptr)
	{
		if (ptr)
		{
			ptr->~T();//�����BlockNode����������

			//�ͷŵ��ڴ滹���ڴ�أ���_lastDelete���������Ա�����Newʹ�ã�
			*((T**)ptr) = _lastDelete;	//�Ȱ�_lastDelete��������
			_lastDelete = ptr;			//�ı�_lastDelete��ָ��
		}
	}
	static size_t InitItemSize()
	{
		if (sizeof(T) > sizeof(void*))
			return sizeof(T);
		else
			return sizeof(void*);
	}
protected:
	void Destory()
	{
		BlockNode* cur = _first;

		while (cur)
		{
			BlockNode* del = cur;
			cur = cur->_next;

			delete del;
		}

		if (_lastDelete)
		{
			cout<<"���ڴ����û���ͷ�"<<endl;
			//��������׳��쳣
		}

		_countIn = 0;
		_first = _last = NULL;
	}
	void AllocateNewNode()
	{
		size_t objNum = _last->_objNum * 2;//ÿ��������ڴ������Զ�������
		
		if(objNum > _maxNum)
			objNum = _maxNum;

		_last->_next = new BlockNode(objNum);
		_last = _last->_next;
		_countIn = 0;//�¿��ٵ��ڴ�ڵ�Ҫ�ǵð�_countIn��Ϊ0
	}
private:
	BlockNode* _first;		//ָ���ڴ������ڵ��ͷ
	BlockNode* _last;		//ָ���ڴ������ڵ��β
	T* _lastDelete;			//ָ�������ͷŵĶ���ռ�
	size_t _countIn;		//��ǰ�ڵ����õļ���
	size_t _maxNum;			//�ڵ������ڴ�����Ķ������
	static size_t _itemSize;//��������Ĵ�С(��̬�ĳ�Ա������Ҫ�����ⶨ��)
};

template<class T>
size_t OBJectPool<T>::_itemSize = OBJectPool<T>::InitItemSize();

///////////////////////////////////////////////////////////
// �����ڴ����صĳ���ʹ�ú��ڴ������ظ�ʹ��
void TestObjectPool()
{
	vector<string*> v;

	OBJectPool<string> pool;
	for (size_t i = 0; i < 32; ++i)
	{
		v.push_back(pool.New());
		printf("Pool New [%d]: %p\n", i, v.back());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	for (size_t i = 0; i < 32; ++i)
	{
		v.push_back(pool.New());
		printf("Pool New [%d]: %p\n", i, v.back());
	}

	v.push_back(pool.New());
	printf("Pool New [%d]: %p\n", 32, v.back());
}

#include <Windows.h>

// ��Ե�ǰ���ڴ����ؽ��м򵥵����ܲ���
void TestObjectPoolOP()
{
	size_t begin , end;
	vector<string*> v;
	const size_t N = 1000000;
	v.reserve(N);

	cout<<"pool new/delete==============================="<<endl;
	// ���������ͷ�5��
	begin = GetTickCount();
	OBJectPool<string> pool;

	//��һ��
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//�ڶ���
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//������
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//���Ĵ�
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//�����
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}

	end = GetTickCount();
	cout<<"Pool:"<<end - begin<<endl;

	cout<<"new/delete==============================="<<endl;
	begin = GetTickCount();
	
	//��һ��
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//�ڶ���
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//������
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//���Ĵ�
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//�����
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}

	end = GetTickCount();
	cout<<"new/delete:"<<end - begin<<endl;
}

int main()
{
	//TestObjectPool();
	TestObjectPoolOP();
	system("pause");
	return 0;
}