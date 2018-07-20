#pragma once

#include <iostream>

using namespace std;

typedef int DataType;

struct ListNode
{
	DataType _val;
	ListNode* _next;
	ListNode* _prev;

	ListNode(const DataType val = 0)
		:_val(val)
		, _next(NULL)
		, _prev(NULL)
	{}
};

class List
{

public:
	List()
		:_head(NULL)
		, _tail(NULL)
		, _size(0)
	{
		_head = new Node();
		_tail = _head;
		_head->_next = _tail;
		_head->_prev = _tail;
	}

	List(List& l)
	{
		//法一：赋用push_back
		_head = new Node(l._head->_val);
		_tail = _head;
		_head->_next = _tail;
		_head->_prev = _tail;
		_size = 1;

		Node* cur = l._head->_next;
		while (cur != _head)
		{
			push_back(cur->_val);
			cur = cur->_next;
		}

		//法二：自行拷贝，不赋用push_back
		//Node* lcur = l._head;
		//lcur = l._head;
		//_head = new Node(lcur->_val);
		//lcur = lcur->_next;
		//Node* cur = _head;
		//while (lcur != l._head)
		//{
		//	cur->_next = new Node(lcur->_val);
		//	lcur = lcur->_next;
		//	cur->_next->_prev = cur;
		//	cur = cur->_next;
		//}
		//_tail = cur;
		//cur->_next = _head;
		//_head->_prev = _tail;
		//_size = l._size;
	}

	~List()
	{
		Node* cur = _head;
		Node* next = _head->_next;
		while (next != _head)
		{
			delete cur;
			cur = next;
			next = cur->_next;
		}
		delete _tail;
	}

	//Insert element at beginning
	void push_front(DataType val)
	{
		if (_size == 0)
		{
			_head->_val = val;
		}
		else
		{
			Node* tmp = new Node(val);
			tmp->_next = _head;
			tmp->_prev = _tail;
			_head->_prev = tmp;
			_tail->_next = tmp;
			_head = tmp;
		}
		_size++;
	}

	void pop_front()
	{
		if (_size != 0)
		{
			if (_size > 1)
			{
				_head = _head->_next;
				_head->_prev = _tail;
				delete _tail->_next;
				_tail->_next = _head;
			}
			_size--;
		}

	}

	void push_back(DataType val)
	{
		if (_size == 0)
		{
			_head->_val = val;
		}
		else
		{
			_tail->_next = new Node(val);
			_tail = _tail->_next;
			_tail->_next = _head;
			_head->_prev = _tail;
		}
		_size++;
	}

	void pop_back()
	{
		if (_size != 0)
		{
			if (_size > 1)
			{
				_tail = _tail->_prev;
				delete _tail->_next;
				_tail->_next = _head;
				_head->_prev = _tail;
			}
			_size--;
		}
	}

	void insert(size_t pos, DataType val)
	{
		Node* cur = _head;
		for (int i = 0; i < pos; i++)
		{
			cur = cur->_next;
		}
		Node* tmp = new Node(val);
		cur->_prev->_next = tmp;
		tmp->_prev = cur->_prev;
		tmp->_next = cur;
		cur->_prev = tmp;
		if (cur == _head)
		{
			if (pos == 0)
				_head == cur->_prev;
			else
				_tail = _tail->_next;
		}
		_size++;
	}

	void erase(size_t pos)
	{
		if (_size != 0)
		{
			if (_size != 1)
			{
				Node* cur = _head;
				for (int i = 0; i < pos; i++)
					cur = cur->_next;
				if (cur == _head)
					_head = _head->_next;
				if (cur == _tail)
					_tail = _tail->_prev;
				cur->_next->_prev = cur->_prev;
				cur->_prev->_next = cur->_next;
				delete cur;
			}
			_size--;
		}
	}



	void swap(List& l)
	{
		std::swap(_head, l._head);
		std::swap(_tail, l._tail);
		std::swap(_size, l._size);
	}

	void resize(size_t size, DataType val = 0)
	{
		if (_size > size)
		{
			for (int i = size; i < _size; i++)
			{
				pop_back();
			}
		}
		else if (_size < size)
		{
			for (int i = _size; i < size; i++)
			{
				push_back(val);
			}
		}
	}

	void clear()
	{
		for (int i = 0; i < _size; i++)
		{
			pop_back();
		}
	}

	void remove(DataType val)
	{
		Node* cur = _head;
		for (int i = 0; i < _size; i++)
		{
			if (cur->_val == val)
			{
				cur = erase(cur);
				i--;
			}
			cur = cur->_next;
		}
	}

	void unique()
	{
		sort();
		Node* cur = _head;
		for (int i = 0; i < _size; i++)
		{
			if (cur->_val == cur->_next->_val)
			{
				erase(cur->_next);
				i--;
			}
		}
	}

	void sort()
	{
		Node* cur = _head;
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size - i - 1; j++)
			{
				if (cur->_val > cur->_next->_val)
					std::swap(cur->_val, cur->_next->_val);
			}
		}
	}
private:
	ListNode* erase(ListNode* node)
	{
		Node* ret = node->_next;
		if (_size != 0)
		{
			if (_size != 1)
			{
				if (node == _head)
					_head = _head->_next;
				else if (node == _tail)
					_tail = _tail->_prev;
				node->_next->_prev = node->_prev;
				node->_prev->_next = node->_next;
				delete node;
			}
			_size--;
		}
		return ret;
	}
private:
	typedef ListNode Node;
	Node* _head;
	Node* _tail;
	size_t _size;
};