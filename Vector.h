#pragma once

#include <iostream>

using namespace std;

typedef int DataType;

//模拟实现vector，不涉及迭代器，所以插入和删除使用下标而非迭代器

class Vector
{
public:
	//Member functions
	//constructor
	Vector()
		:_a(NULL)
		,_capacity(0)
		,_size(0)
	{
		_a = new DataType[10];
		_capacity = 10;
	}

	Vector(const Vector &v)
	{
		_a = new DataType[v._capacity];
		memcpy(_a, v._a, v._size * sizeof(DataType));
		_capacity = v._capacity;
	}

	//destrusctor
	~Vector()
	{
		delete[] _a;
	}

	Vector& operator=(const Vector& v)
	{
		Vector tmp = v;
		std::swap(_a, tmp._a);
		_capacity = tmp._capacity;
		_size = tmp._size;

		//if (_capacity < v._size)
		//{
		//	expand(v._capacity);
		//}
		//_a = new DataType[v._capacity];
		//memcpy(_a, v._a, v._size * sizeof(DataType));
		//_capacity = v._capacity;

		return *this;
	}

	//Capacity
	
	//Return size
	size_t size()//Return size
	{
		return _size;
	}

	//Change size
	void resize(size_t size, DataType val = 0)//问题：此处val如何让其随类型变化，目前只支持整型
	{
		if (_capacity < size)
		{
			expand(size);
		}
		else if (_capacity > size)
		{
			if (_size < size)
			{
				_size = size;
			}
			expand(size);
		}
		memset(_a, val, (_capacity - _size) * sizeof(DataType));
	}

	//Return size of allocated storage capacity
	size_t capacity()
	{
		return _capacity;
	}

	//Test whether vector is empty
	bool empty()
	{
		if (_size == 0)
			return true;
		return false;
	}

	//Request a change in capacity
	void reserve(size_t size)
	{
		if (size > _capacity)
			expand(size);
	}

	//Element access

	//Access element
	DataType operator[](size_t position)
	{
		return *(_a + position);
	}

	//Access first element
	DataType front()
	{
		return *(_a + 0);
	}

	//Access last element
	DataType back()
	{
		return *(_a + _size - 1);
	}

	//Modifiers

	//Add element at the end
	void push_back(DataType data)
	{
		insert(_size, data);
		//if (_size == _capacity)
		//	expand(_capacity * 2);
		//*(_a + _size) = data;
		//_size++;
	}

	//Delete last element
	void pop_back()
	{
		_size--;
	}

	//Insert elements
	void insert(size_t pos, DataType data)
	{
		if (pos > _size)
			return;
		if (_size == _capacity)
			expand(_capacity * 2);
		memmove(_a + pos + sizeof(DataType), _a + pos, (_size - pos) * sizeof(DataType));
		*(_a + pos) = data;
		_size++;
	}

	//Erase elements
	void erase(size_t pos)
	{
		if (pos >= _size)
			return;
		memmove(_a + pos, _a + pos + sizeof(DataType), (_size - pos - 1) * sizeof(DataType));
		_size--;
	}

	//Swap content
	void swap(size_t pos1, size_t pos2)
	{
		if (pos1 < _size && pos2 < _size)
			std::swap(*(_a + pos1), *(_a + pos2));
	}

	//Clear content
	void clear()
	{
		_size = 0;
	}
private:
	void expand(size_t capacity)
	{
		_capacity = capacity;
		DataType* tmp = new DataType[_capacity];
		memcpy(tmp, _a, _size * sizeof(DataType));
		delete[] _a;
		_a = tmp;
	}
private:
	DataType* _a;
	size_t _capacity;
	size_t _size;

	static size_t npos;
};

size_t Vector::npos = -1;

void test()
{
	Vector v;
	cout << "push_back:";
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for (int i = 0; i < 10; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << "pop_back:";
	v.pop_back();
	v.push_back(100);

	cout << "operator=:";
	Vector v1;
	v1 = v;
	for (int i = 0; i < 10; i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;

	cout << "front:" << v.front() << endl;
	cout << "back:" << v.back() << endl;

	cout << "size:" << v.size() << endl;
	cout << "capacity:" << v.capacity() << endl;
	cout << "empty:" << v.empty() << endl;

	v.clear();
	cout << "clear:" << "new size" << v.size() << endl;
}