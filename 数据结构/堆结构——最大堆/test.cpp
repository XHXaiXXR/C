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
		
		//数组建堆
		for(int i = (_arr.size()-2)/2;i >= 0;--i)
		{
			AdjustDown(i);
		}
	}

	void Push(const T& data)
	{
		_arr.push_back(data);
		AdjustUp(_arr.size()-1);
	}
	//pop掉堆顶的数据
	void Pop()
	{
		//先使堆顶数据和最后一个数据交换，然后吧最后一个数据pop掉
		swap(_arr[0],_arr[_arr.size()-1]);
		_arr.pop_back();

		//原先的最后一个数据调至堆顶，然后除堆顶外左右子树还是满足大堆
		//所以此时只需要将堆顶的数据向下调整
		AdjustDown(0);

	}
	void Display()
	{
		for(size_t i = 0;i < _arr.size();i++)
		{
			cout<<_arr[i]<<" ";
		}
		cout<<endl;
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
	void AdjustUp(size_t root)
	{
		size_t child = root;
		size_t parent = (child-1)/2;

		while(parent >= 0)
		{
			if(_arr[child] > _arr[parent])
			{
				swap(_arr[child],_arr[parent]);
				child = parent;
				parent = (child-1)/2;
			}
			else
			{
				break;
			}
		}
	}
	size_t Size()
	{
		return _arr.size();
	}
	bool Empty()
	{
		return _arr.empty();
	}
	const T& Top()
	{
		return _arr[0];
	}
private:
	vector<T> _arr;
};

void test()
{
	int arr[] = {10,11,13,12,16,18,15,17,14,19};
	int size = sizeof(arr)/sizeof(arr[0]);

	Heap<int> hp(arr,size);
	hp.Display();

	hp.Push(20);
	hp.Display();

	hp.Pop();
	hp.Display();

	cout<<"size = "<<hp.Size()<<endl;
	cout<<"empty ? "<<hp.Empty()<<endl;
	cout<<"top = "<<hp.Top()<<endl;
}
int main()
{
	test();
	return 0;
}