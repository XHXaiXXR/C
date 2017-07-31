#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
using namespace std;
#include <vadefs.h>
#include <stdarg.h>
#include <Windows.h>
#include <vector>

#define __DEBUG__

FILE* fout = fopen("trace.log", "w");

static string GetFileName(const string& path)
{
	char ch = '/';

#ifdef __WIN32
	ch = '\\';
#endif

	size_t pos = path.rfind(ch);
	if (pos == string::npos)
	{
		return path;
	}
	else
	{
		return path.substr(pos+1);
	}
}

//用于调试追溯的trace.log
inline static void __trace_debug(const char* function, const char* filename, int line, char* format, ...)
{
	//读取配置文件
#ifdef __DEBUG__
	//输出调试函数的信息
	//fprintf(stdout, "【%s : %d】%s",GetFileName(filename).c_str(), line, function);
	fprintf(fout, "【%s : %d】%s",GetFileName(filename).c_str(), line, function);

	va_list args;//typedef char* va_list;
	va_start(args, format);//#define va_start(ap,v)  ( ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v) )
	
	//vfprintf(stdout, format, args);
	vfprintf(fout, format, args);

	//fprintf(stdout, "%c", '\n');
	fprintf(fout, "%c", '\n');

	va_end(args);
#endif
}

#define __TRACE_DUBUG(...) __trace_debug(__FUNCTION__, __FILE__, __LINE__, __VA_ARGS__)

typedef void(*MALLOCALLOC)();	//函数指针，将void(*)()重命名为MALLOCALLOC

template<int inst>
class MallocAllocTemplate
{
private:
	static void* _OoMalloc(size_t n);			//malloc开辟空间失败调用的函数,会调用该函数企图系统释放空间
	static MALLOCALLOC _MallocAllocOomHandler;	//内存不足的时候处理机制	函数指针
public:
	MallocAllocTemplate(){}
	static void* Allocate(size_t n)	//分配n个字节的空间，调用malloc函数
	{
		__TRACE_DUBUG("向一级空间配置器申请了%u个字节", n);

		void* result = 0;
		result = malloc(n);	//void* malloc(size_t size)

		if (0 == result)	//如若malloc失败，则调用_OomMalloc
		{
			_OoMalloc(n);
		}

		return result;
	}
	static void DeAllocate(void* p, size_t n)	//释放这块空间，调用free函数
	{	
		__TRACE_DUBUG("一级空间配置器释放了0x%p:%u个字节", p, n);

		free(p);	//释放这块空间
		p = NULL;	//指针置空是一个良好的习惯
	}
	static MALLOCALLOC SetMallocHandle(MALLOCALLOC f)	//这是一个函数，参数和返回值都是一个函数指针
	{
		__TRACE_DUBUG("一级空间配置器企图系统释放空间");

		MALLOCALLOC old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;	//将内存分配失败的句柄设置为f（让它指向一个内存失败，让系统去释放其他地方空间的函数）
		return old;
	}
};

typedef MallocAllocTemplate<0> malloc_alloc;

template<int inst>
void* MallocAllocTemplate<inst>::_OoMalloc(size_t n)
{
	__TRACE_DUBUG("一级空间配置器申请%u个字节失败，调用_OoMalloc", n);

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

//二级空间配置器（默认的空间配置器）
//当申请分配的空间大于128字节时，调用一级空间配置器，一级空间配置器中用malloc()函数开辟空间
//当申请分配的空间小于等于128字节时，直接取内存池或者自由链表中拿适合的空间大小来分配

enum{ _ALIGN = 8 };			//按照基准值为8的倍数进行内存操作
enum{ _MAXBYTES = 128 };	//自由链表中最大的块的大小是128
enum{ _NFREELISTS = 16 };	//自由链表的长度，相当于 _MAXBYTES / _ALIGN

template<bool threads,int inst>
class DefaultAllocTemplate
{
	//自由链表结点的类型
	union _Obj
	{
		_Obj* _FreeListLink;	//指向自由链表结点的指针
		char _ClienData[1];		//暴露给客户看的
	};
private:
	static char* _startFree;	//内存池的头指针
	static char* _endFree;	//内存池的尾指针
	static size_t _heapSize;	//记录内存池已经向系统申请了多大的内存
	static _Obj* volatile _freeList[_NFREELISTS];	//自由链表，是一个数组，数组长度为_NFREELISTS，每个元素都是一个_Obj的类型
private:
	static size_t _GetFreeListInder(size_t bytes)		//计算这个字节bytes在自由链表中对应下标的位置
	{
		return (bytes + (size_t)_ALIGN - 1) / (size_t)_ALIGN - 1;
	}
	static size_t _GetRoundUp(size_t bytes)			//把这个字节上升到8的倍数
	{
		return (bytes + (size_t)_ALIGN - 1) & (~(_ALIGN - 1));
	}
	static void* _Refill(size_t n)						//向内存池申请空间，并返回这块空间的地址，如果有多余的空间，要将多余的空间挂到自由链表上
	{
		//能进入这个函数，那么就是自由链表上没有能满足n字节的内存块
		int nobjs = 20;//默认一次申请20个n大小的空间，返回第一块内存空间的地址，将多余的内存块挂在自由链表上以便后续申请分配内存，这样做是为了提高效率
		
		__TRACE_DUBUG("自由链表的%u的位置上没有空的缓冲块可供使用，在这个位置上填充%u个缓冲块", _GetFreeListInder(n), nobjs);

		char* chunk = _ChunkAlloc(n,nobjs);//需要去内存池中申请大块的内存，将多余的内存在挂到自由链表上

		if (1 == nobjs)
		{
			//如果只申请到了一块n字节的内存空间，那么就直接把这块空间的地址返回回去
			return chunk;
		}

		//走到这一步，说明不止分配了一个n字节的大小的空间，我们要将多余的内存空间分块挂在自由链表上
		_Obj* ret = (_Obj*)chunk;//保存第一块空间的地址，将多余的内存空间挂在自由链表后，还要将保存起来的这块空间的地址返回

		//将多余的空间分块挂在自由链表上
		_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(n);//找到自由链表中对应的位置
		*myFreeList = (_Obj*)(chunk + n);//指针偏移一个对象的大小，将第二个对象的地址放在自由链表中相应的位置上
		_Obj* cur = *myFreeList;
		_Obj* next = 0;
		cur->_FreeListLink = 0;
		for (int i = 2;i < nobjs;++i)//将剩下的内存块都挂上去
		{
			//相当于尾插
			next = (_Obj*)(chunk + n * i);
			cur->_FreeListLink = next;
			cur = next;
		}
		cur->_FreeListLink = 0;//出了循环以后需要将自由链表相应位置上最后一个结点的指针置空

		return ret;//把第一块空间地址返回
	}
	static char* _ChunkAlloc(size_t size,int& nobjs)	//大块内存分配
	{
		char* result = 0;
		size_t totalBytes = size * nobjs;//总共请求的内存空间大小
		size_t leftBytes = _endFree - _startFree;//内存池内剩余的空间大小

		if (leftBytes > totalBytes)//剩余的大于所申请的，那么就直接分配出去，并改变内存池中头指针的指向
		{
			__TRACE_DUBUG("内存池中有%u个字节，足够分配%u个字节，可以分配%u个对象", leftBytes, totalBytes, nobjs);

			result = _startFree;//记录保存这块空间
			_startFree += totalBytes;//改变内存池中头指针的指向
			return result;//返回这个空间
		}
		else if (leftBytes >= size)//剩余的至少能分配一个对象的大小
		{
			nobjs = (int)(leftBytes / size);//能申请多少块size大小的内存块，onbj的大小在这里被改变

			__TRACE_DUBUG("内存池中有%u个字节，不够分配%u个字节，只能分配%个对象",leftBytes, totalBytes, nobjs);

			result = _startFree;
			_startFree += (nobjs * size);//内存池头指针被改变
			return result;
		}
		else//内存池中连一块size大小的内存空间都分配不出来了
		{
			//判断内存池中是不是还有内存，如果有的话，把剩余的内存挂在自由链表上，再重新给内存池开辟一块更大的空间
			if (leftBytes > 0)//内存池中还有内存
			{
				__TRACE_DUBUG("内存池中还有内存，将他挂在自由链表的%的位置上", _GetFreeListInder(leftBytes));

				_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(leftBytes);
				((_Obj*)_startFree)->_FreeListLink = *myFreeList;
				*myFreeList = (_Obj*)_startFree;
			}

			//重新开辟更大的新的空间当做内存池
			size_t newBytes = 2 * totalBytes + _GetRoundUp(_heapSize>>4);//每次以所需要申请的大小以2倍增长，并多开辟_heap的1/16（但必须调整为8的倍数）的大小以防止多次找操作系统分配内存
			_startFree = (char*)malloc(newBytes);//重新开辟空间，并让内存池的头指针指向新分配的空间

			__TRACE_DUBUG("现在内存池中没有已经没有了内存，malloc申请%u个字节", newBytes);

			//如果开辟失败
			if (0 == _startFree)
			{
				//如果开辟失败的话，表明系统中已经没有内存在提供使用了，这时候我们要到自由链表中找一块比
				//size个字节还大的内存块，如果自由链表中还是没有合适的内存块作为内存池的话，那么就调用一
				//级空间配置器去开辟一块新的空间

				__TRACE_DUBUG("malloc申请%u个字节失败", newBytes);

				for (size_t i = size;i < (size_t)_MAXBYTES;++i)
				{
					_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(i);
					_Obj* p = *myFreeList;

					if (0 != p)//在自由链表的相应位置下找到一块内存块
					{
						__TRACE_DUBUG("在自由链表的%u位置下找到空闲的缓冲块", _GetFreeListInder(i));
						_startFree = (char*)p;//内存池中的头指针指向新的内存块
						*myFreeList = p->_FreeListLink;//相当于头删
						_endFree = _startFree + i;
						return _ChunkAlloc(size,nobjs);//递归再调用_ChunkAlloc()函数，至少会在else if(leftBytes > size)的时候会返回一块空间的地址
					}
				}

				//出了for循环，那么就是自由链表中也没有合适的内存块在供你使用，那么就要调用一级空间配置器
				//其中有内存不足的处理机制，要是还不能开辟新的空间的话，会自动抛出异常

				__TRACE_DUBUG("malloc申请内存失败并且在自由链表中也没有找到合适的空缓冲块，调用一级空间配置器");

				_endFree = NULL;//这里一定要将_endFree置空，如果一级空间配置器中申请失败抛出异常，这时_startFree也一定是0
				//如果不置空，那么此时的头尾指针不相等，使用的时候就会以为内存池中还有空间，那么就错了
				_startFree = (char*)malloc_alloc::Allocate(newBytes);//调用一级空间配置器
			}

			__TRACE_DUBUG("申请空间成功");
			//开辟成功
			_heapSize += newBytes;//更新_heapSize(记录总共向系统申请了多少内存)
			_endFree = _startFree + newBytes;//更新内存池中尾指针的指向
			return _ChunkAlloc(size,nobjs);//递归再调用_ChunkAlloc()函数，至少会在else if(leftBytes > size)的时候会返回一块空间的地址
		}
	}
public:
	DefaultAllocTemplate(){}
	static void* Allocate(size_t n)//分配内存，如果需要分配的空间大于128个字节就调用一级空间配置器，反之，则先到自由链表中去获取，自由链表中如果没有，那么就调用Refill()函数去内存池中申请
	{
		void* ret = NULL;

		//判断需要分配的空间是否大于128字节
		if (n > _MAXBYTES)
		{
			//大于_MAXBYTES字节则认为是大块内存，直接调用一级空间配置器
			ret = malloc_alloc::Allocate(n);
		}
		else	//去自由链表里面找一块合适的空间分配
		{
			__TRACE_DUBUG("向二级空间配置器申请%u个字节", n);

			//myFreeList是一个指针，指向自由链表结点（结点类型为_Obj）的指针
			_Obj* volatile  *myFreeList = _freeList + _GetFreeListInder(n);//让myFreeList指向这个字节所对应的自由链表的位置
			_Obj* result = *myFreeList;

			if (0 == result)	//对应的自由链表下的位置下没有挂(_Obj)类型的节点，相当于没有内存块
			{
				//自由链表对应位置下没有节点，无法分配内存，这时候要去内存池中申请
				ret = _Refill(_GetRoundUp(n));//申请的大小自然也应该是8的整数倍，这样才能保证自由链表上挂的所有内存块都是8的整数倍
			} 
			else //自由链表下有符合要求的内存块可以进行分配
			{
				__TRACE_DUBUG("自由链表的%u的位置还有空的缓冲块可供使用", _GetFreeListInder(n));

				//摘取第一个内存块，把第二块内存块的地址存放到第一个位置上去（相当于头删）
				*myFreeList = result->_FreeListLink;//把第二块空间的地址放在了自由链表上
				ret = result;
			}
		}
		return ret;
	}
	static void DeAllocate(void* p,size_t n)//释放内存。如果这块空间大于128字节，那么就调用一级空间配置器的_DeAlloc()去直接释放，反之，将这块空间挂到自由链表上
	{
		// 判断这个字节的大小是否大于_MAXBYTES，如果大于，则调用一级空间配置器
		if (n > _MAXBYTES)
		{
			malloc_alloc::DeAllocate(p, n);
		}
		else	//这里的释放空间，是将内存回收起来，挂在自由链表的相应位置
		{
			__TRACE_DUBUG("在自由链表的%u的位置上插入空的缓冲块", _GetFreeListInder(n));

			_Obj* del = (_Obj*)p;//viod类型的指针需要转成所需的其他类型才能对指针进行加减
			_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(n);//找到自由链表中相应的位置
			del->_FreeListLink = *myFreeList;//释放的这块空间里存放相应自由链表位置的地址
			*myFreeList = del;//在把释放的这块空间的地址放到自由链表的相应位置上（相当于头插）
		}
	}
};

template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::_startFree = NULL;	//内存池的头指针

template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::_endFree = NULL;	//内存池的尾指针

template<bool threads,int inst>
size_t DefaultAllocTemplate<threads,inst>::_heapSize = 0;	//记录内存池已经向系统申请了多大的内存

template<bool threads,int inst>
typename DefaultAllocTemplate<threads,inst>::_Obj* volatile 
	DefaultAllocTemplate<threads,inst>::_freeList[_NFREELISTS] = {0};	//自由链表，是一个数组，数组长度为_NFREELISTS，每个元素都是一个_Obj的类型

//测试一般场景
void test()
{
	DefaultAllocTemplate<true,0> d;
	char* p = (char*)d.Allocate(100);
	int* q = (int*)d.Allocate(129);
	d.DeAllocate(q,129);
	d.DeAllocate(p,100);
}

//测试分配释放的场景
void test2()
{
	int begin = GetTickCount();

	DefaultAllocTemplate<true,0> d;
	vector<pair<void*, int>> v;
	v.push_back(make_pair(d.Allocate(130), 130));

	for (int i = 0;i < 100;++i)
	{
		//申请小于128字节的空间
		v.push_back(make_pair(d.Allocate(20), 20));
	}
	while (!v.empty())
	{
		d.DeAllocate(v.back().first, v.back().second);
		v.pop_back();
	}

	for (int i = 0;i < 100;++i)
	{
		//申请大于128字节的空间
		v.push_back(make_pair(d.Allocate(130), 130));
	}
	while (!v.empty())
	{
		d.DeAllocate(v.back().first, v.back().second);
		v.pop_back();
	}

	int end = GetTickCount();
	cout<<end - begin<<endl;
}

//测试内存池分配效率和malloc分配效率的比较
void test3()
{
	int begin = GetTickCount();

	vector<int*> v;
	for (int i = 0;i < 100000;i++)
	{
		//int* p = (int* )malloc(sizeof(int) * (i%300+1));
		int* p = (int* )malloc(sizeof(int) * 100);
		v.push_back(p);
	}
	while (!v.empty())
	{
		free(v.back());
		v.pop_back();
	}

	int end = GetTickCount();
	cout<<"malloc : "<<end-begin<<endl;


	begin = GetTickCount();

	DefaultAllocTemplate<true,0> d;
	vector<pair<void*, int>> vv;

	for (int i = 0;i < 100000;++i)
	{
		//vv.push_back(make_pair(d.Allocate(i%300+1), (i%300+1)));
		vv.push_back(make_pair(d.Allocate(100), 100));
	}
	while (!vv.empty())
	{
		d.DeAllocate(vv.back().first, vv.back().second);
		vv.pop_back();
	}

	end = GetTickCount();
	cout<<"内存池 : "<<end-begin<<endl;
}
int main()
{
	test3();
	system("pause");
	return 0;
}