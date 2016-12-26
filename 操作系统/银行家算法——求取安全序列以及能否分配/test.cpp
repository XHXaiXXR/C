#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>
#define MAX 50

int MaxMatrix[MAX][MAX] = {{0}};		//�������
int AllMatrix[MAX][MAX] = {{0}};		//�ѷ���
int NeedMatrix[MAX][MAX] = {{0}};		//����
//�洢һ��ԭ�ȵ�����
int newNeedMatrix[MAX][MAX] = {{0}};		//����

void InitMatrix(int n,int m)
{
	cout<<"����������������"<<endl;
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cin>>MaxMatrix[i][j];
		}
	}
	cout<<"�������ѷ������"<<endl;
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
	cout<<"MaxMtrix:"<<endl;//����������
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cout<<MaxMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"AllMatrix:"<<endl;//�ѷ������
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < m;++j)
		{
			cout<<AllMatrix[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"NeedMatrix:"<<endl;//�������
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
			//�������������Ҫ��ռ�õ��ѷ�����Դ��������ϵͳ�����õ�ÿ����Դ����Ҫ�ı�
			AvaMatrix[index] += AllMatrix[i][index];
		}
		q.push_back(i);		//��ס����ִ�е�˳��
		finish[i] = true;	////�����������Ҫ��־�����й������ٺ������������ÿ�����Դ
	}
	//����ѭ�������ֿ���
	//һ���ǰ�ȫ����ȫ�����
	//����һ�ֿ�����״̬����ȫ
}
void PrintSafeSequence(vector<int>& AvaMatrix,vector<bool>& finish,vector<int>& q)
{
	cout<<endl<<"��Դ������"<<"Ava[";
	for (size_t i = 0;i < AvaMatrix.size();++i)
	{
		cout<<AvaMatrix[i];
		if (i != (AvaMatrix.size() - 1))
		{
			cout<<",";
		}
	}
	cout<<"]"<<endl;
	cout<<"��ȫ���У�";
	for(size_t i = 0;i < q.size();++i)
	{
		cout<<"P"<<(q[i] + 1)<<" ";
	}
	cout<<endl;
}
void Ask(vector<int> newAvaMatrix,int n,int m)
{
	int num = 0;
	cout<<"�Ƿ���Ҫ������Դ?"<<endl<<"1.��Ҫ	0.����Ҫ"<<endl;
	cin>>num;
	if (num == 1)
	{
		int pid = 0;
		cout<<"���Ž��̻���Ҫ������Դ��";
		cin>>pid;	//�û�����1�൱�������0�±�
		--pid;

		vector<int> ask(m,0);
		cout<<"����������Դ��";
		for (int i = 0;i < m;++i)
		{
			cin>>ask[i];
		}

		for (int i = 0;i < m;++i)
		{
			AllMatrix[pid][i] += ask[i];	//������Դ���ѷ������Դ��Ӧ������һ������
			NeedMatrix[pid][i] -= ask[i];	//���ڶ�������Դ�������������Ӧ��ֵ�����
			newAvaMatrix[i] -= ask[i];			//��������Դ��ô������Դ��Ȼ��Ҫ����
		}

		for (int i = 0;i < m;++i)
		{
			if (newAvaMatrix[i] < 0)
			{
				cout<<"���ܷ��䣬�����״̬����ȫ����ȫ"<<endl;
				return;
			}
		}

		vector<bool> newfinish(n,false);//��ȫ�Լ������
		vector<int> newq;//��¼��ȫ����
		SafeSequence(newAvaMatrix,newfinish,newq,n,m);
		if (!CheckFinish(newfinish,n))
			cout<<"���в���ȫ"<<endl;
		else
			PrintSafeSequence(newAvaMatrix,newfinish,newq);
	}
}
void test()
{
	cout<<"�ж��ٸ����̣�"<<endl;
	int N = 0;
	cin>>N;
	cout<<"�ж�������Դ:"<<endl;
	int M = 0;
	cin>>M;
	cout<<"���������Դ:"<<endl;
	vector<int> AvaMatrix(M);			//������Դ
	for (int i = 0;i < M;++i)
	{
		cin>>AvaMatrix[i];
	}
	vector<int> newAvaMatrix(AvaMatrix);			//������Դ

	InitMatrix(N,M);//��ʼ������������������ѷ������ݾ���
	Display(N,M);//���������������Ҵ�ӡ��������ѷ��䣬�����������

	vector<bool> finish(N,false);//��ȫ�Լ������
	vector<int> q;//��¼��ȫ����
	SafeSequence(AvaMatrix,finish,q,N,M);
	if (!CheckFinish(finish,N))
		cout<<"���в���ȫ"<<endl;
	else
		PrintSafeSequence(AvaMatrix,finish,q);

	//�Ƿ���Ҫ����
	Ask(newAvaMatrix,N,M);
}

int main()
{
	test();
	system("pause");
	return 0;
}