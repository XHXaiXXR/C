#include<iostream>
using namespace std;

struct TrueType
{
	//����������
	bool Get()
	{
		return true;
	}
};

struct FalseType
{
	//������������
	bool Get()
	{
		return false;
	}
};

template<class T>
struct TypeTraits
{
	typedef FalseType IsPODType;//�����������ͣ�ISPODType��FalseType
};

//�ػ����е���������
template<>
struct TypeTraits<int>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<unsigned int>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<short>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<unsigned short>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<char>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<unsigned char>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<float>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<double>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<long double>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<unsigned long>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<long long>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<>
struct TypeTraits<unsigned long long>
{
	typedef TrueType IsPODType;//���������ͣ�IsPODType��TrueType
};

template<class T>
void Copy(T* dest,T* src,int size)
{
	if (TypeTraits<T>::IsPODType().Get() == true)//����������
	{
		memmove(dest,src,size * sizeof(T));
	} 
	else//������������
	{
		for (int i = 0;i < size;++i)
		{
			dest[i] = src[i];
		}
	}
}
