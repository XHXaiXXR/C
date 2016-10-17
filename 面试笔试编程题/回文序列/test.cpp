#include<iostream>
using namespace std;

int comb(int* nums,int start,int end)
{
	int count = 0;
	int left = nums[start];
	int right = nums[end];

	while(start < end && left != right)
	{
		if(left < right)
		{
			left += nums[++start];
			count++;
		}
		else
		{
			right += nums[--end];
			count++;
		}
	}
	if(start > end)
	{
		return count;
	}
	else
	{
		return count += comb(nums,++start,--end);
	}
}
void test()
{
	int n = 0;
	int nums[50] = {0};
	
	cin>>n;
	for(int i = 0;i < n;i++)
	{
		cin>>nums[i];
	}

	cout<<comb(nums,0,n-1)<<endl;
}
int main()
{
	test();
	return  0;
}