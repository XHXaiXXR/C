#include<iostream>
using namespace std;
#include <stdio.h>
#include <vector>
#include<algorithm>

struct ServeContent
{
	int _name;					//进程名
	int _arrivetime;			//到达时间
	int _runingtime;			//服务时间（运行）
	int _priority;				//优先级数（优先值越低，优先级约高）
	int _intomemory;			//进入内存时间
	int _finish;				//完成时间
	double _revolve;				//周转时间
	double _weightrevolve;		//带权周转时间

	ServeContent()
		:_name(int())
		,_arrivetime(int())
		,_runingtime(int())
		,_priority(int())
		,_intomemory(int())
		,_finish(int())
		,_revolve(int())
		,_weightrevolve(double())
	{}
};


class Serve
{
	typedef ServeContent sc;
public:
	Serve(const int size = int())
	{
		_arr.resize(size);
	}

	//先来先服务
	void FCFS()
	{
		Insert();

		_sort_arrivetime();//根据到达时间进行排序，先到先服务

		for (size_t i = 0;i < _arr.size();++i)
		{
			if (i == 0)
				_arr[i]._intomemory = 0;
			else
				_arr[i]._intomemory = _arr[i-1]._intomemory + _arr[i-1]._runingtime;

			_arr[i]._finish = _arr[i]._runingtime + _arr[i]._intomemory;	//完成时间 = 开始执行时间 + 服务（运行）时间
			_arr[i]._revolve = _arr[i]._finish - _arr[i]._arrivetime;		//周转时间 = 完成时间 - 到达时间
			_arr[i]._weightrevolve = _arr[i]._revolve / _arr[i]._runingtime;//带权周转时间 = 周转时间 / 运行时间
		}

		Display();
	}

	//短作业优先
	void SJF()
	{
		Insert();
		_sort_arrivetime();

		vector<sc>::iterator it = _arr.begin();

		_arr[0]._intomemory = 0;
		_arr[0]._finish = _arr[0]._runingtime + _arr[0]._intomemory;	//完成时间 = 开始执行时间 + 服务（运行）时间
		_arr[0]._revolve = _arr[0]._finish - _arr[0]._arrivetime;		//周转时间 = 完成时间 - 到达时间
		_arr[0]._weightrevolve = _arr[0]._revolve / _arr[0]._runingtime;//带权周转时间 = 周转时间 / 运行时间

		for (size_t i = 1;i < _arr.size();++i)
		{
			vector<sc>::iterator cur = it + 1;

			while (cur != _arr.end())
			{
				if (cur->_arrivetime > it->_finish)
				{
					break;
				}

				++cur;
			}

			struct Less
			{
				bool operator()(const sc& left,const sc right)
				{
					return left._runingtime < right._runingtime;
				}
			};

			sort(it+1,cur,Less());

			_arr[i]._intomemory = _arr[i-1]._intomemory + _arr[i-1]._runingtime;
			_arr[i]._finish = _arr[i]._runingtime + _arr[i]._intomemory;	//完成时间 = 开始执行时间 + 服务（运行）时间
			_arr[i]._revolve = _arr[i]._finish - _arr[i]._arrivetime;		//周转时间 = 完成时间 - 到达时间
			_arr[i]._weightrevolve = _arr[i]._revolve / _arr[i]._runingtime;//带权周转时间 = 周转时间 / 运行时间

			++it;
		}

		Display();
	}

	//时间片轮转
	void Robin()
	{
		Insert();

		cout<<"请输入时间片轮转时间：";
		int num = 0;
		cin>>num;

		if (num <= 0)
		{
			return;
		}

		_sort_arrivetime();

		vector<int> tmp(_arr.size());
		for (size_t i = 0;i < _arr.size();++i)
		{
			//保存_runingtime值，因为后面会做修改
			tmp[i] = _arr[i]._runingtime;
		}

		//记录当前有几个进程
		int count = 0;
		//一个进程结束后，时间片不再为他分配PCB，记录结束位置的下一个位置
		int key = 0;
		//当前时刻下是否有进程进入
		int Y = 0;
		//时间轴
		int time = 0;
		//保存进程的个数
		int newcount = 0;
		do 
		{
			size_t i = Y;
			for (;i < _arr.size();++i)
			{
				//寻找当前时刻下是否有进程进入PCB
				if (time >= _arr[i]._arrivetime)
					++count;
				else
					break;
			}
			
			if (count == 0)
			{
				//如果没有进程进入的话，时间要增长
				time += num;
			} 
			else
			{
				newcount = count;
				Y = i;
			}
			int begin = key;

			while (newcount--)
			{
				time += num;
				_arr[begin]._runingtime -= num;

				if (_arr[begin]._runingtime == 0)
				{
					_arr[begin]._finish = time;
					--count;
					++key;
				} 
				else if(_arr[begin]._runingtime < 0)
				{
					_arr[begin]._finish = time + _arr[begin]._runingtime;
				}

				++begin;
			}
		} while (count > 0);

		for (size_t i = 0;i < _arr.size();++i)
		{
			//把之前保存的_runingtime值重新赋值给进程
			_arr[i]._runingtime = tmp[i];

			if (i == 0)
			{
				_arr[0]._intomemory =0;
			} 
			else
			{
				_arr[i]._intomemory = _arr[i-1]._intomemory + _arr[i-1]._runingtime;
			}

			_arr[i]._revolve = _arr[i]._finish - _arr[i]._arrivetime;		//周转时间 = 完成时间 - 到达时间
			_arr[i]._weightrevolve = _arr[i]._revolve / _arr[i]._runingtime;//带权周转时间 = 周转时间 / 运行时间
		}

		Display();
	}

	void Insert()
	{
		int flag = 0;
		cout<<"是否对优先级数有要求？（是——输入1，否——输入0）："<<endl;
		cin>>flag;

		if (flag == 0)
		{
			cout<<"请分别输入："<<endl;
			cout<<"进程名   到达时间   运行时间"<<endl;
			for (size_t i = 0;i < _arr.size();++i)
			{
				cin>>_arr[i]._name>>_arr[i]._arrivetime>>_arr[i]._runingtime;
			}
		} 
		else if(flag == 1)
		{
			cout<<"请分别输入："<<endl;
			cout<<"进程名	到达时间	运行时间	优先级数"<<endl;
			for (size_t i = 0;i < _arr.size();++i)
			{
				cin>>_arr[i]._name>>_arr[i]._arrivetime>>_arr[i]._runingtime>>_arr[i]._priority;
			}
		}
	}
	void Display()
	{
		cout<<"******************************************************************************************************************************************"<<endl;
		printf("进程名\t\t到达时间\t服务时间\t进入内存时间\t优先级数\t完成时间\t周转时间\t\t带权周转时间\n");
		cout<<"******************************************************************************************************************************************"<<endl;

		for (size_t i = 0;i < _arr.size();++i)
		{
			printf("%2d\t\t%2d\t\t%2d\t\t%2d\t\t%2d\t\t%2d\t\t%2f\t\t%2f\n",_arr[i]._name,_arr[i]._arrivetime,_arr[i]._runingtime,
				_arr[i]._intomemory,_arr[i]._priority,_arr[i]._finish,_arr[i]._revolve,_arr[i]._weightrevolve);
		}
		cout<<"******************************************************************************************************************************************"<<endl;

	}
protected:
	void _sort_arrivetime()
	{
		for (size_t i = 0;i < _arr.size() - 1;++i)//趟数
		{
			for (size_t j = 0;j < _arr.size() - 1 - i;++j)//次数
			{
				if (_arr[j]._arrivetime > _arr[j+1]._arrivetime)
				{
					swap(_arr[j],_arr[j+1]);
				}
			}
		}
	}
private:
	vector<sc> _arr;
};

void test()
{
	cout<<"几个进程？ "<<endl;
	int n = 0;
	cin>>n;
	Serve s(n);
	//s.FCFS();	//先来先服务算法
	//s.SJF();	//短作业优先
	s.Robin();	//时间片轮转
}
int main()
{
	test();
	system("pause");
	return 0;
}