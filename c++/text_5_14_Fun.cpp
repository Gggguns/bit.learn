#define _CRT_SECURE_NO_WARNINGS
#include"text_5_14.h"

int add(int x , int y )
{
	return x + y;
}

double add(double x = 0, double y = 0)
{
	return x + y;
}

//����������ͬ
int Dul(int x, int y, int z)
{
	return x * y * z;
}

int Dul(int x, int y)
{
	return x * y;
}

//��������˳��ͬ
double add(double x, int y)
{
	return x + y;
}

double add(int x, double y)
{
	return x + y;
}