#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
union
{
	char c;
	int a;
}un;
void text1()//��һ�ַ���
{
	int a = 1;
	if (*(char *)&a == 1)
		printf("С��");
	else
		printf("���");
}
void text2()//�ڶ��ַ���
{
	un.a = 1;
	if (un.c == 1)
		printf("\nС��");
	else
		printf("\n���");
}
int main()
{
	text1();
	text2();
	return 0;
}
