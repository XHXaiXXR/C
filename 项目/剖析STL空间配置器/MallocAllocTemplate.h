#pragma once
//一级空间配置器

typedef void(*MALLOCALLOC)();	//函数指针，将void(*)()重命名为MALLOCALLOC

template<int inst>
class MallocAllocTemplate
{
private:
	static void* _OoMalloc(size_t n);			//malloc开辟空间失败调用的函数
	static MALLOCALLOC _MallocAllocOomHandler;	//内存不足的时候处理机制	函数指针
public:
	MallocAllocTemplate(){}
	static void* Allocate(size_t n)	//分配n个字节的空间，调用malloc函数
	{
		void* result = 0;
		result = malloc(n);	//void* malloc(size_t size)

		if (0 == result)	//如若malloc失败，则调用_OomMalloc
		{
			_OoMalloc(n);
		}

		return result;
	}
	static void DeAllocate(void* p)	//释放这块空间，调用free函数
	{
		free(p);	//释放这块空间
		p = NULL;	//指针置空是一个良好的习惯
	}
	static MALLOCALLOC SetMallocHandle(MALLOCALLOC f)	//这是一个函数，参数和返回值都是一个函数指针
	{
		MALLOCALLOC old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;	//将内存分配失败的句柄设置为f（让它指向一个内存失败，让系统去释放其他地方空间的函数）
		return old;
	}
};

typedef MallocAllocTemplate<0> malloc_alloc;

template<int inst>
void* MallocAllocTemplate<inst>::_OoMalloc(size_t n)
{
	MALLOCALLOC MyMallocHandler;//定义一个函数指针
	void* result = NULL;

	while (1)
	{
		MyMallocHandler = _MallocAllocOomHandler;

		if (0 == MyMallocHandler)	//没有设置内存不足处理机制
		{
			throw std::bad_alloc();
		}

		(*MyMallocHandler)();	//调用内存不足处理函数，申请释放其他地方的内存

		if (result == malloc(n))	//重新申请内存，申请成功则退出while()死循环，如果申请不成功那么就不断的申请直至申请成功
		{
			break;
		}
	}
}

template<int inst>
//void(*MallocAllocTemplate<inst>::_MallocAllocOomHandler)() = 0;
MALLOCALLOC MallocAllocTemplate<inst>::_MallocAllocOomHandler = 0;