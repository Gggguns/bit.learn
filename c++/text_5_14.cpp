#define _CRT_SECURE_NO_WARNINGS
#include"text_5_14.h"

int main()
{
	cout << add(6.5,3.3) << endl;
	cout << add(1, 3) << endl;

	cout << Dul(10, 2, 3) << endl;
	cout << Dul(3, 8) << endl;

	cout << add(3, 3.3) << endl;
	cout << add(7.3, 5) << endl;

	int x = 10;
	int& ra = x;//��Ҫע��������õ�����Ҫ������ʵ���������ͬ
	const int& r = 10;

	return 0;
}