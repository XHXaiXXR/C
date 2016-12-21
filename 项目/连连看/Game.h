#pragma once

#include "Function.h"

void Game()
{
	const int ROW = 4;//游戏界面的行
	const int COL = 4;//游戏界面的列
	int gamedata[ROW][COL] = {{0}};//游戏数组初始化

	InitGameData((int*)gamedata,ROW,COL);
	
	int x1 = 0,y1 = 0,x2 = 0,y2 = 0;
	int count = 3;//有三次交换已有数组的机会

	//死循环刷新游戏 
	while (1)
	{
		//显示游戏桌面
		DisplayGameView((int*)gamedata,ROW,COL);

		//当没办法在现有的游戏界面上消除时的解决方法
		int num;
		if (count)
		{
			printf("你还有%d次机会刷新游戏，是否刷新？\n",count);
			printf("         1.是      0.否           \n");
			printf("请输入：");
			cin>>num;
			if (num == 1)
			{
				count--;
				Refresh((int* )gamedata,ROW,COL);
				continue;
			}
		}

		//用户输入坐标
		cout<<endl<<"提示：x为横坐标，y为纵坐标，坐标从左到右，从上到下，从1开始递增"<<endl<<endl;//从1开始符合人的思维
		cout<<"请输入两个坐标(x1,y1),(x2,y2):";
		cin>>x1>>y1>>x2>>y2;

		if (x1 > COL|| y1 > ROW|| x2 > COL|| y2 > ROW)
		{
			continue;
		}

		//减一已达到满足数组从0开始的特性
		int newx1 = x1 - 1;
		int newy1 = y1 - 1;
		int newx2 = x2 - 1;
		int newy2 = y2 - 1;

		if (CanClear((int*) gamedata,newx1,newy1,newx2,newy2,ROW,COL))
		{
			gamedata[newy1][newx1] = 0;
			gamedata[newy2][newx2] = 0;
		}

		//检查是否全部消除完毕
		if(CheckSucceed((int*) gamedata,ROW,COL))
		{
			DisplayGameView((int*)gamedata,ROW,COL);
			cout<<"恭喜你成功消除了所有的障碍"<<endl;
			return;
		}
	}
}