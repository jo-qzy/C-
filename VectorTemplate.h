#pragma once

#include <iostream>

using namespace std;

template <class T>

class Vector
{
public:
	Vector()
		:_data(NULL)
		,_size(0)
		,_capacity(0)
	{}

	Vector(const Vector& v)
	{
		_data = NULL;
		if (v._capacity != 0)
		{
			_data = new T[_capacity];
			for (int i = 0; i < _size; i++)
			{
				_data[i] = v._data[i];
			}
		}
		_size = v._size;
		_capacity = v._capacity;
	}

	~Vector()
	{
		if (_data != NULL)
			delete[] _data;
	}

	Vector& operator=(Vector v)
	{
		std::swap(_data, v._data);
		std::swap(_size, v._size);
		std::swap(_capacity, v._capacity);
		return *this;
	}

	void push_back(T& val)
	{
		if (_size == _capacity)
			expand();
		_data[_size - 1] = val;
		_size++;
	}
private:
	void expand()
	{

	}
private:
	T* _data;
	int _size;
	int _capacity;
};

