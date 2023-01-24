#define _CRT_SECURE_NO_WARNINGS
#include"better_contact.h"
//�˵�
void menu(void)
{
	printf("*************************************\n");
	printf("******   1.Add      2.Del     *******\n");
	printf("******   3.Search   4.Modify  *******\n");
	printf("******   5.Show     6.Clean   *******\n");
	printf("******   7.Sort               *******\n");
	printf("*************************************\n");
	return;
}

//����ͨѶ¼
void load_contact(Contact* con)
{
	FILE* pf = fopen("cc.txt", "rb");
	if (pf == NULL)
	{
		perror("load_contact");
		return;
	}
	else
	{
		int i = 0;
		Peoinf tmp = { 0 };
		while (fread(&tmp, sizeof(Peoinf), 1, pf))
		{
			Check_capacity(con);
			con->data[i] = tmp;
			i++;
			con->sz++;
		}
		fclose(pf);
		pf = NULL;
	}
}

//��ʼ��ͨѶ¼����
void Init_contact(Contact* con)
{
	assert(con);
	con->sz = 0;
	Peoinf* ptr = calloc(3, sizeof(struct Peoinf));
	if (NULL == ptr)
	{
		perror("Init_contact calloc");
		return;
	}
	else
	{
		con->data = ptr;
		con->Capacity = 3;
		load_contact(con);
		return;
	}
}
//�����������
int Check_capacity(Contact* con)
{
	assert(con);
	if (con->sz == con->Capacity)
	{
		Peoinf* prt = realloc(con->data, (con->Capacity + 2) * sizeof(Peoinf));
		if (NULL == prt)
		{
			perror("Check_capacipy realloc");
			return 0;
		}
		else
		{
			con->data = prt;
			con->Capacity = con->Capacity + 2;
			printf("���ݳɹ�\n");
			return 1;
		}
	}
	return 1;
}
//������ϵ�˺���
void Add_contact(Contact* con)
{
	assert(con);
	int ret = Check_capacity(con);
	if (0 == ret)
	{
		printf("ͨѶ¼��������������ʧ�ܣ��޷�����������ϵ��\n");
		return;
	}
	else
	{
		printf("����������:>");
		scanf("%s", con->data[con->sz].name);
		printf("�������Ա�:>");
		scanf("%s", con->data[con->sz].sex);
		printf("����������:>");
		scanf("%s", con->data[con->sz].age);
		printf("������绰:>");
		scanf("%s", con->data[con->sz].tele);
		printf("�������ַ:>");
		scanf("%s", con->data[con->sz].addr);
		con->sz++;
		return;
	}
}
//���������Һ���
int Find_name(Contact* con)
{
	assert(con);
	char name[Max_name];
	scanf("%s", name);
	for (int i = 0;i < con->sz; i++)
	{
		if (strcmp((con->data[i].name), name) == 0)
		{
			return i;
		}
	}
	return -1;
}

//ɾ����ϵ�˺���
void Del_contact(Contact* con)
{
	assert(con);
	printf("������Ҫɾ����ϵ�˵�����:>");
	int ret = Find_name(con);
	if (-1 == ret)
	{
		printf("����ϵ�˲�����\n");
		return;
	}
	else
	{
		for (int i = ret;i < con->sz - 1;i++)
		{
			con->data[i] = con->data[i + 1];
		}
		con->sz--;
		return;
	}
}

//������ϵ�˺���
void Search_contact(Contact* con)
{
	assert(con);
	printf("������Ҫ������ϵ�˵�����:>");
	int ret = Find_name(con);
	if (-1 == ret)
	{
		printf("����ϵ�˲�����\n");
		return;
	}
	else
	{
		printf("%-10s\t%-1s\t%-15s\t%-4s\t%-10s\n", " ����", "�Ա�", "�绰", "����", "��ַ");
		printf("%-10s\t%-1s\t%-15s\t%-4s\t%-10s\n", con->data[ret].name, con->data[ret].sex, con->data[ret].tele, con->data[ret].age, con->data[ret].addr);
		return;
	}
}

//������ϵ�˵���Ϣ����
void Modify_contact(Contact* con)
{
	assert(con);
	printf("������Ҫ������Ϣ��ϵ�˵�����:>");
	int ret = Find_name(con);
	if (-1 == ret)
	{
		printf("����ϵ�˲�����\n");
		return;
	}
	else
	{
		printf("����������:>");
		scanf("%s", con->data[ret].name);
		printf("�������Ա�:>");
		scanf("%s", con->data[ret].sex);
		printf("������绰:>");
		scanf("%s", con->data[ret].tele);
		printf("����������:>");
		scanf("%s", con->data[ret].age);
		printf("�������ַ:>");
		scanf("%s", con->data[ret].addr);
		return;
	}
}

//��ʾ������ϵ�˺���
void Show_contact(Contact* con)
{
	printf("%-10s\t%-1s\t%-15s\t%-4s\t%-10s\n", " ����", "�Ա�", "�绰", "����", "��ַ");
	for (int i = 0;i < con->sz;i++)
	{
		printf("%-10s\t%-1s\t%-15s\t%-4s\t%-10s\n", con->data[i].name, con->data[i].sex, con->data[i].tele, con->data[i].age, con->data[i].addr);
	}
	return;
}

//����������ϵ�˺���
void Clean_contact(Contact* con)
{
	assert(con);
	free(con->data);
	con->data = NULL;
	Init_contact(con);
	return;
}

//����������
int cmp1(const void* e1, const void* e2)
{
	return strcmp(((Peoinf*)e1)->name, ((Peoinf*)e2)->name);
}

//������ϵ�˺���
void Sort_contact(Contact* con)
{
	assert(con);
	qsort(con->data, con->sz, sizeof(Peoinf), cmp1);
	return;
}


//����������ϵ����Ϣ����
void Save_contact(Contact* con)
{
	FILE* pf = fopen("cc.txt", "wb");
	if (NULL == pf)
	{
		perror("Save_contact");
		return;
	}
	else
	{
		int i = 0;
		for (i = 0;i < con->sz;i++)
		{
			fwrite(con->data + i, sizeof(Peoinf), 1, pf);
		}
		fclose(pf);
		pf = NULL;
		printf("����ɹ�\n");
	}
}


//�ݻ���������ϵ����Ϣ����
void Destory_contact(Contact* con)
{
	assert(con);
	free(con->data);
	con->data = NULL;
	return;
}
