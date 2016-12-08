#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>
#include <queue>

const int N = 5;	//有n个进程
const int M = 3;	//有m类资源

void InitMatrix(int* MaxMatrix,int* AllMatrix,int n,int m)
{
	FILE* Max = fopen("Max.txt","r");
	FILE* All = fopen("Allocation.txt","r");

	char maxnum = 0;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;)
		{
			maxnum = fgetc(Max);
			
			if (maxnum != ' ' && maxnum != '\n')
			{
				MaxMatrix[i * m + j] = maxnum - '0';
				++j;
			}
		}
	}

	char allnum = 0;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;)
		{
			allnum = fgetc(All);

			if (allnum != ' ' && allnum != '\n')
			{
				AllMatrix[i * m + j] = allnum - '0';
				++j;
			}
		}
	}
}
void Display(int* MaxMatrix,int* AllMatrix,int* NeedMatrix,int n,int m)
{
	cout<<"MaxMtrix:"<<endl;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cout<<MaxMatrix[i * m + j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl<<"AllMatrix:"<<endl;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cout<<AllMatrix[i * m + j]<<" ";
		}
		cout<<endl;
	}

	cout<<endl<<"NeedMatrix:"<<endl;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			NeedMatrix[i * m + j] = MaxMatrix[i * m + j] - AllMatrix[i * m + j];
			cout<<NeedMatrix[i * m + j]<<" ";
		}
		cout<<endl;
	}
}
bool IsFinish(const vector<bool>& finish)
{
	for (int i = 0;i < finish.size();++i)
	{
		if (finish[i] == false)
		{
			return true;
		}
	}

	return false;
}
int GetIndex(const vector<bool>& finish)
{
	for (int i = 0;i < finish.size();++i)
	{
		if (finish[i] == false)
		{
			return i;
		}
	}

	return -1;
}
void SafeSequence(int* AllMatrix,int* NeedMatrix,vector<int>& AvaMatrix,vector<bool>& finish,queue<int>& q)
{
	int i = 0;
	while (IsFinish(finish))
	{
		int j = 0;
		while (j < M)
		{
			//判断各个进程的每类资源是否都小于等于可用资源的每类资源
			if (NeedMatrix[i * M + j] <= AvaMatrix[j])
			{
				++j;
			}
			else
				break;

			//该进程满足可用资源的安全性
			if (j == M)
			{
				int index = 0;
				while(index < M)
				{
					//进程运行完毕需要将占用的已分配资源还给操作系统，可用的每类资源都需要改变
					AvaMatrix[index] += AllMatrix[i * M + index];
					++index;
				}
				//记住进程执行的顺序
				q.push(i);
				//进程运行完毕要标志他运行过，不再和其他进程争用可用资源
				finish[i] = true;
			}
		}
		//一个进程执行完或者一个进程为不安全状态需要阻塞等待换下一个进程继续执行
		++i;
		
		if (i == N || finish[i] == true)
		{
			i = GetIndex(finish);
		}
	}

}
void PrintSafeSequence(vector<int>& AvaMatrix,vector<bool>& finish,queue<int>& q)
{
	cout<<endl<<"资源总数："<<"Ava[";
	for (size_t i = 0;i < AvaMatrix.size();++i)
	{
		cout<<AvaMatrix[i];
		if (i != 2)
		{
			cout<<",";
		}
	}
	cout<<"]"<<endl;
	cout<<"安全序列：";
	while (!q.empty())
	{
		cout<<"P"<<q.front()<<" ";
		q.pop();
	}
	cout<<endl;
}
void test()
{
	int MaxMatrix[N][M] = {0};		//最大需求
	int AllMatrix[N][M] = {0};		//已分配
	int NeedMatrix[N][M] = {0};		//尚需
	vector<int> AvaMatrix(M);			//可用资源
	
	for (int i = 0;i < M;++i)
	{
		cin>>AvaMatrix[i];
	}

	InitMatrix((int*)MaxMatrix,(int*)AllMatrix,N,M);//初始化最大需求数组矩阵和已分配数据矩阵
	Display((int*)MaxMatrix,(int*)AllMatrix,(int*)NeedMatrix,N,M);//求得需求数组矩阵并且打印最大需求、已分配，尚需数组矩阵

	vector<bool> finish(N,false);//安全性检测数组
	queue<int> q;//记录安全序列
	SafeSequence((int*)AllMatrix,(int*)NeedMatrix,AvaMatrix,finish,q);
	PrintSafeSequence(AvaMatrix,finish,q);
}

int main()
{
	test();
	system("pause");
	return 0;
}