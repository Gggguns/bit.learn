#pragma once

#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#define Max_name 10
#define Max_addr 50
#define Add 1
#define Max_sex 5
#define Max_tele 20
#define Max_age 5
typedef struct Peoinf
{
	char name[Max_name];
	char sex[Max_sex];
	char tele[Max_tele];
	char age[Max_age];
	char addr[Max_addr];
}Peoinf;
typedef struct Contact
{
	struct Peoinf* data;
	int sz;
	int Capacity;
}Contact;

//�˵� 
void menu();

//����ͨѶ¼
void load_contact(Contact* con);

//��ʼ��ͨѶ¼
void Init_contact(Contact* con);

//�������
int Check_capacity(Contact* con);

//������ϵ��
void Add_contact(Contact* con);

//����������
int Find_name(Contact* con);

//ɾ����ϵ��
void Del_contact(Contact* con);

//������ϵ��
void Search_contact(Contact* con);

//������ϵ�˵���Ϣ
void Modify_contact(Contact* con);

//��ʾ������ϵ��
void Show_contact(Contact* con);

//����������ϵ��
void Clean_contact(Contact* con);

//������ϵ��
void Sort_contact(Contact* con);

//����������
int cmp1(const void* e1, const void* e2);

//������ϵ����Ϣ
void Save_contact(Contact* con);

//�ݻ���������ϵ����Ϣ
void Destory_contact(Contact* con);

