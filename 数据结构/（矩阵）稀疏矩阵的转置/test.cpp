#include<iostream>
using namespace std;
#include<vector>
#include<string.h>

template<class T>
struct Triple
{
	size_t _row;
	size_t _col;
	T _value;

	Triple(size_t row = 0,size_t col = 0,const T& value = T())
		:_row(row)
		,_col(col)
		,_value(value)
	{}
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix(){}
	SparseMatrix(T* a,size_t m,size_t n,const T& invalid)
		:_m(m)
		,_n(n)
		,_invalid(invalid)
	{
		for(size_t i = 0;i < _m;i++)
		{
			for(size_t j = 0;j < _n;j++)
			{
				if(a[i*_n+j] != _invalid)
				{
					Triple<T> t(i,j,a[i*_n+j]);
					_matrix.push_back(t);
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;

		for(size_t i = 0;i < _m;i++)
		{
			for(size_t j = 0;j < _n;j++)
			{
				if(index < _matrix.size()\
					&& _matrix[index]._row == i\
					&& _matrix[index]._col == j)
				{
					cout<<_matrix[index]._value<<" ";
					index++;
				}
				else
				{
					cout<<_invalid<<" ";
				}
			}
			cout<<endl;
		}
		cout<<endl;
	}
	
	SparseMatrix<T> Transpart()
	{
		SparseMatrix<T> sm;
		sm._m = _n;
		sm._n = _m;
		sm._invalid = _invalid;
		
		for(size_t i = 0;i < _n;i++)
		{
			size_t index = 0;
			
			while(index < _matrix.size())
			{
				if(_matrix[index]._col == i)
				{
					Triple<T> t(_matrix[index]._col,_matrix[index]._row,_matrix[index]._value);
					sm._matrix.push_back(t);
				}
				++index;
			}
		}
		return sm;
	}

	SparseMatrix<T> FastTranspart()
	{
		SparseMatrix<T> sm;
		sm._m = _n;
		sm._n = _m;
		sm._invalid = _invalid;
		sm._matrix.resize(_matrix.size());

		int* count = new int[_n];
		memset(count,0,sizeof(int) * _n);
		int* start = new int[_n];
		size_t index = 0;
		
		//count array
		while(index < _matrix.size())
		{
			int row = _matrix[index]._col;
			//hash
			count[row]++;
			index++;
		}
		//start array
		index = 1;
		start[0] = 0;
		while(index < _n)
		{
			start[index] = start[index-1] + count[index-1];
			index++;
		}

		for(size_t i = 0;i < _matrix.size();i++)
		{
			int row = _matrix[i]._col;
			Triple<T> tmp(_matrix[i]._col,_matrix[i]._row,_matrix[i]._value);
			int begin  = start[row]++;
			sm._matrix[begin] = tmp;
		}

		delete[] count;
		delete[] start;
		return sm;
	}
private:
	vector< Triple<T> > _matrix;
	size_t _m;
	size_t _n;
	T _invalid;
};

void test()
{
	int arr[6][5] = \
	{\
		{1,0,3,0,5},\
		{0,0,0,0,0},\
		{0,0,0,0,0},\
		{2,0,4,0,6},\
		{0,0,0,0,0},\
		{0,0,0,0,0},\
	};
	SparseMatrix<int> s((int *)arr,6,5,0);
	s.Display();
	
	SparseMatrix<int> s2 = s.Transpart();
	s2.Display();
	
	SparseMatrix<int> s3 = s.FastTranspart();
	s3.Display();
}
int main()
{
	test();
	return 0;
}