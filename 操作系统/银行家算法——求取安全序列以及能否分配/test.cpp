#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>
#define MAX 50

int MaxMatrix[MAX][MAX] = {{0}};		//最大需求
int AllMatrix[MAX][MAX] = {{0}};		//已分配
int NeedMatrix[MAX][MAX] = {{0}};		//尚需
//存储一份原先的数据
int newNeedMatrix[MAX][MAX] = {{0}};		//尚需

void InitMatrix(int n,int m)
{
	cout<<"请输入最大需求矩阵"<<endl;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cin>>MaxMatrix[i][j];
		}
	}
	cout<<"请输入已分配矩阵"<<endl;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cin>>AllMatrix[i][j];
		}
	}
}
void Display(int n,int m)
{
	cout<<"MaxMtrix:"<<endl;//最大需求矩阵
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cout<<MaxMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"AllMatrix:"<<endl;//已分配矩阵
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cout<<AllMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"NeedMatrix:"<<endl;//需求矩阵
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			NeedMatrix[i][j] = MaxMatrix[i][j] - AllMatrix[i][j];
			cout<<NeedMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
}
bool IsSafe(vector<int> AvaMatrix,vector<bool>finish,int& index,int n,int m)
{
	int pidnum = n;
	while (pidnum--)
	{
		if (finish[pidnum] == true)
		{
			continue;
		}
		int count = 0;
		for (int i = 0;i < m;++i)
		{
			if (NeedMatrix[pidnum][i] <= AvaMatrix[i])
			{
				++count;
			}
			if (count == m)
			{
				index = pidnum;
				return true;
			}
		}
	}
	return false;
}
bool CheckFinish(const vector<bool>& finish,int n)
{
	for(int i = 0;i < n;++i)
	{
		if (finish[i] == false)
		{
			return false;
		}
	}
	return true;
}
void SafeSequence(vector<int>& AvaMatrix,vector<bool>& finish,vector<int>& q,int n,int m)
{
	int i = 0;
	while (IsSafe(AvaMatrix,finish,i,n,m))
	{
		for (int index = 0;index < m;++index)
		{
			//进程运行完毕需要将占用的已分配资源还给操作系统，可用的每类资源都需要改变
			AvaMatrix[index] += AllMatrix[i][index];
		}
		q.push_back(i);		//记住进程执行的顺序
		finish[i] = true;	////进程运行完毕要标志他运行过，不再和其他进程争用可用资源
	}
	//跳出循环有两种可能
	//一种是安全序列全部求出
	//还有一种可能是状态不安全
}
void PrintSafeSequence(vector<int>& AvaMatrix,vector<bool>& finish,vector<int>& q)
{
	cout<<endl<<"资源总数："<<"Ava[";
	for (size_t i = 0;i < AvaMatrix.size();++i)
	{
		cout<<AvaMatrix[i];
		if (i != (AvaMatrix.size() - 1))
		{
			cout<<",";
		}
	}
	cout<<"]"<<endl;
	cout<<"安全序列：";
	for(size_t i = 0;i < q.size();++i)
	{
		cout<<"P"<<(q[i] + 1)<<" ";
	}
	cout<<endl;
}
void Ask(vector<int> newAvaMatrix,int n,int m)
{
	int num = 0;
	cout<<"是否需要请求资源?"<<endl<<"1.需要	0.不需要"<<endl;
	cin>>num;
	if (num == 1)
	{
		int pid = 0;
		cout<<"几号进程还需要申请资源：";
		cin>>pid;	//用户输入1相当于数组的0下标
		--pid;

		vector<int> ask(m,0);
		cout<<"还需申请资源：";
		for (int i = 0;i < m;++i)
		{
			cin>>ask[i];
		}

		for (int i = 0;i < m;++i)
		{
			AllMatrix[pid][i] += ask[i];	//申请资源，已分配的资源相应的增加一定的数
			NeedMatrix[pid][i] -= ask[i];	//由于多申请资源所以需求数组对应的值会减少
			newAvaMatrix[i] -= ask[i];			//多申请资源那么可用资源自然需要减少
		}

		for (int i = 0;i < m;++i)
		{
			if (newAvaMatrix[i] < 0)
			{
				cout<<"不能分配，分配后状态不安全不安全"<<endl;
				return;
			}
		}

		vector<bool> newfinish(n,false);//安全性检测数组
		vector<int> newq;//记录安全序列
		SafeSequence(newAvaMatrix,newfinish,newq,n,m);
		if (!CheckFinish(newfinish,n))
			cout<<"序列不安全"<<endl;
		else
			PrintSafeSequence(newAvaMatrix,newfinish,newq);
	}
}
void test()
{
	cout<<"有多少个进程："<<endl;
	int N = 0;
	cin>>N;
	cout<<"有多少类资源:"<<endl;
	int M = 0;
	cin>>M;
	cout<<"输入可用资源:"<<endl;
	vector<int> AvaMatrix(M);			//可用资源
	for (int i = 0;i < M;++i)
	{
		cin>>AvaMatrix[i];
	}
	vector<int> newAvaMatrix(AvaMatrix);			//可用资源

	InitMatrix(N,M);//初始化最大需求数组矩阵和已分配数据矩阵
	Display(N,M);//求得需求数组矩阵并且打印最大需求、已分配，尚需数组矩阵

	vector<bool> finish(N,false);//安全性检测数组
	vector<int> q;//记录安全序列
	SafeSequence(AvaMatrix,finish,q,N,M);
	if (!CheckFinish(finish,N))
		cout<<"序列不安全"<<endl;
	else
		PrintSafeSequence(AvaMatrix,finish,q);

	//是否需要分配
	Ask(newAvaMatrix,N,M);
}

int main()
{
	test();
	system("pause");
	return 0;
}