#ifndef __DATA_H__
#define __DATA_H__

#include <iostream>
using namespace std;

class Data
{
public:
	Data(int year = 1995,int month = 8 ,int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{

	}

	Data(const Data& d) // 拷贝构造函数
	{
		this->_year = d._year;
		this->_month = d._month;
		this->_day = d._day;
	}

	Data& operator=(const Data& d)//操作符重载 =
	{
		if(this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	Data& operator+(const int day)
	{
		if (day >= 0)
		{
			_day += day;
			while(_day > this->DayOfMonth())//这里刚开始我写的时候用的是if，当用if的时候if里面的内容只检测一次，
				                            //那么当我加的日子足够多的话，程序将出现bug
			{
				int tmp = _day - DayOfMonth();
				if (_month < 12)
				{
					_month++;
					_day = tmp;
				} 
				else
				{
					_year++;
					_month = 1;
					_day = tmp;
				}
			}
		}
		else
		{
			operator-(-day);
		}
		return *this;
	}

	Data& operator-(const int day)
	{
		if (day >= 0)
		{
			_day -= day;

			while (_day < 1)
			{
				int tmp = this->LastDayOfMonth() - (-_day);
				if (_month > 1)
				{
					_month--;
					_day = tmp;
				} 
				else
				{
					_year--;
					_month = 12;
					_day = tmp;
				}
			}
		} 
		else
		{
			operator+(-day);
		}
		return *this;
	}
	//前置后置自加和自减的区别
	//1>为区别前置和后置运算符，需要在后置运算符重载函数中加参数“int”，
	//	虽然这个类型在此除了以示区别之外并不代表任何实际含义；
    //2>前置返回的是变量的引用，后置返回的是常量。

	Data& operator++()//前置加加
	{
		_day++;
		if (_day > this->DayOfMonth())
		{
			if (_month < 12)
			{
				_month++;
				_day = 1;
			} 
			else
			{
				_year++;
				_month = 1;
				_day = 1;
			}
		}
		return *this;
	}

	Data operator++(int)//后置加加
	{
		Data tmp = *this;
		_day++;
		if (_day > this->DayOfMonth())
		{
			if (_month < 12)
			{
				_month++;
				_day = 1;
			} 
			else
			{
				_year++;
				_month = 1;
				_day = 1;
			}
		}
		return tmp;
	}

	Data& operator--()//前置减减
	{
		_day--;
		if (_day < 1)
		{
			if (_month > 1)
			{
				_day = this->LastDayOfMonth();
				_month--;
			} 
			else
			{
				_year--;
				_day = this->LastDayOfMonth();
				_month = 12;
			}
		}
		return *this;
	}

	Data operator--(int)//后置减减
	{
		Data tmp = *this;
		_day--;
		if (_day < 1)
		{
			if (_month > 1)
			{
				_day = this->LastDayOfMonth();
				_month--;
			} 
			else
			{
				_year--;
				_day = this->LastDayOfMonth();
				_month = 12;
			}
		}
		return tmp;
	}

	bool operator==(const Data& d)
	{
		return ((_year == d._year) && (_month == d._month) && (_day == d._day));
	}

	bool operator!=(const Data& d)
	{
		return (!(_year == d._year) && (_month == d._month) && (_day == d._day));
	}

	bool operator>(const Data& d)
	{
		return ((_year > d._year) || ((_year == d._year) && (_month > d._month)) || ((_year == d._year) &&(_month == d._month) && (_day > d._day)));
	}

	bool operator<(const Data& d)
	{
		return ((_year < d._year) || ((_year == d._year) && (_month < d._month)) || ((_year == d._year) &&(_month == d._month) && (_day < d._day)));
	}

	int operator-(const Data& d)
	{
		if (operator>(d) == true)
		{
			int count = 0;
			Data tmp = d;
			while (!(*this == tmp))
			{
				++tmp;
				count++;
			}
			return count;
		}
		else//operator==(d) == true
		{
			return 0;
		}
	}

	bool IsLeepYear(int year)
	{
		if (((year/4 == 0) && (year/100 != 0)) || (year/400 == 0))
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

	bool IsValidData()
	{
		if ((_year < 1995) || (_month < 1) || (_month > 12) || (_day < 1) || (_day > DayOfMonth()))
		{
			return false;
		} 
		else
		{
			return true;
		}
	}

	int DayOfMonth()
	{
		int arr[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};//每个月的最大天数
		if (IsLeepYear(_year) == true)
		{
			arr[2] = 29;
		}

		return arr[_month];
	}

	int LastDayOfMonth()
	{
		int arr[13] = {0,31,31,28,31,30,31,30,31,31,30,31,30};//上个月的最大天数
		if (IsLeepYear(_year) == true)
		{
			arr[3] = 29;
		}

		return arr[_month];
	}

	void Display()
	{
		cout<<this->_year<<"_"<<this->_month<<"_"<<this->_day<<endl;
	}

private:
	int _year;
	int _month;
	int _day;
};


#endif//__DATA_H__