#pragma once
//һ���ռ�������

typedef void(*MALLOCALLOC)();	//����ָ�룬��void(*)()������ΪMALLOCALLOC

template<int inst>
class MallocAllocTemplate
{
private:
	static void* _OoMalloc(size_t n);			//malloc���ٿռ�ʧ�ܵ��õĺ���
	static MALLOCALLOC _MallocAllocOomHandler;	//�ڴ治���ʱ�������	����ָ��
public:
	MallocAllocTemplate(){}
	static void* Allocate(size_t n)	//����n���ֽڵĿռ䣬����malloc����
	{
		void* result = 0;
		result = malloc(n);	//void* malloc(size_t size)

		if (0 == result)	//����mallocʧ�ܣ������_OomMalloc
		{
			_OoMalloc(n);
		}

		return result;
	}
	static void DeAllocate(void* p)	//�ͷ����ռ䣬����free����
	{
		free(p);	//�ͷ����ռ�
		p = NULL;	//ָ���ÿ���һ�����õ�ϰ��
	}
	static MALLOCALLOC SetMallocHandle(MALLOCALLOC f)	//����һ�������������ͷ���ֵ����һ������ָ��
	{
		MALLOCALLOC old = _MallocAllocOomHandler;
		_MallocAllocOomHandler = f;	//���ڴ����ʧ�ܵľ������Ϊf������ָ��һ���ڴ�ʧ�ܣ���ϵͳȥ�ͷ������ط��ռ�ĺ�����
		return old;
	}
};

typedef MallocAllocTemplate<0> malloc_alloc;

template<int inst>
void* MallocAllocTemplate<inst>::_OoMalloc(size_t n)
{
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