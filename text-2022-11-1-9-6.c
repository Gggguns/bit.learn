#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//ѭ��ʵ��strlen
size_t my_strlen1(char* arr)
{
	int count = 0;
	while (*arr++)
	{
		count++;
	}
	return count;
}
//�ݹ�ʵ��strlen
size_t my_strlen2(char* arr)
{
	if (!*arr)
		return 0;
	else
		return 1 + strlen(++arr);
}
//ָ���ָ��ʵ��strlen
size_t my_strlen3(char*arr)
{
	char* Star = arr;
	while (*arr)
	{
		arr = arr + 1;
	}
	return arr - Star;
}
int main()
{
	char arr[] = "csd ";
	printf("%d\n", my_strlen1(arr));
	printf("%d\n", my_strlen2(arr));
	printf("%d\n", my_strlen3(arr));
	return 0;
}