#include<iostream>
using namespace std;

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a,size_t n)
		:_n(n)
		,_size(n*(n+1)/2)
		,_matrix(new T[n*(n+1)/2])
	{
		size_t index = 0;
		for(size_t i = 0;i < _n;i++)
		{
			for(size_t j = 0;j < _n;j++)
			{
				if(i >= j)
				{
					_matrix[index++] = a[i*_n+j];	
				}
				else
				{
					continue;
				}
			}
		}
	}

	T& access(size_t i,size_t j)
	{
		if(i < j)
		{
			swap(i,j);
		}
		return _matrix[i*(i+1)/2+j];
	}
	
	void Display()
	{
		for(size_t i = 0;i < _n;i++)
		{
			for(size_t j = 0;j < _n;j++)
			{
				cout<<access(i,j)<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}
private:
	T* _matrix;
	size_t _size;
	size_t _n;
};

void test()
{
	int a[][4] =\
	{ \
	  {0,1,2,3},\
	  {1,0,4,5},\
	  {2,4,0,6},\
	  {3,5,6,0},\
	};

	SymmetricMatrix<int> s((int *)a,4);
	s.Display();
}
int main()
{
	test();
	return 0;
}