#include<iostream>
using namespace std;
#include<assert.h>
#include<stack>

bool IsLegalOrder(int* arr1,int size1,int* arr2,int size2)
{
	assert(arr1);
	assert(arr2);
 	stack<int> s;
	int j = 0;

	for(int i = 0;i < size1;i++)
	{
		if(arr1[i] != arr2[j])
		{
			s.push(arr1[i]);
		}
		else
		{
			j++;
		}

		while(!s.empty() && s.top() == arr2[j])
		{
			s.pop();
			j++;
		}
	}

	if(j == size2)
	{
		return true;
	}
	return false;
}
void test()
{
	int arr1[] = {1,2,3,4,5};
	size_t size1 = sizeof(arr1)/sizeof(arr1[0]);
	//int arr2[] = {4,5,3,2,1};  //yes
	//int arr2[] = {2,4,5,3,1};  //yes
	//int arr2[] = {5,4,3,2,1};  //yes
	int arr2[] = {1,2,5,3,4};  //no
	size_t size2 = sizeof(arr2)/sizeof(arr2[0]);

	bool ret = IsLegalOrder(arr1,size1,arr2,size2);

	if(ret)
	{
		cout<<"yes"<<endl;
	}
	else
	{
		cout<<"no"<<endl;
	}
}
int main()
{
	test();
	return 0;
}