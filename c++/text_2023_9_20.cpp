#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int main()
{
	int* ptr = new int(10);

	int* p = new int[10] {1,2,3,4,5,6,7,8,9,10};
	int i = 0;
	for (i = 0;i < 10;i++)
	{
		cout << p[i] << endl;
	}
	
	//�ڿռ���ִ��������������ɶ�������Դ������
	delete ptr;
	//����N����������������N���������Դ
	delete[] p;
	return  0;
}