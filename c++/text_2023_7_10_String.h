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
		void reserve(size_t size)
		{
			assert(size >= 0);
			if(size>_capacity)
			{
				char* ret = new char[size + 1];
				_capacity = size + 1;
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
	private:
		size_t _size;
		size_t _capacity;
		char* _str;
		const static size_t npos;
	};
	//const size_t string::npos = -1;
}