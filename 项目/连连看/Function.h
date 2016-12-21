#pragma once

#include <stdlib.h>
#include <time.h>

void InitGameData(int* gamedata,int row,int col)
{
	//����������Ϸ�����У����ݶ��ǳɶԳ��ֵģ�������ֵ�����һ������
	
	//1.���ɳɶԵ����ݣ����η�����Ϸ������
	int num = 0;
	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;++j)
		{
			gamedata[i * col + j] = num / 2 + 1;//�������ɴ�1�����ĳɶ�����
			++num;
		}
	}

	//2.��������������������
	srand((unsigned)time(NULL));	//ʹ�õ�ǰ��ϵͳʱ����Ϊ���������
	for (int count = 0;count < (row * col) / 2;++count)
	{
		int x1 = rand() % col;	//���� 0 -- (col - 1) ������
		int y1 = rand() % row;	//���� 0 -- (row - 1) ������
		int x2 = rand() % col;	//���� 0 -- (col - 1) ������
		int y2 = rand() % row;	//���� 0 -- (row - 1) ������

		swap(gamedata[y1 * col + x1],gamedata[y2 * col + x2]);
	}
}

void DisplayGameView(int* gamedata,int row,int col)
{
	system("cls");//ִ��ϵͳ��������������ְ취��ȱ���ǳ����������ϵͳ����ִ�������������ӳ��˳���ִ��ʱ�䡣

	//��ӡ����
	printf("**************************************\n");
	printf("                                      \n");
	printf("               ��������Ϸ             \n");
	printf("                                      \n");	
	printf("             ����ߣ�����ϼ           \n");
	printf("                                      \n");	
	printf("**************************************\n");	

	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;j++)
		{
			if (gamedata[i * col + j] == 0)
			{
				printf("       ");
			} 
			else
			{
				printf("%7d",gamedata[i * col + j]);
			}
		}
		cout<<endl;
	}
}
bool ConnectZero(int* gamedata,int x1,int y1,int x2,int y2,int row,int col)
{
	//�����ͬһ���� Y���
	if (y1 == y2)
	{
		int y = y1;
		//sum���ڱ�����������֮��·����ֵ�������������ݵ���������Ѿ��ó�0�����Ե�sum==0ʱ��������������ݲ�������
		int sum = 0;

		//��֤x1һ��С�ڵ���x2
		if (x1 > x2)
		{
			swap(x1,x2);
		}

		for (int x = x1 + 1;x < x2;++x)
		{
			sum += gamedata[y * col + x];
		}

		if (sum == 0)
		{
			return true;
		}
	}
	//�����ͬһ���� X���
	if(x1 == x2)
	{
		int x = x1;
		//sum���ڱ�����������֮��·����ֵ�������������ݵ���������Ѿ��ó�0�����Ե�sum==0ʱ��������������ݲ�������
		int sum = 0;

		//��֤x1һ��С�ڵ���x2
		if (y1 > y2)
		{
			swap(y1,y2);
		}

		for (int y = y1 + 1;y < y2;++y)
		{
			sum += gamedata[y * col + x];
		}

		if (sum == 0)
		{
			return true;
		}
	}

	return false;
}
bool ConnectOne(int* gamedata,int x1,int y1,int x2,int y2,int row,int col)
{
	//ͨ���м�ֵ���±�Ϊ[y1][x2]
	if (ConnectZero(gamedata,x1,y1,x2,y1,row,col)&&
		ConnectZero(gamedata,x1,y1,x1,y2,row,col)&&
		gamedata[y1 * col + x2] == 0)
	{
		return true;
	}
	//ͨ���м�ֵ���±�Ϊ[y2][x1]
	if (ConnectZero(gamedata,x1,y1,x1,y2,row,col)&&
		ConnectZero(gamedata,x1,y2,x2,y2,row,col)&&
		gamedata[y2 * col + x2] == 0)
	{
		return true;
	}
}

bool CanClear(int* gamedata,int x1,int y1,int x2,int y2,int row,int col)
{
	//1.����û������������±���ͬ����������
	if (x1 == x2 && y1 == y2)
	{
		return false;
	}

	//2.����û�������������������Ӧ��ֵ����ͬ����������
	if (gamedata[y1 * col + x1] != gamedata[y2 * col + x2])
	{
		return false;
	}

	//3.������Բ�ת�����ͨ
	if (ConnectZero(gamedata,x1,y1,x2,y2,row,col))
	{
		return true;
	}
	if (ConnectOne(gamedata,x1,y1,x2,y2,row,col))
	{
		return true;
	}
}

void Refresh(int* gamedata,int row,int col)
{
	//��������������������
	srand((unsigned)time(NULL));	//ʹ�õ�ǰ��ϵͳʱ����Ϊ���������
	for (int count = 0;count < (row * col) / 2;++count)
	{
		int x1 = rand() % col;	//���� 0 -- (col - 1) ������
		int y1 = rand() % row;	//���� 0 -- (row - 1) ������
		int x2 = rand() % col;	//���� 0 -- (col - 1) ������
		int y2 = rand() % row;	//���� 0 -- (row - 1) ������

		swap(gamedata[y1 * col + x1],gamedata[y2 * col + x2]);
	}
}

bool CheckSucceed(int* gamedata,int row,int col)
{
	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;++j)
		{
			if (gamedata[i * col + j] != 0)
			{
				return false;
			}
		}
	}

	return true;
}

 

