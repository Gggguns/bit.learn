#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//ģ��stringʹ�õ������ռ�
namespace zjh
{
	class string
	{
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}