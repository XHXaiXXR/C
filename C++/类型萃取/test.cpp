#include<iostream>
using namespace std;

struct TrueType
{
	//是内置类型
	bool Get()
	{
		return true;
	}
};

struct FalseType
{
	//不是内置类型
	bool Get()
	{
		return false;
	}
};

template<class T>
struct TypeTraits
{
	typedef FalseType IsPODType;//不是内置类型，ISPODType是FalseType
};

//特化所有的内置类型
template<>
struct TypeTraits<int>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<unsigned int>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<short>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<unsigned short>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<char>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<unsigned char>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<float>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<double>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<long double>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<unsigned long>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<long long>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<>
struct TypeTraits<unsigned long long>
{
	typedef TrueType IsPODType;//是内置类型，IsPODType是TrueType
};

template<class T>
void Copy(T* dest,T* src,int size)
{
	if (TypeTraits<T>::IsPODType().Get() == true)//是内置类型
	{
		memmove(dest,src,size * sizeof(T));
	} 
	else//不是内置类型
	{
		for (int i = 0;i < size;++i)
		{
			dest[i] = src[i];
		}
	}
}
