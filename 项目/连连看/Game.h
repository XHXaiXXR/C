#pragma once

#include "Function.h"

void Game()
{
	const int ROW = 4;//��Ϸ�������
	const int COL = 4;//��Ϸ�������
	int gamedata[ROW][COL] = {{0}};//��Ϸ�����ʼ��

	InitGameData((int*)gamedata,ROW,COL);
	
	int x1 = 0,y1 = 0,x2 = 0,y2 = 0;
	int count = 3;//�����ν�����������Ļ���

	//��ѭ��ˢ����Ϸ 
	while (1)
	{
		//��ʾ��Ϸ����
		DisplayGameView((int*)gamedata,ROW,COL);

		//��û�취�����е���Ϸ����������ʱ�Ľ������
		int num;
		if (count)
		{
			printf("�㻹��%d�λ���ˢ����Ϸ���Ƿ�ˢ�£�\n",count);
			printf("         1.��      0.��           \n");
			printf("�����룺");
			cin>>num;
			if (num == 1)
			{
				count--;
				Refresh((int* )gamedata,ROW,COL);
				continue;
			}
		}

		//�û���������
		cout<<endl<<"��ʾ��xΪ�����꣬yΪ�����꣬��������ң����ϵ��£���1��ʼ����"<<endl<<endl;//��1��ʼ�����˵�˼ά
		cout<<"��������������(x1,y1),(x2,y2):";
		cin>>x1>>y1>>x2>>y2;

		if (x1 > COL|| y1 > ROW|| x2 > COL|| y2 > ROW)
		{
			continue;
		}

		//��һ�Ѵﵽ���������0��ʼ������
		int newx1 = x1 - 1;
		int newy1 = y1 - 1;
		int newx2 = x2 - 1;
		int newy2 = y2 - 1;

		if (CanClear((int*) gamedata,newx1,newy1,newx2,newy2,ROW,COL))
		{
			gamedata[newy1][newx1] = 0;
			gamedata[newy2][newx2] = 0;
		}

		//����Ƿ�ȫ���������
		if(CheckSucceed((int*) gamedata,ROW,COL))
		{
			DisplayGameView((int*)gamedata,ROW,COL);
			cout<<"��ϲ��ɹ����������е��ϰ�"<<endl;
			return;
		}
	}
}