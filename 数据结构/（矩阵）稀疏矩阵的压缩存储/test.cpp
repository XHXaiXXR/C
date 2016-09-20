#include<iostream>
using namespace std;
#include<vector>

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
}
int main()
{
	test();
	return 0;
}