#pragma once
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#define Max_name 10
#define Max_addr 50
#define Add 1
struct Peoinf
{
	char name[Max_name];
	char sex;
	int tele;
	int age;
	char addr[Max_addr];
};
typedef struct Contact
{
	struct Peoinf* data;
	int sz;
	int Capacity;
}Contact;
Contact con;
//�˵� 
void menu()
//��ʼ��ͨѶ¼
void Init_contact(Contact* con);
//�������
void Check_capacity(Contact* con);
//������ϵ��
void Add_contact(Contact* con);
//����������
void Find_name(Contact* con);
//ɾ����ϵ��
void Del_contact(Contact* con);
//������ϵ��
void Searcch_contact(Contact* con);
//������ϵ�˵���Ϣ
void Modify_contact(Contact* con);
//��ʾ������ϵ��
void Show_contact(Contact* con);
//����������ϵ��
void Clean_contact(Contact* con);
//������ϵ��
void Sort_contact(Contact* con);
//������ϵ����Ϣ
void Save_contact(Contact* con);
//�ݻ���������ϵ����Ϣ
void Destory(Contact* con);

