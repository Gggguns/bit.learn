#define _CRT_SECURE_NO_WARNINGS
#include"contact.h"
int main()
{
	int input;
	Initcontact(&con);
	do
	{
	menu();
	printf("����������:>");
	scanf("%d", &input);
	switch (input)
	{
	case add:
		Add(&con);
		break;
	case del:
		Del(&con);
		break;
	case search:
		Search(&con);
		break;
	case modify:
		Mondif(&con);
		break;
	case show:
		Show(&con);
		break;
	case exit:
		printf("�˳�\n");
		break;
	default :
		printf("�������\n");
		break;

	}

	} while (input);

	return 0;
}