#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//���ȣ������ȶ���һ�������б�����ͨ����������������ͬ�ĺ��������ԣ���������ֻ��Ҫһ��ģ�����
template<class T>
//��Σ���ɽ���������ʵ��
void Swap(T& left,T& right)
{
	T tmp = left;
	left = right;
	right = tmp;
}
//�������
template<class T2>
T2 Add(const T2& x, const T2& y)
{
	cout << "�����˺���ģ��\n";
	return x + y;
}

//ר�Ŵ���int����
int Add(int left,int right)
{
	cout << "��û�ߺ���ģ��\n";
	return left+right;
}
void testSwap1()
{
	double a = 10.2;
	double b = 12.3;
	cout << "����ǰ��" << endl;
	cout << "a:" << a << ' ' << "b:" << b << endl;
	Swap(a, b);
	cout << "������:\n";
	cout << "a:" << a << ' ' << "b:" << b << endl;
}

void testSwap2()
{
	double a = 10.5;
	int b = 90;
	int c = 10;
	//Swap(a, b);
	//��ʽ����ת�����������ᴫ��ȥ�������Զ��Ƶ�
	cout << Add(b, c) << endl;
	cout << Add(a, (double)b) << endl;//�Ա���b��������ת��

	//��ʾ����ת��
	//cout << Add(a, b) << endl;
	cout << Add<double>(a, b) << endl;
	
}

void testSwap3()
{
	int a = 10;
	int b = 20;
	cout << Add(a, b) << endl;
}
int main()
{
	testSwap3();

	return 0;
}