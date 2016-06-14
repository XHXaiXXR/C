#define _CRT_SECURE_NO_WARNINGS 1

#include "RevolveArray.h"

void test1()
{
	//int arr[] = {1,2,3,4,5};
	int arr[] = {8,3,7,2,0};	
	int size = sizeof(arr)/sizeof(arr[0]);
	int count = 0;
	cout<<"请输入需要旋转数组的个数"<<endl;
	cin>>count;
	int min = RevolveArray<int>(arr,size,count);
	
	for (int i = 0;i < size;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl<<"min = "<<min<<endl;
}



int main()
{
	test1();
	system("pause");
	return 0;
}