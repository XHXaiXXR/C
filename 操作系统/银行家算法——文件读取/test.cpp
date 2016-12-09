#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>
#include <queue>

const int N = 5;	//��n������
const int M = 3;	//��m����Դ

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
			//�жϸ������̵�ÿ����Դ�Ƿ�С�ڵ��ڿ�����Դ��ÿ����Դ
			if (NeedMatrix[i * M + j] <= AvaMatrix[j])
			{
				++j;
			}
			else
				break;

			//�ý������������Դ�İ�ȫ��
			if (j == M)
			{
				int index = 0;
				while(index < M)
				{
					//�������������Ҫ��ռ�õ��ѷ�����Դ��������ϵͳ�����õ�ÿ����Դ����Ҫ�ı�
					AvaMatrix[index] += AllMatrix[i * M + index];
					++index;
				}
				//��ס����ִ�е�˳��
				q.push(i);
				//�����������Ҫ��־�����й������ٺ������������ÿ�����Դ
				finish[i] = true;
			}
		}
		//һ������ִ�������һ������Ϊ����ȫ״̬��Ҫ�����ȴ�����һ�����̼���ִ��
		++i;
		
		if (i == N || finish[i] == true)
		{
			i = GetIndex(finish);
		}
	}

}
void PrintSafeSequence(vector<int>& AvaMatrix,vector<bool>& finish,queue<int>& q)
{
	cout<<endl<<"��Դ������"<<"Ava[";
	for (size_t i = 0;i < AvaMatrix.size();++i)
	{
		cout<<AvaMatrix[i];
		if (i != 2)
		{
			cout<<",";
		}
	}
	cout<<"]"<<endl;
	cout<<"��ȫ���У�";
	while (!q.empty())
	{
		cout<<"P"<<q.front()<<" ";
		q.pop();
	}
	cout<<endl;
}
void test()
{
	int MaxMatrix[N][M] = {0};		//�������
	int AllMatrix[N][M] = {0};		//�ѷ���
	int NeedMatrix[N][M] = {0};		//����
	vector<int> AvaMatrix(M);			//������Դ
	
	for (int i = 0;i < M;++i)
	{
		cin>>AvaMatrix[i];
	}

	InitMatrix((int*)MaxMatrix,(int*)AllMatrix,N,M);//��ʼ������������������ѷ������ݾ���
	Display((int*)MaxMatrix,(int*)AllMatrix,(int*)NeedMatrix,N,M);//���������������Ҵ�ӡ��������ѷ��䣬�����������

	vector<bool> finish(N,false);//��ȫ�Լ������
	queue<int> q;//��¼��ȫ����
	SafeSequence((int*)AllMatrix,(int*)NeedMatrix,AvaMatrix,finish,q);
	PrintSafeSequence(AvaMatrix,finish,q);
}

int main()
{
	test();
	system("pause");
	return 0;
}