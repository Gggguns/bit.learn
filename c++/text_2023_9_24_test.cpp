#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//void Swap(int& left, int& right)
//{
//	int tmp = left;
//	left = right;
//	right = tmp;
//}
//void Swap(double& left, double& right)
//{
//	double tmp = left;
//	left = right;
//	right = tmp;
//}


//���ͱ��
//����ģ��
////ģ����������������һ�㣬����ȡ��ΪT.
//template<class T>
////�������ȡ������������Ҳ��
//template<class name1>
////����㲻ϲ��class��������typename
//template<typename name2>
////������붨��������Ҫ�Զ�����Ϊ�ָ��
//template<class T1,class T2>

//�����������ܽ���������ͬ���͵����ݣ���Ҫ�õ�����ģ�����
template<class T1,class T2>
//ģ�������ʵ���൱������
void Swap(T1& left, T2& right)
{
	T1 tmp = left;
	left = right;
	right = tmp;
}


void testSwap1()
{
	int a = 98;
	char b = 'a';
	cout << "����ǰ��" << endl;
	cout << "a:" << a << ' ' << "b:" << b << ' ' << endl;
	//���ý�������
	Swap(a, b);
	cout << "������" << endl;
	cout << "a:" << a << ' ' << "b:" << b << ' ' << endl;
}

int main()
{ 
	testSwap1();




	return 0;
}



















//int main(int agc, char* agv[], char* env[])
//{
//	int i = 0;
//	for (i = 0;agv[i];i++)
//	{
//		cout << agv[i] << endl;
//	}
//	return 0;
//}