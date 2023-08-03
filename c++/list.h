#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<assert.h>
using namespace std;
namespace zjh
{
	template<class T>
	struct list_node
	{
		list_node* prev;
		list_node* next;
		T value;

		list_node()
			:prev(nullptr)
			,next(nullptr)
			,value(T())
		{} 
	};
	template<class T,class Ref,class Ptr>
	struct list_iterator
	{
		
		typedef list_iterator<T, Ref, Ptr> self;
		list_node<T>* _node;
		//list_iterator�ĳ�ʼ��
		list_iterator(list_node<T>* node)
			:_node(node)
		{}

		//���������*
		Ref  operator*()
		{
			return _node->value;
		}

		//���������++
		self& operator++()
		{
			_node = _node->next;
			return *this;
		}
		self operator++(int)
		{
			self ret = *this;
			_node = _node->next;
			return ret;
		}
		//���������->
		Ptr operator->()
		{
			return &(_node->value);
		}
		//���������--
		self& operator--()
		{
			_node = _node->prev;
			return *this;
		}
        self operator--(int)
		{
			self ret = *this;
			_node = _node->prev;
			return ret;
		}
		bool operator!=(const self& l)
		{
			return !(_node == l._node);
		}
		bool operator==(const self& l)
		{
			return _node == l._node;
		}
	};
	template<class T>
	class list
	{
	public:
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;
		typedef list_node<T> Node;
		void empty_init()
		{
			_head = new Node;
			_head->next = _head;
			_head->prev = _head;
		}
		list()
		{
			empty_init();
		}
		list(int n, const T& value = T())
		{
			empty_init();
			int i = 0;
			for (i = 0;i < n;i++)
			{
				Node* node = new Node;
				node->value = value;
				node->next = _head->next;
				_head->next->prev = node;
				node->prev = _head;
				_head->next = node;
			}
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();
			InputIterator it = first;
			while (it != last)
			{
				Node* node = new Node;
				*node = *it._node;
				it++;
				node->prev = _head->prev;
				_head->prev->next = node;
				node->next = _head;
				_head->prev = node;
			}
		}
		list(const list<T>& l)
		{
			empty_init();
			zjh::list<T>::const_iterator it = l.begin();
			while (it != l.end())
			{
				Node* node = new Node;
				*node = *it._node;
				it++;
				node->prev = _head->prev;
				_head->prev->next = node;
				node->next = _head;
				_head->prev = node;
			}
		}
		//list<T>�Ľ���
		void Swap( list<T>& l)
		{
			std::swap(_head, l._head);
		}
		//��ֵ����=����
		list<T>& operator=(list<T> l)
		{
			clear();
			Swap(l);
			return *this;
		}
		//������ʵ��
		iterator begin()
		{
			return _head->next;
		}
		iterator end()
		{
			return _head;
		}
		const_iterator begin()const
		{
			return _head->next;
		}
		const_iterator end()const
		{
			return  _head;
		}
		//list��������
		iterator erase(iterator pos)
		{
			Node* cur = pos._node;
			Node* prev = pos._node->prev;
			prev->next = cur->next;
			cur->next->prev = prev;
			pos._node = prev->next;
			delete cur;
			return pos;
		}
		//��������
		void clear()
		{
			zjh::list<T>::iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		//���ݸ���
		size_t size()const
		{
			size_t i = 0;
			zjh::list<T>::const_iterator it = begin();
			while (it != end())
			{
				i++;
				it++;
			}
			return i;
		}
		//�鿴list����Ԫ�ؼ�βԪ��
		T& front()
		{
			assert(size() != 0);
			return _head->next->value;
		}
		const T& front()const
		{
			assert(size() != 0);
			return _head->next->value;
		}
		T& back()
		{
			assert(size() != 0);
			return _head->prev->value;
		}
		const T& back()const
		{
			assert(size() != 0);
			return _head->prev->value;
		}
		//listβ��
		void push_back(const T&x)
		{
			Node* newnode = new Node;
			(*newnode).value = x;
			newnode->next = _head;
			newnode->prev = _head->prev;
			_head->prev->next = newnode;
			_head->prev = newnode;
		}
		//listβɾ
		void pop_back()
		{
			assert(size() != 0);
			erase(--end());
		}
		//listͷ��
		void push_front(const T& x)
		{
			Node* newnode = new Node;
			(*newnode).value = x;
			newnode->next = _head->next;
			newnode->prev = _head;
			_head->next->prev = newnode;
			_head->next = newnode;
		}
		//listͷɾ
		void pop_front()
		{
			assert(size() != 0);
			erase(begin());
		}
		//posλ�õĲ���
		iterator insert(iterator pos, const T& value)
		{
			Node* newnode = new Node;
			newnode->value = value;
			newnode->next = pos._node;
			newnode->prev = pos._node->prev;
			pos._node->prev->next = newnode;
			pos._node->prev = newnode;
			pos._node = newnode;
			return pos;
		}
		//list���п�
		bool empty()
		{
			return size() == 0;
		}
		//��������
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
	private:
		Node* _head;
	};
	
}
