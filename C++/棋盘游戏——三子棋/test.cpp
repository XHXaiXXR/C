#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <stdlib.h>
#include "board.h"

void test()
{
	char board[ROWS][COLS] = {0};
	int input = 1;
	while (input)
	{
		init_board(board);
		show();
		cout<<"��ѡ��>"<<endl;
		cin>>input;
		switch (input)
		{
		case BEGIN:
			game(board);
			break;
		case EXIT:
			exit(0);//�����˳�Ϊ0�������˳�Ϊ1
			break;
		}
	}

}

int main()
{
	test();
	system("pause");
	return 0;
}