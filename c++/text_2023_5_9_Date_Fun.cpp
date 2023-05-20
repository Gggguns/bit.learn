#define _CRT_SECURE_NO_WARNINGS
#include"text_2023_5_9_Date.h"

// ��ȡĳ��ĳ�µ�����

int GetMonthDay(int year, int month)
{
	while (12 < month)
	{
		month--;
		year++;
	}
	static int arr[13] = { 0,31,28,31,30,31,30,31 ,31,30 ,31,30 ,31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		return arr[month] + 1;
	else
		return arr[month];
}



// ȫȱʡ�Ĺ��캯��

Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;

}



// �������캯��

Date::Date(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
}



// ��ֵ���������

// d2 = d3 -> d2.operator=(&d2, d3)

Date& Date::operator=(const Date& d)
{
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}



// ��������
Date::~Date()
{
	_year = 0;
	_month = 0;
	_day = 0;
}



// ����+=����

Date& Date::operator+=(int day)
{
	_day = _day + day;
	while (GetMonthDay(_year, _month) < _day)
	{
		_day = _day - GetMonthDay(_year, _month);
		_month++;
		while (_month > 12)
		{
			_month = _month - 12;
			_year++;
		}
	}
	return *this;
}



// ����+����

Date Date::operator+(int day)
{
	Date d(*this);
	d += day;
	return d;

}



// ����-����

Date Date::operator-(int day);



// ����-=����

Date& operator-=(int day);



// ǰ��++

Date& operator++();



// ����++

Date operator++(int);



// ����--

Date operator--(int);



// ǰ��--

Date& operator--();



// >���������

bool operator>(const Date& d);



// ==���������

bool Date::operator==(const Date& d)
{
	if (_year == d._year && _month == d._month && _day == d._day)
		return true;
	else
		return false;
}



// >=���������

bool operator >= (const Date& d);



// <���������

bool Date::operator < (const Date& d)
{
	if (_year >= d._year)
		return false;
	else if (_year == d._year && _month >= d._month)
		return false;
	else if (_year == d._year && _month == d._month && _day >= d._day)
		return false;
	else
		return true;
}



// <=���������

bool operator <= (const Date& d);



// !=���������

bool operator != (const Date& d);



// ����-���� ��������

int operator-(const Date& d);