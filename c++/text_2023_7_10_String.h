#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<assert.h>
using namespace std;

//ģ��stringʹ�õ������ռ�
namespace zjh
{
	class string
	{
		friend istream& operator>>(istream& cin, string& s);
		friend ostream& operator<<(ostream& cout, const string& s);
	public:
		//��ʼ��
		string(const char*str)
		{
			_size = strlen(str);
			_capacity = _size+1;
			_str = new char[_capacity];
			strcpy(_str, str);
		}
		//���ռ�
		void reserve(size_t n)
		{
			assert(n >= 0);
			if(n>=_capacity-1)
			{
				char* ret = new char[n + 1];
				_capacity = n + 1;
				strcpy(ret, _str);
				delete(_str);
				_str = ret;
			}
		}
		//��������
		string(const string& s) 
		{
			_size = s._size;
			_capacity = s._capacity;
			_str = new char[s._capacity];
			strcpy(_str, s._str);
		}
		//�����ͷſռ�
		~string()
		{
			_size = 0;
			_capacity = 0;
			delete(_str);
		}
		//
		//������
		typedef char* iterator;
		//��ʼλ��
		iterator begin()
		{
			return _str;
		}
		const iterator begin()const
		{
			return _str;
		}
		//ĩβλ��
		iterator end()
		{
			return _str + _size;
		}
		const iterator end()const
		{
			return _str + _size;
		}
		//β��һ���ַ�
		void push_back(char c)
		{
			_size++;
			reserve(_size);
			_str[_size - 1] = c;
			_str[_size] = '\0';
		}
		//׷���ַ���
		void append(const char* str)
		{
			int len = strlen(str);
			_size += len;
			reserve(_size);
			strcpy(_str + _size - len, str);
		}
		//��ȡ�ַ���
		const char* c_str()const
		{
			return _str;
		}
		//��ȡ���ݸ���
		size_t size()const
		{
			return _size;
		}
		//��ȡ��������
		size_t capacity()const
		{
			return _capacity;
		}
		//�������
		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}
		//�п�
		bool empty()const
		{
			return _size == 0;
		}
		//���ռ�+��ʼ��
		void resize(size_t n, char c = '\0')
		{
			assert(n >= 0);
			if (n >= _capacity - 1)
			{
				char* ret = new char[n + 1];
				_capacity = n + 1;
				strcpy(ret, _str);
				delete(_str);
				_str = ret;
				memset(_str + _size , c, _capacity - _size);
			}
			_size = n;
			_str[n] = '\0';
		}
	private:
		size_t _size;
		size_t _capacity;
		char* _str;
		const static size_t npos;
	};
	//const size_t string::npos = -1;
}