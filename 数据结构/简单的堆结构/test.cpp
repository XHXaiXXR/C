#include<iostream>
using namespace std;
#include<vector>

template<class T>
class Heap
{
public:
	Heap(T* arr,size_t size)
	{
		_arr.reserve(size);

		for(size_t i = 0;i < size;i++)
		{
			_arr.push_back(arr[i]);
		}

		//Êý×é½¨¶Ñ
		for(int i = (_arr.size()-2)/2;i >= 0;--i)
		{
			AdjustDown(i);
		}
	}

	void AdjustDown(size_t root)
	{
		size_t parent = root;
		size_t child = 2 * parent + 1;

		while(child < _arr.size())
		{
			if(child + 1 < _arr.size()\
				&& _arr[child + 1] > _arr[child])
			{
				++child;
			}

			if(_arr[child] > _arr[parent])
			{
				swap(_arr[child],_arr[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _arr;
};

void test()
{
	int arr[] = {10,11,13,12,16,18,15,17,14,19};
	int size = sizeof(arr)/sizeof(arr[0]);

	Heap<int> hp(arr,size);

	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}