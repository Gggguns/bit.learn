#pragma once
#include<iostream>
#include"reverse_iterator.h"
using namespace std;
namespace zjh
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}
		vector(size_t n, const T& val = T())
		{
			_start = new T[n](val);
			_finish = _start + n;
			_endofstorage=_finish;
		}
		//����
		vector(const vector<T>& v)
		{
			size_t len = T.size();
			if(capacity()<len)
				reserve(len);
			int i = 0;
			for (i = 0;i < len;i++)
			{
				_start[i] = v._start[i];
			}
			_finish = _start + len;
		}
		template<class InputIterator>

		vector(InputIterator first, InputIterator last)
		{
			iterator it = begin();
			while (first != last)
			{
				*it = *first;
				it++;
				first++;
			}
		}
		vector<T> operator=(const vector<T>& v)
		{
			size_t len = v.size();
			if (capacity() < len)
				reserve(len);
			int i = 0;
			for (i = 0;i < len;i++)
			{
				_start[i] = v._start[i];
			}
			_finish = _start + len;
			return *this;
		}
		
		~vector()
		{
			delete[]_start;
			_start = nullptr;
			_finish = nullptr;
			_endofstorage = nullptr;
		}
		//������
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}
		const_iterator cbegin()const
		{
			return _start;
		}
		const_iterator cend()const
		{
			return _finish;
		}
		//����
		void reserve(size_t n)
		{
			if (capacity() < n)
			{
				iterator tmp = new T[n];
				int i = 0;
				while (i<size())
				{
					tmp[i] = _start[i];
					i++;
				}
				size_t oldsize = size();
				delete[] _start;
				_start = tmp;
				_finish = tmp + oldsize;
				_endofstorage = tmp + n;
			}
		}
		void resize(size_t n, const T& value = T())
		{
			if (capacity() < n)
			{
				iterator tmp = new T[n];
				delete[] _start;
				_start = tmp;
				_endofstorage = _start + n;
			}
			int i = 0;
			for (i = 0;i < n;i++)
			{
				_start[i] = value;
			}
			_finish = _start + n;
			
		}
		//vector�Ĵ�С
		size_t size()const
		{
			return _finish - _start;
		}
		//vector������
		size_t capacity()const
		{	
			return _endofstorage - _start;
		}
		//���������������
		T& operator[](size_t pos)
		{
			assert(pos < capacity());
			return _start[pos];
		}

		const T& operator[](size_t pos)const
		{
			assert(pos < capacity());
			return _start[pos];
		}
		//β��
		void push_back(const T& x)
		{
			if (capacity() == size())
			{
				int newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			*_finish = x;
			_finish++;
		}
		//βɾ
		void pop_back()
		{
			_finish--;
		}
		//����
		void swap(vector<T>& v)
		{
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_endofstorage, v._endofstorage);
		}
		//posλ�ò���
		iterator insert(iterator pos, const T& x)
		{
			size_t n = pos - begin();
			if (capacity() == size())
			{
				int newcapacity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newcapacity);
			}
			iterator end1= end();
			pos = begin() + n;
			while (end1 != pos)
			{
				*end1 = *(end1-1);
				end1--;
			}
			_finish++;
			*pos = x;
			return pos;
		}
		//posλ��ɾ��
		iterator erase(iterator pos)
		{
			iterator end = pos;
			_finish--;
			while (end - 1 != _finish)
			{
				*end = *(end + 1);
				end++;
			}
			return pos;
		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
	

}
