#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <cstdio>
#include <time.h>
#include <vector>
#include <Windows.h>

enum
{
	U,
	R,
	D,
	L
};

typedef struct Coor
{
	int _x;
	int _y;

	Coor(int x = 0,int y = 0)
		:_x(x)
		,_y(y)
	{}
}Coor;

void Move(int x ,int y)
{
	COORD c;//定义结构体变量
	c.X = x;
	c.Y = y;

	HANDLE handle;//定义一个句柄
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//获得输出设备的句柄
	SetConsoleCursorPosition(handle,c);//定位句柄控制光标
}

class Snake
{
public:
	//构造函数
	Snake(int row,int col)
		:_row(row)
		,_col(col)
	{
		//开辟地图空间（二维数组）
		_map = new char*[_row];
		for(size_t i = 0;i < _row;i++)
		{
			_map[i] = new char[_col];
		}
	}
	//析构函数
	~Snake()
	{
		for (size_t i = 0;i < _row;i++)
		{
			delete[] _map[i];
		}
		delete[] _map;
	}
private:
	void InitMap()//初始化地图
	{
		//地图的每一个位置都初始化为空格
		for (size_t i = 0;i < _row;i++)
		{
			for (size_t j = 0;j < _col;j++)
			{
				_map[i][j] = ' ';
			}
		}
		//设置地图左右的围墙
		for (size_t i = 0;i < _row;i++)
		{
			_map[i][0] = '#';
			_map[i][_col - 1] = '#';
		}
		//设置地图上下的围墙
		for (size_t i = 0;i < _col;i++)
		{
			_map[0][i] = '#';
			_map[_row-1][i] = '#';
		}
	}
	void PrintMap()
	{
		InitMap();
		for (size_t i = 0;i < _row;i++)
		{
			for (size_t j = 0;j < _col;j++)
			{
				cout<<_map[i][j];
			}
			cout<<endl;
		}

		Coor c;
		c._x = 5;
		c._y = 5;
		_array.push_back(c);
		Move(c._x,c._y);
		cout<<'*';
		_status = D;
	}

	void SetFood()
	{
		int x = 0;
		int y = 0;

		while((_map[x][y] != ' '))
		{
			srand((unsigned)time(NULL));
			//获取一个能落在地图里的坐标；
			x = rand() % _row;
			y = rand() % _col;
		}

		//光标挪到食物的坐标处
		Move(y,x);
		//食物标记为0
		cout<<'0';

		//标记食物坐标
		_food._x = y;
		_food._y = x;
	}

	void Advance()
	{
		//蛇往前挪动(除了蛇头以外，每个蛇单位当前状态都是上一个蛇单位的当前状态)
		for (size_t i = _array.size() - 1;i > 0;i--)
		{
			_array[i]._x = _array[i - 1]._x;
			_array[i]._y = _array[i - 1]._y;
		}
	}
	bool CheckAccess()
	{
		//检查蛇否还在地图内
		if ((_array[0]._x > 0) && (_array[0]._x < (_col - 1))
			&& (_array[0]._y > 0) && (_array[0]._y < (_row - 1)))
		{
			for (size_t i = 1;i < _array.size();i++)
			{
				//蛇头是否和蛇身相撞
				if ((_array[0]._x == _array[i]._x)
					&& (_array[0]._y == _array[i]._y))
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	void DrawSnake(int status)
	{
		//先将蛇全部在屏幕上抹掉
		for (size_t i = 0;i < _array.size();i++)
		{
			//光标挪到蛇单位所处位置
			Move(_array[i]._x,_array[i]._y);
			//将每个蛇单位覆盖
			cout<<' ';
		}

		switch(_status)
		{
		case U:
			{
				Advance();
				//蛇头改变方向
				_array[0]._y -= 1;
			}
			break;
		case R:
			{
				Advance();
				//蛇头改变方向
				_array[0]._x += 1;
			}
			break;
		case D:
			{
				Advance();
				//蛇头改变方向
				_array[0]._y += 1;
			}
			break;
		case L:
			{
				Advance();
				//蛇头改变方向
				_array[0]._x -= 1;
			}
			break;
		}
		//检查当前蛇的状态是否合法
		if (!CheckAccess())
		{
			//不合法则错误返回
			exit(1);//0是正确返回，1是错误返回

			//cout<<"很遗憾，你输了！"<<endl;
			//PlayGame();
		}

		//重新绘制蛇的图案
		for (size_t i = 0;i < _array.size();i++)
		{
			//光标挪到当前蛇单位的位置
			Move(_array[i]._x,_array[i]._y);
			cout<<'*';
		}
	}
public:
	void PlayGame()
	{
		PrintMap();
		SetFood();
		int time = 300;
		//蛇要不断变换位置
		while (1)
		{
			if (GetAsyncKeyState(VK_UP) && _status != U)
			{
				_status = U;
			}
			else if (GetAsyncKeyState(VK_DOWN) && _status != D)
			{
				_status = D;
			}
			else if (GetAsyncKeyState(VK_LEFT) && _status != L)
			{
				_status = L;
			}
			else if (GetAsyncKeyState(VK_RIGHT) && _status != R)
			{
				_status = R;
			}

			//判断是否吃到食物（蛇头坐标是否与食物坐标一致）
			if ((_array[0]._x == _food._x) && (_array[0]._y == _food._y))
			{
				//蛇身加长一个单位
				Coor tmp = _array.back();//增加一个蛇身单位与蛇尾的状态一致
				_array.push_back(tmp);//新增加的一个蛇单位与蛇尾相连

				//食物被吃掉后重新设置一个新的食物
				SetFood();
				if (time > 100)
				{
					time -= 20;
				}
			}

			//绘制蛇的图案
			DrawSnake(_status);
			Sleep(time);
		}
	}

private:
	vector<Coor> _array;//蛇头蛇深的存储
	char** _map;//开辟地图
	size_t _row;//地图的行
	size_t _col;//地图的列
	Coor _food;//事物的位置
	int _status;//蛇头方向的移动的位置
};


void test()
{
	Snake s(20,40);
	s.PlayGame();
}
int main()
{
	test();
	system("pause");
	return 0;
}