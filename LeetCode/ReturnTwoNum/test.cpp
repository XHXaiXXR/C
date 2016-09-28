#include<iostream>
using namespace std;
#include<vector>

vector<int> IsTarget(int* arr,int size,int target)
{
	vector<int> tmp;

	for(size_t i = 0;i < size;i++)
	{
		int first = arr[i];
		for(size_t j = i + 1;j < size;j++)
		{
			int second = arr[j];
			
			if(first + second == target)
			{
				tmp.push_back(i);
				tmp.push_back(j);
				return tmp;
			}
		}
	}

	tmp.push_back(-1);
	tmp.push_back(-1);
	return tmp;
}
void test()
{
	int arr[] = {2,7,11,15};
	int size = sizeof(arr)/sizeof(arr[0]);
	int target = 9;
	vector<int> tmp = IsTarget(arr,size,target);
	
	cout<<"arr[] = {";
	for(size_t i = 0;i < size;i++)
	{
		if(i < size-1)
		{
			cout<<arr[i]<<",";
		}
		else
		{
			cout<<arr[i]<<"}"<<endl;
		}
	}
	cout<<"target = "<<target<<endl;
	if(tmp[0] != -1)
	{
		cout<<tmp[0]<<" "<<tmp[1]<<endl;
	}
}
int main()
{
	test();
	return 0;
}