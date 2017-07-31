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

//���ڵ���׷�ݵ�trace.log
inline static void __trace_debug(const char* function, const char* filename, int line, char* format, ...)
{
	//��ȡ�����ļ�
#ifdef __DEBUG__
	//������Ժ�������Ϣ
	//fprintf(stdout, "��%s : %d��%s",GetFileName(filename).c_str(), line, function);
	fprintf(fout, "��%s : %d��%s",GetFileName(filename).c_str(), line, function);

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

typedef void(*MALLOCALLOC)();	//����ָ�룬��void(*)()������ΪMALLOCALLOC

template<int inst>
class MallocAllocTemplate
{
private:
	static void* _OoMalloc(size_t n);			//malloc���ٿռ�ʧ�ܵ��õĺ���,����øú�����ͼϵͳ�ͷſռ�
	static MALLOCALLOC _MallocAllocOomHandler;	//�ڴ治���ʱ�������	����ָ��
public:
	MallocAllocTemplate(){}
	static void* Allocate(size_t n)	//����n���ֽڵĿռ䣬����malloc����
	{
		__TRACE_DUBUG("��һ���ռ�������������%u���ֽ�", n);

		void* result = 0;
		result = malloc(n);	//void* malloc(size_t size)

		if (0 == result)	//����mallocʧ�ܣ������_OomMalloc
		{
			_OoMalloc(n);
		}

		return result;
	}
	static void DeAllocate(void* p, size_t n)	//�ͷ����ռ䣬����free����
	{	
		__TRACE_DUBUG("һ���ռ��������ͷ���0x%p:%u���ֽ�", p, n);

		free(p);	//�ͷ����ռ�
		p = NULL;	//ָ���ÿ���һ�����õ�ϰ��
	}
	static MALLOCALLOC SetMallocHandle(MALLOCALLOC f)	//����һ�������������ͷ���ֵ����һ������ָ��
	{
		__TRACE_DUBUG("һ���ռ���������ͼϵͳ�ͷſռ�");

		MALLOCALLOC old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;	//���ڴ����ʧ�ܵľ������Ϊf������ָ��һ���ڴ�ʧ�ܣ���ϵͳȥ�ͷ������ط��ռ�ĺ�����
		return old;
	}
};

typedef MallocAllocTemplate<0> malloc_alloc;

template<int inst>
void* MallocAllocTemplate<inst>::_OoMalloc(size_t n)
{
	__TRACE_DUBUG("һ���ռ�����������%u���ֽ�ʧ�ܣ�����_OoMalloc", n);

	MALLOCALLOC MyMallocHandler;//����һ������ָ��
	void* result = NULL;

	while (1)
	{
		MyMallocHandler = _MallocAllocOomHandler;

		if (0 == MyMallocHandler)	//û�������ڴ治�㴦�����
		{
			throw std::bad_alloc();
		}

		(*MyMallocHandler)();	//�����ڴ治�㴦�����������ͷ������ط����ڴ�

		if (result == malloc(n))	//���������ڴ棬����ɹ����˳�while()��ѭ����������벻�ɹ���ô�Ͳ��ϵ�����ֱ������ɹ�
		{
			break;
		}
	}
}

template<int inst>
//void(*MallocAllocTemplate<inst>::_MallocAllocOomHandler)() = 0;
MALLOCALLOC MallocAllocTemplate<inst>::_MallocAllocOomHandler = 0;

//�����ռ���������Ĭ�ϵĿռ���������
//���������Ŀռ����128�ֽ�ʱ������һ���ռ���������һ���ռ�����������malloc()�������ٿռ�
//���������Ŀռ�С�ڵ���128�ֽ�ʱ��ֱ��ȡ�ڴ�ػ����������������ʺϵĿռ��С������

enum{ _ALIGN = 8 };			//���ջ�׼ֵΪ8�ı��������ڴ����
enum{ _MAXBYTES = 128 };	//�������������Ŀ�Ĵ�С��128
enum{ _NFREELISTS = 16 };	//��������ĳ��ȣ��൱�� _MAXBYTES / _ALIGN

template<bool threads,int inst>
class DefaultAllocTemplate
{
	//���������������
	union _Obj
	{
		_Obj* _FreeListLink;	//ָ�������������ָ��
		char _ClienData[1];		//��¶���ͻ�����
	};
private:
	static char* _startFree;	//�ڴ�ص�ͷָ��
	static char* _endFree;	//�ڴ�ص�βָ��
	static size_t _heapSize;	//��¼�ڴ���Ѿ���ϵͳ�����˶����ڴ�
	static _Obj* volatile _freeList[_NFREELISTS];	//����������һ�����飬���鳤��Ϊ_NFREELISTS��ÿ��Ԫ�ض���һ��_Obj������
private:
	static size_t _GetFreeListInder(size_t bytes)		//��������ֽ�bytes�����������ж�Ӧ�±��λ��
	{
		return (bytes + (size_t)_ALIGN - 1) / (size_t)_ALIGN - 1;
	}
	static size_t _GetRoundUp(size_t bytes)			//������ֽ�������8�ı���
	{
		return (bytes + (size_t)_ALIGN - 1) & (~(_ALIGN - 1));
	}
	static void* _Refill(size_t n)						//���ڴ������ռ䣬���������ռ�ĵ�ַ������ж���Ŀռ䣬Ҫ������Ŀռ�ҵ�����������
	{
		//�ܽ��������������ô��������������û��������n�ֽڵ��ڴ��
		int nobjs = 20;//Ĭ��һ������20��n��С�Ŀռ䣬���ص�һ���ڴ�ռ�ĵ�ַ����������ڴ����������������Ա������������ڴ棬��������Ϊ�����Ч��
		
		__TRACE_DUBUG("���������%u��λ����û�пյĻ����ɹ�ʹ�ã������λ�������%u�������", _GetFreeListInder(n), nobjs);

		char* chunk = _ChunkAlloc(n,nobjs);//��Ҫȥ�ڴ������������ڴ棬��������ڴ��ڹҵ�����������

		if (1 == nobjs)
		{
			//���ֻ���뵽��һ��n�ֽڵ��ڴ�ռ䣬��ô��ֱ�Ӱ����ռ�ĵ�ַ���ػ�ȥ
			return chunk;
		}

		//�ߵ���һ����˵����ֹ������һ��n�ֽڵĴ�С�Ŀռ䣬����Ҫ��������ڴ�ռ�ֿ��������������
		_Obj* ret = (_Obj*)chunk;//�����һ��ռ�ĵ�ַ����������ڴ�ռ������������󣬻�Ҫ���������������ռ�ĵ�ַ����

		//������Ŀռ�ֿ��������������
		_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(n);//�ҵ����������ж�Ӧ��λ��
		*myFreeList = (_Obj*)(chunk + n);//ָ��ƫ��һ������Ĵ�С�����ڶ�������ĵ�ַ����������������Ӧ��λ����
		_Obj* cur = *myFreeList;
		_Obj* next = 0;
		cur->_FreeListLink = 0;
		for (int i = 2;i < nobjs;++i)//��ʣ�µ��ڴ�鶼����ȥ
		{
			//�൱��β��
			next = (_Obj*)(chunk + n * i);
			cur->_FreeListLink = next;
			cur = next;
		}
		cur->_FreeListLink = 0;//����ѭ���Ժ���Ҫ������������Ӧλ�������һ������ָ���ÿ�

		return ret;//�ѵ�һ��ռ��ַ����
	}
	static char* _ChunkAlloc(size_t size,int& nobjs)	//����ڴ����
	{
		char* result = 0;
		size_t totalBytes = size * nobjs;//�ܹ�������ڴ�ռ��С
		size_t leftBytes = _endFree - _startFree;//�ڴ����ʣ��Ŀռ��С

		if (leftBytes > totalBytes)//ʣ��Ĵ���������ģ���ô��ֱ�ӷ����ȥ�����ı��ڴ����ͷָ���ָ��
		{
			__TRACE_DUBUG("�ڴ������%u���ֽڣ��㹻����%u���ֽڣ����Է���%u������", leftBytes, totalBytes, nobjs);

			result = _startFree;//��¼�������ռ�
			_startFree += totalBytes;//�ı��ڴ����ͷָ���ָ��
			return result;//��������ռ�
		}
		else if (leftBytes >= size)//ʣ��������ܷ���һ������Ĵ�С
		{
			nobjs = (int)(leftBytes / size);//��������ٿ�size��С���ڴ�飬onbj�Ĵ�С�����ﱻ�ı�

			__TRACE_DUBUG("�ڴ������%u���ֽڣ���������%u���ֽڣ�ֻ�ܷ���%������",leftBytes, totalBytes, nobjs);

			result = _startFree;
			_startFree += (nobjs * size);//�ڴ��ͷָ�뱻�ı�
			return result;
		}
		else//�ڴ������һ��size��С���ڴ�ռ䶼���䲻������
		{
			//�ж��ڴ�����ǲ��ǻ����ڴ棬����еĻ�����ʣ����ڴ�������������ϣ������¸��ڴ�ؿ���һ�����Ŀռ�
			if (leftBytes > 0)//�ڴ���л����ڴ�
			{
				__TRACE_DUBUG("�ڴ���л����ڴ棬�����������������%��λ����", _GetFreeListInder(leftBytes));

				_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(leftBytes);
				((_Obj*)_startFree)->_FreeListLink = *myFreeList;
				*myFreeList = (_Obj*)_startFree;
			}

			//���¿��ٸ�����µĿռ䵱���ڴ��
			size_t newBytes = 2 * totalBytes + _GetRoundUp(_heapSize>>4);//ÿ��������Ҫ����Ĵ�С��2�����������࿪��_heap��1/16�����������Ϊ8�ı������Ĵ�С�Է�ֹ����Ҳ���ϵͳ�����ڴ�
			_startFree = (char*)malloc(newBytes);//���¿��ٿռ䣬�����ڴ�ص�ͷָ��ָ���·���Ŀռ�

			__TRACE_DUBUG("�����ڴ����û���Ѿ�û�����ڴ棬malloc����%u���ֽ�", newBytes);

			//�������ʧ��
			if (0 == _startFree)
			{
				//�������ʧ�ܵĻ�������ϵͳ���Ѿ�û���ڴ����ṩʹ���ˣ���ʱ������Ҫ��������������һ���
				//size���ֽڻ�����ڴ�飬������������л���û�к��ʵ��ڴ����Ϊ�ڴ�صĻ�����ô�͵���һ
				//���ռ�������ȥ����һ���µĿռ�

				__TRACE_DUBUG("malloc����%u���ֽ�ʧ��", newBytes);

				for (size_t i = size;i < (size_t)_MAXBYTES;++i)
				{
					_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(i);
					_Obj* p = *myFreeList;

					if (0 != p)//�������������Ӧλ�����ҵ�һ���ڴ��
					{
						__TRACE_DUBUG("�����������%uλ�����ҵ����еĻ����", _GetFreeListInder(i));
						_startFree = (char*)p;//�ڴ���е�ͷָ��ָ���µ��ڴ��
						*myFreeList = p->_FreeListLink;//�൱��ͷɾ
						_endFree = _startFree + i;
						return _ChunkAlloc(size,nobjs);//�ݹ��ٵ���_ChunkAlloc()���������ٻ���else if(leftBytes > size)��ʱ��᷵��һ��ռ�ĵ�ַ
					}
				}

				//����forѭ������ô��������������Ҳû�к��ʵ��ڴ���ڹ���ʹ�ã���ô��Ҫ����һ���ռ�������
				//�������ڴ治��Ĵ�����ƣ�Ҫ�ǻ����ܿ����µĿռ�Ļ������Զ��׳��쳣

				__TRACE_DUBUG("malloc�����ڴ�ʧ�ܲ���������������Ҳû���ҵ����ʵĿջ���飬����һ���ռ�������");

				_endFree = NULL;//����һ��Ҫ��_endFree�ÿգ����һ���ռ�������������ʧ���׳��쳣����ʱ_startFreeҲһ����0
				//������ÿգ���ô��ʱ��ͷβָ�벻��ȣ�ʹ�õ�ʱ��ͻ���Ϊ�ڴ���л��пռ䣬��ô�ʹ���
				_startFree = (char*)malloc_alloc::Allocate(newBytes);//����һ���ռ�������
			}

			__TRACE_DUBUG("����ռ�ɹ�");
			//���ٳɹ�
			_heapSize += newBytes;//����_heapSize(��¼�ܹ���ϵͳ�����˶����ڴ�)
			_endFree = _startFree + newBytes;//�����ڴ����βָ���ָ��
			return _ChunkAlloc(size,nobjs);//�ݹ��ٵ���_ChunkAlloc()���������ٻ���else if(leftBytes > size)��ʱ��᷵��һ��ռ�ĵ�ַ
		}
	}
public:
	DefaultAllocTemplate(){}
	static void* Allocate(size_t n)//�����ڴ棬�����Ҫ����Ŀռ����128���ֽھ͵���һ���ռ�����������֮�����ȵ�����������ȥ��ȡ���������������û�У���ô�͵���Refill()����ȥ�ڴ��������
	{
		void* ret = NULL;

		//�ж���Ҫ����Ŀռ��Ƿ����128�ֽ�
		if (n > _MAXBYTES)
		{
			//����_MAXBYTES�ֽ�����Ϊ�Ǵ���ڴ棬ֱ�ӵ���һ���ռ�������
			ret = malloc_alloc::Allocate(n);
		}
		else	//ȥ��������������һ����ʵĿռ����
		{
			__TRACE_DUBUG("������ռ�����������%u���ֽ�", n);

			//myFreeList��һ��ָ�룬ָ�����������㣨�������Ϊ_Obj����ָ��
			_Obj* volatile  *myFreeList = _freeList + _GetFreeListInder(n);//��myFreeListָ������ֽ�����Ӧ�����������λ��
			_Obj* result = *myFreeList;

			if (0 == result)	//��Ӧ�����������µ�λ����û�й�(_Obj)���͵Ľڵ㣬�൱��û���ڴ��
			{
				//���������Ӧλ����û�нڵ㣬�޷������ڴ棬��ʱ��Ҫȥ�ڴ��������
				ret = _Refill(_GetRoundUp(n));//����Ĵ�С��ȻҲӦ����8�����������������ܱ�֤���������Ϲҵ������ڴ�鶼��8��������
			} 
			else //�����������з���Ҫ����ڴ����Խ��з���
			{
				__TRACE_DUBUG("���������%u��λ�û��пյĻ����ɹ�ʹ��", _GetFreeListInder(n));

				//ժȡ��һ���ڴ�飬�ѵڶ����ڴ��ĵ�ַ��ŵ���һ��λ����ȥ���൱��ͷɾ��
				*myFreeList = result->_FreeListLink;//�ѵڶ���ռ�ĵ�ַ����������������
				ret = result;
			}
		}
		return ret;
	}
	static void DeAllocate(void* p,size_t n)//�ͷ��ڴ档������ռ����128�ֽڣ���ô�͵���һ���ռ���������_DeAlloc()ȥֱ���ͷţ���֮�������ռ�ҵ�����������
	{
		// �ж�����ֽڵĴ�С�Ƿ����_MAXBYTES��������ڣ������һ���ռ�������
		if (n > _MAXBYTES)
		{
			malloc_alloc::DeAllocate(p, n);
		}
		else	//������ͷſռ䣬�ǽ��ڴ�������������������������Ӧλ��
		{
			__TRACE_DUBUG("�����������%u��λ���ϲ���յĻ����", _GetFreeListInder(n));

			_Obj* del = (_Obj*)p;//viod���͵�ָ����Ҫת��������������Ͳ��ܶ�ָ����мӼ�
			_Obj* volatile *myFreeList = _freeList + _GetFreeListInder(n);//�ҵ�������������Ӧ��λ��
			del->_FreeListLink = *myFreeList;//�ͷŵ����ռ�������Ӧ��������λ�õĵ�ַ
			*myFreeList = del;//�ڰ��ͷŵ����ռ�ĵ�ַ�ŵ������������Ӧλ���ϣ��൱��ͷ�壩
		}
	}
};

template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::_startFree = NULL;	//�ڴ�ص�ͷָ��

template<bool threads,int inst>
char* DefaultAllocTemplate<threads,inst>::_endFree = NULL;	//�ڴ�ص�βָ��

template<bool threads,int inst>
size_t DefaultAllocTemplate<threads,inst>::_heapSize = 0;	//��¼�ڴ���Ѿ���ϵͳ�����˶����ڴ�

template<bool threads,int inst>
typename DefaultAllocTemplate<threads,inst>::_Obj* volatile 
	DefaultAllocTemplate<threads,inst>::_freeList[_NFREELISTS] = {0};	//����������һ�����飬���鳤��Ϊ_NFREELISTS��ÿ��Ԫ�ض���һ��_Obj������

//����һ�㳡��
void test()
{
	DefaultAllocTemplate<true,0> d;
	char* p = (char*)d.Allocate(100);
	int* q = (int*)d.Allocate(129);
	d.DeAllocate(q,129);
	d.DeAllocate(p,100);
}

//���Է����ͷŵĳ���
void test2()
{
	int begin = GetTickCount();

	DefaultAllocTemplate<true,0> d;
	vector<pair<void*, int>> v;
	v.push_back(make_pair(d.Allocate(130), 130));

	for (int i = 0;i < 100;++i)
	{
		//����С��128�ֽڵĿռ�
		v.push_back(make_pair(d.Allocate(20), 20));
	}
	while (!v.empty())
	{
		d.DeAllocate(v.back().first, v.back().second);
		v.pop_back();
	}

	for (int i = 0;i < 100;++i)
	{
		//�������128�ֽڵĿռ�
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

//�����ڴ�ط���Ч�ʺ�malloc����Ч�ʵıȽ�
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
	cout<<"�ڴ�� : "<<end-begin<<endl;
}
int main()
{
	test3();
	system("pause");
	return 0;
}