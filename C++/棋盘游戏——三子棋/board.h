#pragma once
#define ROWS 3
#define COLS 3

enum op
{
	EXIT = 0,
	BEGIN
};

void show()
{
	cout<<"********************"<<endl;
	cout<<"*******1.开始*******"<<endl;
	cout<<"*******0.退出*******"<<endl;
	cout<<"********************"<<endl;

}
void init_board(char board[ROWS][COLS])
{
	for (int i = 0;i < ROWS;i++)
	{
		for (int j = 0;j < COLS;j++)
		{
			board[i][j] = ' ';
		}
	}
}
void print_board(char board[ROWS][COLS])
{
	int i = 0;
	for (;i < ROWS;i++)
	{
		cout<<" "<<board[i][0]<<" | "<<board[i][1]<<" | "<<board[i][2]<<" "<<endl;;
		if (i != 2)
		{
			cout<<"---|---|---"<<endl;;
		}
	}
}
bool check_coord(char board[ROWS][COLS],int x,int y)
{
	return (board[x][y] == ' ')
		&& (x >= 0 && x <= 2)
		&& (y >= 0 && y <= 2);
}
void play_move(char board[ROWS][COLS])
{
	int x = 0;
	int y = 0;
	cout<<"请输入坐标：>"<<endl;
	cin>>x;
	cin>>y;
	x--;
	y--;
	if (check_coord(board,x,y))
	{
		board[x][y] = '*';
	}
	else
	{
		cout<<"请重新输入"<<endl;
		play_move(board);
	}
}
void computer_move(char board[ROWS][COLS])
{
	int x = 0;
	int y = 0;
	x = rand()%3;//0 1 2
	y = rand()%3;//0 1 2

	if (check_coord(board,x,y))
	{
		board[x][y] = '@';
	}
	else
	{
		computer_move(board);
	}
}
char check_min(char board[ROWS][COLS])
{
	int i = 0;
	for (;i < ROWS;i++)//横行
	{
		if ((board[i][0] == board[i][1])
			&&(board[i][1] == board[i][2])
			&&(board[i][0] != ' '))
		{
			return board[i][1];
		}
	}

	for (i = 0;i < COLS;i++)
	{
		if ((board[0][i] == board[1][i])
			&&(board[1][i] == board[2][i])
			&&(board[1][i] != ' '))
		{
			return board[1][i];
		}
	}

	if ((board[0][0] == board[1][1])
		&&(board[1][1] == board[2][2])
		&&(board[1][1] != ' '))
	{
		return board[1][1];
	}

	if ((board[0][2] == board[1][1])
		&&(board[1][1] == board[2][0])
		&&(board[1][1] != ' '))
	{
		return board[1][1];
	}

	return ' ';
}
bool check_full(char board[ROWS][COLS])
{
	int i = 0;
	int j = 0;
	for (i = 0;i < ROWS;i++)
	{
		for (j = 0;j < COLS;j++)
		{
			if (board[i][j] == ' ')
			{
				return false;
			}
		}
	}
	return true;
}
bool game(char board[ROWS][COLS])
{
	bool _bool = false;
	char ret = 0;
	do 
	{
		play_move(board);
		ret = check_min(board);
		if (ret != ' ')
		{
			break;
		}
		if (check_full(board))
		{
			_bool = true;
			break;
		}
		computer_move(board);
		ret = check_min(board);
		if (ret != ' ')
		{
			break;
		}
		if (check_full(board))
		{
			_bool = true;
			break;
		}
		print_board(board);
	} while (ret == ' ');

	if (_bool == true)
	{
		print_board(board);
		cout<<"平局！"<<endl;
		return true;
	}
	if (ret == '*')
	{
		print_board(board);
		cout<<"恭喜你，你赢了！！！"<<endl;
		return true;
	} 
	else//ret = '@'
	{
		print_board(board);
		cout<<"很遗憾，你输了..."<<endl;
		return true;
	}
}