#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//����
class Date

{
	friend  ostream& operator<<(ostream& out, const Date& d);
	friend  istream& operator>>(istream& in, Date& d);

public:

	// ��ȡĳ��ĳ�µ�����

	int GetMonthDay(int year, int month)const;



	// ȫȱʡ�Ĺ��캯��

	Date(int year = 1900, int month = 1, int day = 1);



	// �������캯��

	Date(const Date& d);



	// ��ֵ���������

  // d2 = d3 -> d2.operator=(&d2, d3)

	Date& operator=(const Date& d);



	// ��������

	~Date();



	// ����+=����

	Date& operator+=(int day);



	// ����+����

	Date operator+(int day)const;



	// ����-����

	Date operator-(int day)const;



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

	bool operator>(const Date& d)const;



	// ==���������

	bool operator==(const Date& d)const;



	// >=���������

	bool operator >= (const Date& d)const;



	// <���������

	bool operator < (const Date& d)const;



	// <=���������

	bool operator <= (const Date& d)const;



	// !=���������

	bool operator != (const Date& d)const;



	// ����-���� ��������

	int operator-(const Date& d)const;

private:

	int _year;

	int _month;

	int _day;

};

ostream& operator<<(ostream& out, const Date& d);

istream& operator>>(istream& in, Date& d);
