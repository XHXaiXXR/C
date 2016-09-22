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
	COORD c;//����ṹ�����
	c.X = x;
	c.Y = y;

	HANDLE handle;//����һ�����
	handle = GetStdHandle(STD_OUTPUT_HANDLE);//�������豸�ľ��
	SetConsoleCursorPosition(handle,c);//��λ������ƹ��
}

class Snake
{
public:
	//���캯��
	Snake(int row,int col)
		:_row(row)
		,_col(col)
	{
		//���ٵ�ͼ�ռ䣨��ά���飩
		_map = new char*[_row];
		for(size_t i = 0;i < _row;i++)
		{
			_map[i] = new char[_col];
		}
	}
	//��������
	~Snake()
	{
		for (size_t i = 0;i < _row;i++)
		{
			delete[] _map[i];
		}
		delete[] _map;
	}
private:
	void InitMap()//��ʼ����ͼ
	{
		//��ͼ��ÿһ��λ�ö���ʼ��Ϊ�ո�
		for (size_t i = 0;i < _row;i++)
		{
			for (size_t j = 0;j < _col;j++)
			{
				_map[i][j] = ' ';
			}
		}
		//���õ�ͼ���ҵ�Χǽ
		for (size_t i = 0;i < _row;i++)
		{
			_map[i][0] = '#';
			_map[i][_col - 1] = '#';
		}
		//���õ�ͼ���µ�Χǽ
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
			//��ȡһ�������ڵ�ͼ������ꣻ
			x = rand() % _row;
			y = rand() % _col;
		}

		//���Ų��ʳ������괦
		Move(y,x);
		//ʳ����Ϊ0
		cout<<'0';

		//���ʳ������
		_food._x = y;
		_food._y = x;
	}

	void Advance()
	{
		//����ǰŲ��(������ͷ���⣬ÿ���ߵ�λ��ǰ״̬������һ���ߵ�λ�ĵ�ǰ״̬)
		for (size_t i = _array.size() - 1;i > 0;i--)
		{
			_array[i]._x = _array[i - 1]._x;
			_array[i]._y = _array[i - 1]._y;
		}
	}
	bool CheckAccess()
	{
		//����߷��ڵ�ͼ��
		if ((_array[0]._x > 0) && (_array[0]._x < (_col - 1))
			&& (_array[0]._y > 0) && (_array[0]._y < (_row - 1)))
		{
			for (size_t i = 1;i < _array.size();i++)
			{
				//��ͷ�Ƿ��������ײ
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
		//�Ƚ���ȫ������Ļ��Ĩ��
		for (size_t i = 0;i < _array.size();i++)
		{
			//���Ų���ߵ�λ����λ��
			Move(_array[i]._x,_array[i]._y);
			//��ÿ���ߵ�λ����
			cout<<' ';
		}

		switch(_status)
		{
		case U:
			{
				Advance();
				//��ͷ�ı䷽��
				_array[0]._y -= 1;
			}
			break;
		case R:
			{
				Advance();
				//��ͷ�ı䷽��
				_array[0]._x += 1;
			}
			break;
		case D:
			{
				Advance();
				//��ͷ�ı䷽��
				_array[0]._y += 1;
			}
			break;
		case L:
			{
				Advance();
				//��ͷ�ı䷽��
				_array[0]._x -= 1;
			}
			break;
		}
		//��鵱ǰ�ߵ�״̬�Ƿ�Ϸ�
		if (!CheckAccess())
		{
			//���Ϸ�����󷵻�
			exit(1);//0����ȷ���أ�1�Ǵ��󷵻�

			//cout<<"���ź��������ˣ�"<<endl;
			//PlayGame();
		}

		//���»����ߵ�ͼ��
		for (size_t i = 0;i < _array.size();i++)
		{
			//���Ų����ǰ�ߵ�λ��λ��
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
		//��Ҫ���ϱ任λ��
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

			//�ж��Ƿ�Ե�ʳ���ͷ�����Ƿ���ʳ������һ�£�
			if ((_array[0]._x == _food._x) && (_array[0]._y == _food._y))
			{
				//����ӳ�һ����λ
				Coor tmp = _array.back();//����һ������λ����β��״̬һ��
				_array.push_back(tmp);//�����ӵ�һ���ߵ�λ����β����

				//ʳ�ﱻ�Ե�����������һ���µ�ʳ��
				SetFood();
				if (time > 100)
				{
					time -= 20;
				}
			}

			//�����ߵ�ͼ��
			DrawSnake(_status);
			Sleep(time);
		}
	}

private:
	vector<Coor> _array;//��ͷ����Ĵ洢
	char** _map;//���ٵ�ͼ
	size_t _row;//��ͼ����
	size_t _col;//��ͼ����
	Coor _food;//�����λ��
	int _status;//��ͷ������ƶ���λ��
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