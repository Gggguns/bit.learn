#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
struct ListNode
{
	ListNode(int val)
		:_val(val)
	{
		cout << "��ʼ��" << endl;
	}
	int _val;
};
void testlist1()
{
	//���ռ�+���ù��캯����ʼ��
	ListNode* head = new ListNode(1);
}
void testlist2()
{
	//ע�⣺head����ָ���ֻ������һ�ξ��к�ListNode����ͬ����С�Ŀռ䣬���㲻�϶�����Ϊ���캯����ûִ��
	ListNode* head = (ListNode*)malloc(sizeof(ListNode));
	new(head)ListNode(8);//ע�⣺���ListNode���޲����Ĺ��캯����������Բ�����ʼֵ8��

}
int main()
{
	testlist2();
	/*int* ptr = new int(10);

	int* p = new int[10] {1,2,3,4,5,6,7,8,9,10};
	int i = 0;
	for (i = 0;i < 10;i++)
	{
		cout << p[i] << endl;
	}
	
	
	delete ptr;
	delete[] p;*/
	return  0;
}