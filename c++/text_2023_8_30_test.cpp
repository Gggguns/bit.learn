#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;
inline int fun1()
{
	static int x = 0;
	return x;
}

void fun(int)
{
	cout << "f(int)" << endl;
}
void fun(int*)
{
	cout << "f(int*)" << endl;
}
int main()
{

	fun(0);
	fun(NULL);
	fun((int*)NULL);


























	//int& ret = fun1();//Ȩ�޵ķŴ�
	//const int& ret = fun1();//Ȩ�޵�ƽ��
	//int ret = fun1();//����

	//int Arr[10] = { 1,2,3,4,5,6,7,8,9,0 };
	////֮ǰ������
	//int size = sizeof(Arr) / sizeof(Arr[0]);
	//int i = 0;
	//for (i = 0;i < size;i++)
	//{
	//	cout << Arr[i] << ' ';
	//}
	//cout << endl;
	////���ڵ�����
	//for (auto e : Arr)
	//{
	//	cout << e << ' ';
	//}






















	////���ù�����,Ȩ�޷Ŵ�
	//const int a = 0;
	//int& b = a;

	////���õĹ����У�����d�Ա���c���п���
	//const int& c = 0;
	//int d = c; 
	//
	//
	//int x = 0;
	//int& y = x;//����x�����ǿ��Ա��޸ģ�����y�Ա���x���ã�Ҳ���ԶԱ���x�����޸ġ�������Ȩ�޵�ƽ��
	//const int& z = x;//����x�����ǿ��Ա��޸ģ�������z�Ա���x���ã����ܶԱ���x�����޸ġ�������Ȩ�޵���С

	//double e = 1.1;
	////int& i = e;
	//const int& i = e;
	//std::cout << i << std::endl;

	return 0;
}