#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int main()
{
	float Sum = 0;
	float SumCredit = 0;
	cout << "������Ҫ����Ŀ�Ŀ������" << endl;
	int count = 0;
	cin >> count;
	while (count--)
	{
		float general = 0;
		float credit = 0;
		cout << "����������ÿ�Ƶ�������ѧ�֣��Կո���Ϊ�����:" << endl;
		cin >> general >> credit;
		SumCredit = SumCredit + credit;
		Sum = Sum + general * credit;
	}
	cout << Sum / SumCredit << endl;

	return 0;
}