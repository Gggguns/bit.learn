#define _CRT_SECURE_NO_WARNINGS
#include"text-2022-11-7-2-game.h"
void TextGame()
{
	int input = 0;
	do
	{
		menu();
		printf("������ѡ�������:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			Game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�������\n");
			break;
		}
	} while (input);
}
int main()
{
	TextGame();
	return 0;
}