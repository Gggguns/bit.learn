#define _CRT_SECURE_NO_WARNINGS
#include"contact.h"
void menu()
{
	printf("**********************************************\n");
	printf("*******     0.exit        1.add    ***********\n");
	printf("*******     2.del         3.search ***********\n");
	printf("*******     4.modify      5.show   ***********\n");
	printf("*******     6.                     ***********\n");
	printf("**********************************************\n");
}
void Initcontact(struct contact2* con)
{
	assert(con);
	con->sz = 0;
	memset(con->data, '0', sizeof(con->data));
}
void Add(con2 *con)
{
	assert(con);
	if (con->sz > 100)
	{
		printf("��ϵ���������޷�����\n");
		return;
	}
	printf("����������:>");
	scanf("%s", con->data[con->sz].name);
	printf("������绰:>");
	scanf("%d", &con->data[con->sz].tele);
	printf("����������:>");
	scanf("%d", &con->data[con->sz].age);
	printf("�������ַ:>");
	scanf("%s", con->data[con->sz].addr);
	con->sz++;
}
void Show(con2 *con)
{
	assert(con);
	int i = 0;
	printf("%-10s\t%-15s\t%-4s\t%-10s\n", "����", "�绰", "����", "��ַ");//˫���������ַ��������������ڵ����ַ�
	for(i=0;i<con->sz;i++)
	{
		printf("%-10s\t%-15d\t%-4d\t%-10s\n", con->data[i].name, con->data[i].tele, con->data[i].age, con->data[i].addr);
	}
}
void Del(con2 *con)
{
	assert(con);
	printf("����������:>");
	char name[10];
	scanf("%s", name);
	int ret=Find_name(con,name);
	if (ret == -1)
	{
		printf("�����ڸ���ϵ��\n");
		return;
	}
	int i = 0;
	for (i = ret;i < con->sz;i++)
	{
		con->data[i] = con->data[i + 1];
	}
	con->sz--;
}
int Find_name(con2 *con,char name[])
{
	assert(con);
	int i=0;
	for (i = 0;i < con->sz;i++)
	{
		if (strcmp(con->data[i].name, name) == 0)
			return i;
	}
	return -1;
}
void Search(con2 *con)
{
	assert(con);
	printf("����������:>");
	char name[10];
	scanf("%s", name);
	int ret = Find_name(con, name);
	if (ret == -1)
	{
		printf("�����ڸ���ϵ��\n");
		return;
	}
	printf("%-10s\t%-15s\t%-4s\t%-10s\n", "����", "�绰", "����", "��ַ");//˫���������ַ��������������ڵ����ַ�
	printf("%-10s\t%-15d\t%-4d\t%-10s\n", con->data[ret].name, con->data[ret].tele, con->data[ret].age, con->data[ret].addr);
}
void Mondif(con2* con)
{
	assert(con);
	printf("��������Ҫ����Ϣ���˵�����:>");
	char name[10];
	scanf("%s", name);
	int ret = Find_name(con, name);
	if (ret == -1)
	{
		printf("�����ڸ���ϵ��\n");
		return;
	}
	printf("��������ĵ�����:>");
	scanf("%s", con->data[ret].name);
	printf("��������ĵĵ绰:>");
	scanf("%d", &con->data[ret].tele);
	printf("��������ĵ�����:>");
	scanf("%d", &con->data[ret].age);
	printf("��������ĵĵ�ַ:>");
	scanf("%s", con->data[ret].addr);
}