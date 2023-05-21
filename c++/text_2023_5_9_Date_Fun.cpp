#define _CRT_SECURE_NO_WARNINGS
#include"text_2023_5_9_Date.h"
using namespace std;

// ��ȡĳ��ĳ�µ�����

int Date::GetMonthDay(int year, int month)const
{
	while (12 < month)
	{
		month--;
		year++;
	}
	while (month < 0)
	{
		month += 12;
		year--;
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

Date Date::operator+(int day)const
{
	Date d(*this);
	d += day;
	return d;

}



// ����-����

Date Date::operator-(int day)const
{
	Date d(*this);
	if (day < 0)
	{
		day = -day;
		return d + day;
	}
	else
	{
		d._day = d._day - day;
		while (0 > d._day)
		{
			d._day = d._day + GetMonthDay(d._year, d._month);
			d._month--;
			while (d._month <= 0)
			{
				d._month = d._month + 12;
				d._year--;
			}
		}
		return d;
	}
}



// ����-=����

Date& Date::operator-=(int day)
{
	*this = *this - day;
	return *this;
}



// ǰ��++

Date& Date::operator++()
{
	*this += 1;
	return *this;
}



// ����++

Date Date::operator++(int)
{
	Date d(*this);
	*this += 1;
	return d;
}



// ����--

Date Date::operator--(int)
{
	Date d(*this);
	*this -= 1;
	return d;
}



// ǰ��--

Date& Date::operator--()
{
	*this -= 1;
	return *this;
}



// >���������

bool Date::operator>(const Date& d)const
{
	if (*this <= d)
		return false;
	else
		return true;
}



// ==���������

bool Date::operator==(const Date& d)const
{
	if (_year == d._year && _month == d._month && _day == d._day)
		return true;
	else
		return false;
}



// >=���������

bool Date::operator >= (const Date& d)const
{
	if (*this < d)
		return false;
	else
		return true;
}



// <���������

bool Date::operator < (const Date& d)const
{
	if (_year > d._year)
		return false;
	else if (_year == d._year && _month > d._month)
		return false;
	else if (_year == d._year && _month == d._month && _day >= d._day)
		return false;
	else
		return true;
}



// <=���������

bool Date::operator <= (const Date& d)const
{
	if (*this < d || *this == d)
		return true;
	else
		return false;
}



// !=���������

bool Date::operator != (const Date& d)const
{
	if (*this == d)
		return false;
	else
		return true;
}



// ����-���� ��������

int Date::operator-(const Date& d)const
{
	Date Max(*this);
	Date Min(d);
	if ((*this) < d)
	{
		Max = d;
		Min = *this;
	}
	int i = 0;
	while (Min < Max)
	{
		i++;
		++Min;
	}
	if (*this > d)
		return i;
	else
		return -i;
}

ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "��" << d._month << "��" << d._day << "��" << endl;
	return out;
}

istream& operator>>(istream& in, Date& d)
{
	int year, month, day;
	in >> year >> month >> day;
	if (month > 12 || day > d.GetMonthDay(year, month))
	{
		cout << "�Ƿ�����" << endl;
	}
	else
	{
		d._year = year;
		d._month = month;
		d._day = day;
	}
	return in;
}