#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
//����
class Data
{
public:
	//��ʼ�����캯��
	Data(int year = 0, int month = 0, int day = 0);

	//�������캯��
	Data(const Data& d);

	//���������
	//����
	bool operator<(const Data& d);

	//����
	bool operator==(const Data& d);

private:
	int _year;
	int _month;
	int _day;

};