#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

//ģ��stringʹ�õ������ռ�
namespace zjh
{
	//����
	template<typename T>
	void Swap(T& p1, T& p2)
	{
		T tmp = p1;
		p1 = p2;
		p2 = tmp;
	}
	class string
	{
		friend istream& operator>>(istream& cin, string& s);
		friend ostream& operator<<(ostream& cout, const string& s);
	public:
		//��ʼ��
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_size + 1];
			memmove(_str, str, _size + 1);
		}
		//���ռ�
		void reserve(size_t n)
		{
			assert(n >= 0);
			if (n > _capacity)
			{
				char* ret = new char[n + 1];
				_capacity = n;
				memmove(ret, _str, _size + 1);
				delete[] _str;
				_str = ret;
				_str[_capacity] = '\0';
			}
		}
		//��������
		string(const string& s)
		{
			_size = s._size;
			_capacity = s._capacity;
			_str = new char[s._capacity + 1];
			memmove(_str, s._str, _size + 1);
		}
		//�����ͷſռ�
		~string()
		{
			_size = 0;
			_capacity = 0;
			delete[] _str;
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
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
			_str[_size] = c;
			_size++;
			_str[_size] = '\0';
		}
		//׷���ַ���
		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			memmove(_str + _size, str, len + 1);
			_size += len;
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
			if (n > _capacity)
			{
				char* ret = new char[n + 1];
				_capacity = n;
				memmove(ret, _str, n);
				delete(_str);
				_str = ret;
				memset(_str + _size, c, _capacity - _size);
			}
			_size = n;
			_str[n] = '\0';
		}
		//����
		void swap(string& s)
		{
			zjh::Swap(_size, s._size);
			zjh::Swap(_capacity, s._capacity);
			zjh::Swap(_str, s._str);
		}
		//����c��string�е�һ�γ��ֵ�λ��
		size_t find(char c, size_t pos = 0) const
		{
			size_t i = 0;
			for (i = pos;i < _size;i++)
			{
				if (_str[i] == c)
					return i;
			}
			return npos;
		}
		// �����Ӵ�s��string�е�һ�γ��ֵ�λ��
		size_t find(const char* s, size_t pos = 0) const
		{
			size_t str1 = 0;
			size_t str2 = 0;
			size_t cp = 0;
			while (cp < _size)
			{
				str1 = cp;
				str2 = 0;
				while (s[str2] != '\0')
				{
					if (_str[str1++] != s[str2++])
						break;
				}
				if (s[str2] == '\0')
					return cp;
				cp++;
			}
			return npos;
		}
		string substr(size_t pos = 0, size_t len = npos) const
		{
			assert(pos < _size);
			string tmp;
			size_t n = len;
			if (pos + len > _size || len == npos)
			{
				n = _size - pos;
			}
			tmp.resize(n);
			int i = 0;
			for (i = 0;i < n;i++)
			{
				tmp._str[i] = _str[pos + i];
			}
			tmp._str[pos + i] = '\0';
			return tmp;
		}
		// ��posλ���ϲ����ַ�c/�ַ���str�������ظ��ַ���λ��
		string& insert(size_t pos, char c)
		{
			assert(pos < _size);
			size_t end = _size;
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}
			while (end >= pos && end != npos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = c;
			_size++;
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			size_t n = strlen(str);
			if (_size + n > _capacity)
			{
				size_t newcapacity = _capacity + n;
				reserve(newcapacity);
			}
			size_t end = _size;
			while (end >= pos && end != npos)
			{
				_str[end + n] = _str[end];
				end--;
			}
			_size += n;
			int i = 0;
			for (i = 0;i < n;i++)
			{
				_str[pos + i] = str[i];
			}
			return *this;
		}
		//�����ŷ�������
		char& operator[](size_t index)
		{
			assert(index < _size);
			return _str[index];
		}

		const char& operator[](size_t index)const
		{
			assert(index < _size);
			return _str[index];
		}
		//��=����
		string& operator+=(char c)
		{
			this->push_back(c);
			return *this;
		}
		
		string& operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}
		//��ֵ����
		string& operator=(string tmp)
		{
			this->swap(tmp);
			return *this;
		}
		//string�ıȽϴ�С����
		bool operator<(const string& s)
		{
			size_t end1 = 0;
			size_t end2 = 0;
			while (end1 < _size && end2 < s._size)
			{
				if (_str[end1] > s._str[end2])
					return false;
				end1++;
				end2++;
			}
			if (_size < s._size)
				return true;
			else
				return false;
		}
		bool operator<=(const string& s)
		{
			if (*this == s || *this < s)
				return true;
			else
				false;
		}
		bool operator>(const string& s)
		{
			if (*this <= s)
				return false;
			else
				return true;
		}
		bool operator>=(const string& s)
		{
			if (*this < s)
				return false;
			else
				return true;
		}
		bool operator==(const string& s)
		{
			if (_size != s._size)
				return false;
			size_t end1 = 0;
			size_t end2 = 0;
			while (end1 < _size && end2 < s._size)
			{
				if (_str[end1] != s._str[end2])
					return false;
				end1++;
				end2++;
			}
			return true;
		}
		bool operator!=(const string& s)
		{
			return !(*this == s);
		}
	private:
		size_t _size;
		size_t _capacity;
		char* _str;
	public:
		const static size_t npos;
	};
	const  size_t string::npos = -1;
	//ģ��string�����������
	istream& operator>>(istream& in, string& s)
	{
		s.clear();
		char ch=in.get();
		char buffer[128] = {0};
		size_t i = 0;
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}
		while (ch != ' ' && ch != '\n')
		{
			buffer[i++] = ch;
			if (i == 127)
			{
				buffer[i] = '\0';
				s.append(buffer);
				i = 0;
			}
			ch = in.get();
		}
		if (i != 0)
			s.append(buffer);
		return in;
	}
	ostream& operator<<(ostream& out, const string& s)
	{
		size_t i = 0;
		for (i = 0;i < s._size;i++)
		{
			out << s._str[i];
		}
		return out;
	}
}
