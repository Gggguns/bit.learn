#define _CRT_SECURE_NO_WARNINGS
#include"text_2023_5_9_Date.h"

// ��ȡĳ��ĳ�µ�����

int GetMonthDay(int year, int month);



// ȫȱʡ�Ĺ��캯��

Date::Date(int year = 1900, int month = 1, int day = 1)
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
	return;
}



// ��������

~Date();



// ����+=����

Date& operator+=(int day);



// ����+����

Date operator+(int day);



// ����-����

Date operator-(int day);



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