#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<time.h>
#define Col 3
#define Row 3

//�˵�
void menu();

//��Ϸ
void Game();

//���̳�ʼ��
void Init_broad(char broad[Row][Col], int row, int col);

//�������
void Playmove(char broad[Row][Col], int row, int col);

//��������
void Conputurmove(char broad[Row][Col], int row, int col);

//��ӡ����
void Printf_broad(char broad[Row][Col], int row, int col);

//˭Ӯ��
char Is_win(char broad[Row][Col], int row, int col);

//��������
char Is_full(char broad[Row][Col], int row, int col);