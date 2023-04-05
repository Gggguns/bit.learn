#define _CRT_SECURE_NO_WARNINGS
#include"text-2022-11-7-2-game.h"

//�˵�
void menu()
{
	printf("*************************************\n");
	printf("*********      1.Play      **********\n");
	printf("*********      0.Exit     **********\n");
	printf("*************************************\n");
}

//��Ϸ
void Game()
{
	char broad[Row][Col];
	srand((unsigned int)time(NULL));
	Init_broad(broad, Row, Col);
	char ret;
	while(1)
	{
		
		//Printf_broad(broad, Row, Col);
		Playmove(broad, Row, Col);
		ret=Is_win(broad, Row, Col);
		if (ret != 'C')
		{
			break;
		}
		Conputurmove(broad, Row, Col);
		ret = Is_win(broad, Row, Col);
		if (ret != 'C')
		{
			break;
		}
	}
	
	if (ret == '*')
		printf("��һ�ʤ\n");
	else if (ret == '#')
		printf("���Ի�ʤ\n");
	else
		printf("ƽ��\n");
	Printf_broad(broad, Row, Col);
}

//���̳�ʼ��
void Init_broad(char broad[Row][Col], int row, int col)
{
	int i = 0;
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			broad[i][j] = ' ';
		}
	}
}

//�������
void Playmove(char broad[Row][Col], int row, int col)
{
	int x = 0, y = 0;
	printf("�������\n");
	Printf_broad(broad, row, col);
	printf("�������������:>");
	while(1)
	{
		
		scanf("%d%d", &x, &y);
		if (0 < x && 0 < y && x <= 3 && y <= 3)
		{
			if (broad[x - 1][y - 1] == ' ')
			{
				broad[x - 1][y - 1] = '*';
				break;
			}
			else
				printf("��λ���ѷ�������\n");
		}
		else
		{
			printf("�����������\n");
		}
		printf("�����������������:>");
	}
}

//��ӡ����
void Printf_broad(char broad[Row][Col], int row, int col)
{
	int i = 0;
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			printf(" %c ", broad[i][j]);
			if(j<col-1)
				printf("|");
		}
		printf("\n");
		if(i<row-1)
		{
			for (j = 0;j < col;j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
		}
		printf("\n");
	}
}

//��������
void Conputurmove(char broad[Row][Col], int row, int col)
{
	printf("��������\n");
	Printf_broad(broad, row, col);
	while (1)
	{
		int x = rand() % row;
		int y = rand() % col;
		if (0 <= x && 0 <= y && x < 3 && y < 3)
		{
			if (broad[x][y] == ' ')
			{
				broad[x][y] = '#';
				break;
			}
		}
	}
}

//˭Ӯ��
char Is_win(char broad[Row][Col], int row, int col)
{
	//����
	int i = 0;
	for (i = 0;i < row;i++)
	{
		if (broad[i][0] == broad[i][1] && broad[i][1] == broad[i][2] && broad[i][0] != ' ')
			return broad[i][0];
	}
	//����
	for (i = 0;i < col;i++)
	{
		if (broad[0][i] == broad[1][i] && broad[1][i] == broad[2][i] && broad[0][i] != ' ')
			return broad[0][i];
	}
	//�Խ���
	if (broad[0][0] == broad[1][1] && broad[1][1] == broad[2][2] && broad[1][1] != ' ')
		return broad[0][0];
	if (broad[0][2] == broad[1][1] && broad[1][1] == broad[2][0] && broad[1][1] != ' ')
		return broad[0][2];
	//ƽ��
	return Is_full(broad, row, col);
}

//��������
char Is_full(char broad[Row][Col], int row, int col)
{
	int i = 0;
	for (i = 0;i < row;i++)
	{
		int j = 0;
		for (j = 0;j < col;j++)
		{
			if (broad[i][j] == ' ')
				return 'C';
		}
	}
	return 'Q';
}