#pragma once
#include<stdio.h>
#include<string.h>
#include<assert.h>
#define exit 0
#define add  1
#define del 2
#define search 3
#define modify 4
#define show 5
#define MAX_name 10
#define MAX_addr 20
#define MAX_data 100
void menu();
void Initcontact(struct contact2 *con);
struct contact1
{
	char name[MAX_name];
	int tele;
	int age;
	char addr[MAX_addr];
};
typedef struct contact2
{
	struct contact1 data[MAX_data];
	int sz;
}con2;
con2 con;
//����������
int Find_name(con2 *con, char name[]);
//������ϵ��
void Add(con2 *con);
//��ʾ��ϵ��
void Show(con2 *con);
//ɾ����ϵ��
void Del(con2 *con);
//������ϵ��
void Search(con2 *con);
//�޸���ϵ��
void Mondif(con2 *con);