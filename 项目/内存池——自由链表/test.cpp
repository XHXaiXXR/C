#include<iostream>
using namespace std;
#include <vector>
#include <string>
#include <stdio.h>

template<class T>
class OBJectPool
{
	//每一个节点挂着一个内存
	struct BlockNode
	{
		void* _memory;		//指向一块已经分配好的内存块
		BlockNode* _next;	//指向下一个结点的指针
		size_t _objNum;		//内存块中内存对象的个数

		BlockNode(size_t objNum)
			:_next(NULL)
			,_objNum(objNum)
		{
			//malloc( 对象的个数 * sizeof(T) )     
			//malloc( 对象的个数 * 单个对象的大小 )
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
	OBJectPool(size_t initSize = 32,size_t maxNum = 1000000)//这里initSize不是字节大小，而是对象个数
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
	//从内存池中直接取已开辟的空间，减少了直接向内存new申请空间操作带来的开销
	T* New()
	{
		//优先使用以前释放的空间
		if (_lastDelete)
		{
			T* obj = _lastDelete;				//先把_lastDelete保存起来
			
			//T** = 指针变量的地址		*(T**) = T* = 指针
			_lastDelete = *((T**)_lastDelete);	//取出最后释放的一块地址空间，让_lastDelete指向倒数第二个释放的空间
			
			//new的定位表达式，相当于调用它的构造函数
			return new(obj) T();				//把这块内存用定位new来初始化
		}

		//如果没有内存对象，就要申请新的节点对象
		if (_countIn >= _last->_objNum)
		{
			//已经没有了内存对象，重新分配内存	
			AllocateNewNode();
		}

		//如果有内存对象，就直接在内存块中申请
		T* obj = (T*)_last->_memory + _countIn;//内存块转成指针类型在加上当前节点在用的计数，相当于指针偏移，现在就直接指向一块没有被使用的内存对象
		++_countIn;//使用一块内存对象，当前节点在用的计数就要加一，以便后续使用
		return new(obj) T();
	}

	//释放内存
	void Delete(T* ptr)
	{
		if (ptr)
		{
			ptr->~T();//会调用BlockNode的析构函数

			//释放的内存还给内存池，用_lastDelete连接起来以备后续New使用，
			*((T**)ptr) = _lastDelete;	//先把_lastDelete保存起来
			_lastDelete = ptr;			//改变_lastDelete的指向
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
			cout<<"有内存对象没有释放"<<endl;
			//这里最好抛出异常
		}

		_countIn = 0;
		_first = _last = NULL;
	}
	void AllocateNewNode()
	{
		size_t objNum = _last->_objNum * 2;//每次申请的内存块对象以二倍增长
		
		if(objNum > _maxNum)
			objNum = _maxNum;

		_last->_next = new BlockNode(objNum);
		_last = _last->_next;
		_countIn = 0;//新开辟的内存节点要记得把_countIn置为0
	}
private:
	BlockNode* _first;		//指向内存池链表节点的头
	BlockNode* _last;		//指向内存池链表节点的尾
	T* _lastDelete;			//指向最新释放的对象空间
	size_t _countIn;		//当前节点在用的计数
	size_t _maxNum;			//节点申请内存块最大的对象个数
	static size_t _itemSize;//单个对象的大小(静态的成员变量需要在类外定义)
};

template<class T>
size_t OBJectPool<T>::_itemSize = OBJectPool<T>::InitItemSize();

///////////////////////////////////////////////////////////
// 测试内存对象池的常规使用和内存对象的重复使用
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

// 针对当前的内存对象池进行简单的性能测试
void TestObjectPoolOP()
{
	size_t begin , end;
	vector<string*> v;
	const size_t N = 1000000;
	v.reserve(N);

	cout<<"pool new/delete==============================="<<endl;
	// 反复申请释放5次
	begin = GetTickCount();
	OBJectPool<string> pool;

	//第一次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//第二次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//第三次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//第四次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(pool.New());
	}

	while (!v.empty())
	{
		pool.Delete(v.back());
		v.pop_back();
	}
	//第五次
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
	
	//第一次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//第二次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//第三次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//第四次
	for (size_t i = 0; i < N; ++i)
	{
		v.push_back(new string);
	}

	while (!v.empty())
	{
		delete v.back();
		v.pop_back();
	}
	//第五次
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