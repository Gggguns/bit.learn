#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	char killer = 'a';
	for (;killer < 'e';killer++)
	{
		if ((killer != 'a') + (killer == 'c') + (killer == 'd') + (killer != 'd') == 3)
			printf("������%c", killer);
	}
	return 0;
}