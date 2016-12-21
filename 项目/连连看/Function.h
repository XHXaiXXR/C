#pragma once

#include <stdlib.h>
#include <time.h>

void InitGameData(int* gamedata,int row,int col)
{
	//连连看的游戏数组中，数据都是成对出现的，不会出现单独的一个数字
	
	//1.生成成对的数据，依次放在游戏数组中
	int num = 0;
	for (int i = 0;i < row;++i)
	{
		for (int j = 0;j < col;++j)
		{
			gamedata[i * col + j] = num / 2 + 1;//依次生成从1递增的成对数字
			++num;
		}
	}

	//2.随机打乱数组里面的数据
	srand((unsigned)time(NULL));	//使用当前的系统时间作为随机数种子
	for (int count = 0;count < (row * col) / 2;++count)
	{
		int x1 = rand() % col;	//生成 0 -- (col - 1) 的数据
		int y1 = rand() % row;	//生成 0 -- (row - 1) 的数据
		int x2 = rand() % col;	//生成 0 -- (col - 1) 的数据
		int y2 = rand() % row;	//生成 0 -- (row - 1) 的数据

		swap(gamedata[y1 * col + x1],gamedata[y2 * col + x2]);
	}
}

void DisplayGameView(int* gamedata,int row,int col)
{
	system("cls");//执行系统清屏命令，但是这种办法的缺点是程序额外运行系统程序执行清屏操作，延长了程序执行时间。

	//打印标题
	printf("**************************************\n");
	printf("                                      \n");
	printf("               连连看游戏             \n");
	printf("                                      \n");	
	printf("             设计者：萧海霞           \n");
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
	//如果在同一行上 Y相等
	if (y1 == y2)
	{
		int y = y1;
		//sum用于遍历两个坐标之间路径的值，由于消除数据的坐标程序已经置成0，所以当sum==0时，两个坐标的数据才能消除
		int sum = 0;

		//保证x1一定小于等于x2
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
	//如果在同一列上 X相等
	if(x1 == x2)
	{
		int x = x1;
		//sum用于遍历两个坐标之间路径的值，由于消除数据的坐标程序已经置成0，所以当sum==0时，两个坐标的数据才能消除
		int sum = 0;

		//保证x1一定小于等于x2
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
	//通过中间值，下标为[y1][x2]
	if (ConnectZero(gamedata,x1,y1,x2,y1,row,col)&&
		ConnectZero(gamedata,x1,y1,x1,y2,row,col)&&
		gamedata[y1 * col + x2] == 0)
	{
		return true;
	}
	//通过中间值，下标为[y2][x1]
	if (ConnectZero(gamedata,x1,y1,x1,y2,row,col)&&
		ConnectZero(gamedata,x1,y2,x2,y2,row,col)&&
		gamedata[y2 * col + x2] == 0)
	{
		return true;
	}
}

bool CanClear(int* gamedata,int x1,int y1,int x2,int y2,int row,int col)
{
	//1.如果用户所给我两个下标相同，则不能消除
	if (x1 == x2 && y1 == y2)
	{
		return false;
	}

	//2.如果用户所给的两个坐标所对应的值不相同，则不能消除
	if (gamedata[y1 * col + x1] != gamedata[y2 * col + x2])
	{
		return false;
	}

	//3.如果可以不转弯就连通
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
	//随机打乱数组里面的数据
	srand((unsigned)time(NULL));	//使用当前的系统时间作为随机数种子
	for (int count = 0;count < (row * col) / 2;++count)
	{
		int x1 = rand() % col;	//生成 0 -- (col - 1) 的数据
		int y1 = rand() % row;	//生成 0 -- (row - 1) 的数据
		int x2 = rand() % col;	//生成 0 -- (col - 1) 的数据
		int y2 = rand() % row;	//生成 0 -- (row - 1) 的数据

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

 

