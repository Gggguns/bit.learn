#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using  namespace std;

struct business
{
public:
	void Modify(string name)
	{
		name = name;
	}
private:
	string name;//����
	string _number;//�绰
	string _address;//��ַ
};
class customer
{
public:
	void Modify(string name)
	{
		name = name;
	}
private:
	int name;//����
	int _number;//�绰
	int _address;//��ַ
};



int main()
{
	//customer��ʵ�������Ķ���
	customer c1;
	customer c2;

	cout << sizeof(c1) << endl;
	cout << sizeof(c2) << endl;


	//c.Modify("M");
	return 0;
}