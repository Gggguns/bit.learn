#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//���ȣ������ȶ���һ�������б�����ͨ����������������ͬ�ĺ��������ԣ���������ֻ��Ҫһ��ģ�����
template<class T>
//��Σ���ɽ���������ʵ��
void Swap(T& left,T& right)
{
	T tmp = left;
	left = right;
	right = tmp;
}
//�������
template<class T2>
T2 Add(const T2& x, const T2& y)
{
	cout << "�����˺���ģ��\n";
	return x + y;
}

//ר�Ŵ���int����
int Add(int left,int right)
{
	cout << "��û�ߺ���ģ��\n";
	return left+right;
}
void testSwap1()
{
	double a = 10.2;
	double b = 12.3;
	cout << "����ǰ��" << endl;
	cout << "a:" << a << ' ' << "b:" << b << endl;
	Swap(a, b);
	cout << "������:\n";
	cout << "a:" << a << ' ' << "b:" << b << endl;
}

void testSwap2()
{
	double a = 10.5;
	int b = 90;
	int c = 10;
	//Swap(a, b);
	//��ʽ����ת�����������ᴫ��ȥ�������Զ��Ƶ�
	cout << Add(b, c) << endl;
	cout << Add(a, (double)b) << endl;//�Ա���b��������ת��

	//��ʾ����ת��
	//cout << Add(a, b) << endl;
	cout << Add<double>(a, b) << endl;
	
}

void testSwap3()
{
	int a = 10;
	int b = 20;
	cout << Add(a, b) << endl;
}

//�ȶ�������б�
template<class Type>
//������ģ��
struct Stack
{
public:
	bool InitStack()
	{
		_size = 0;
		_ptr = (Type*)malloc(sizeof(Type) * 4);
		if (_ptr!=NULL)
		{
			_capacity = 4;
		}
		else
		{
			_capacity = 0;
		}
		return true;
	}
	//��ջ
	bool Push(Type val)
	{
		if (_size == _capacity)
		{
			int newcapacity = _capacity > 0 ? 2 * _capacity : 4;
			Type* ptr = (Type*)realloc(_ptr, sizeof(Type) * newcapacity);
			if (ptr==NULL)
			{
				return false;
			}
			_ptr = ptr;
			ptr = NULL;
			_capacity = newcapacity;
		}
		_ptr[_size++] = val;
		return true;
	}
	
	//��ջ
	bool Pop()
	{
		//...
		if (_size)
		{
			_size--;
			return true;
		}
		return false;
	}

	//ջ��Ԫ��
	Type Top()
	{
		return _ptr[_size - 1];
	}

	//�п�
	bool EmptyStack()
	{
		return _size == 0;
	}
private:
	Type* _ptr;
	int _size;
	int _capacity;
};

void testStack1()
{
	Stack<int> s;
	s.InitStack();
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	s.Push(6);
	s.Push(7);
	while (!s.EmptyStack())
	{
		cout << s.Top() << ' ';
		s.Pop();
	}
}
void testStack2()
{
	//Stack��������֮ǰ��ͬ���������ͣ�������ģ�壬Stack<int> ������������
	Stack<double> s;
	s.InitStack();
	s.Push(1.8);
	s.Push(5.2);
	s.Push(3.3);
	s.Push(4.5);
	s.Push(4.5);
	s.Push(6.6);
	s.Push(7.3);
	while (!s.EmptyStack())
	{
		cout << s.Top() << ' ';
		s.Pop();
	}
}
int main()
{
	//testSwap3();
	testStack2();

	return 0;
}