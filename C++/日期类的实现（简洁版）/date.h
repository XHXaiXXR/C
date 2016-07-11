#pragma once

class Date
{
public:
	Date(int year = 1990,int month = 1,int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		if (IsInvalidData() == false)
		{
			_year = 1990;
			_month = 1;
			_day = 1;
		}
	}
	Date(const Date& d)
	{
		this->_year = d._year;
		this->_month = d._month;
		this->_day = d._day;
	}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			this->_year = d._year;
			this->_month = d._month;
			this->_day = d._day;
		}
		return *this;
	}
	Date& operator+(const int day)
	{
		_day += day;

		while (_day > DayOfMonth())
		{
			_month++;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
			_day = _day - DayOfMonth();
		}
		return *this;
	}
	Date& operator-(const int day)
	{
		_day -= day;
		while(_day < 1)
		{
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day = DayOfMonth() - (-_day);
		}
		return *this;
	}
	Date& operator++()//前置++
	{
		_day++;
		if (_day > DayOfMonth())
		{
			_month++;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
			_day = 1;
		}
		return *this;
	}
	Date operator++(int)//后置++
	{
		Date tmp = *this;
		_day++;
		if (_day > DayOfMonth())
		{
			_month++;
			if (_month > 12)
			{
				_year++;
				_month = 1;
			}
			_day = 1;
		}
		return tmp;
	}
	Date& operator--()//前置--
	{
		_day--;
		if (_day < 1)
		{
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day = DayOfMonth();
		}
		return *this;
	}
	Date operator--(int)//后置--
	{
		Date tmp = *this;
		_day--;
		if (_day < 1)
		{
			_month--;
			if (_month < 1)
			{
				_year--;
				_month = 12;
			}
			_day = DayOfMonth();
		}
		return tmp;
	}
	int operator-(const Date& d)
	{
		if (this > &d)
		{
			Date tmp = d;
			int count = 0;
			while (tmp != *this)
			{
				++tmp;
				++count;
			}
			return count;
		}
		else
		{
			Date tmp = *this;
			int count = 0;
			while(tmp != d)
			{
				++tmp;
				count++;
			}
			return count;
		}
	}
	bool operator==(const Date& d)
	{
		return (_year==d._year) && (_month == d._month) && (_day == d._day);
	}
	bool operator!=(const Date& d)
	{
		return !(operator==(d));
	}
	bool operator>(const Date& d)
	{
		return (_year > d._year)
			|| (_year == d._year && _month > d._month)
			|| (_year == d._year && _month > d._month && _day > d._day);
	}
	bool operator<(const Date& d)
	{
		return !(operator>(d));
	}
	void Display()
	{
		cout<<this->_year<<"_"<<this->_month<<"_"<<this->_day<<endl;
	}
protected:
	bool IsInvalidData()
	{
		if (_year < 1990 || _month < 1 || _month > 12 || _day < 1 || _day > DayOfMonth())
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
		int arr[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
		if (IsLeepYear(_year) == true)
		{
			arr[2] = 29;
		}
		return arr[_month];
	}
	bool IsLeepYear(int year)
	{
		if (((year % 4 == 0)&&(year % 100 == 0)) || (year % 400 == 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	int _year;
	int _month;
	int _day;
};