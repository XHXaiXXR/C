#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#define N 1000
#define K 20

//���µ���
void AdjustDown(int* a,size_t size,int parent)
{
	int child = 2 * parent + 1;
	while (child < size)
	{
		//����С��
		if (((child + 1) < size)
			&&(a[child+1] < a[child]))
		{
			child++;
		}

		if (a[child] < a[parent])
		{
			swap(a[child],a[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}

void GetTopK(int* arr,int* topk,int n,int k)
{
	for (size_t i = 0;i < k;i++)
	{
		topk[i] = arr[i];
	}
	//��Ҷ�ӽڵ����µ���
	for (int i = (k-2)/2;i >= 0;i--)
	{
		//topk����
		AdjustDown(topk,k,i);
	}
	for (size_t i = k;i < n;i++)
	{
		if (arr[i] > topk[0])
		{
			topk[0] = arr[i];
			AdjustDown(topk,k,0);
		}
	}
}

void Test()
{
	//��1000�������ҳ�����ǰ20����
	int arr[N] = {0};//��ʼ������
	int topk[K] = {0};

	for (size_t i = 0;i < N;i++)
	{
		arr[i] = i;
	}
	arr[50] = 2542;
	arr[100] = 3415;
	arr[150] = 4685;
	arr[200] = 1185;

	GetTopK(arr,topk,N,K);

	for (size_t i = 0;i < K;i++)
	{
		cout<<topk[i]<<" ";
	}
	cout<<endl;
}

int main()
{
	Test();
	system("pause");
	return 0;
}

