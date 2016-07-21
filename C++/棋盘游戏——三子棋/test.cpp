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
		cout<<"请选择：>"<<endl;
		cin>>input;
		switch (input)
		{
		case BEGIN:
			game(board);
			break;
		case EXIT:
			exit(0);//正常退出为0，错误退出为1
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