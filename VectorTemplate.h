#pragma once

#include <iostream>
#include <cassert>
#include <string>

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

	Vector(const Vector<T>& v)
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

	Vector<T>& operator=(Vector<T> v)
	{
		std::swap(_data, v._data);
		std::swap(_size, v._size);
		std::swap(_capacity, v._capacity);
		return *this;
	}

	const T& operator[](size_t pos) const
	{
		assert(pos < _size);
		return _data[pos];
	}

	T& operator[](size_t pos)
	{
		assert(pos < _size);
		return _data[pos];
	}

	void insert(size_t pos, const T& val)
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			_capacity = (_capacity == 0) ? 5 : _capacity * 2;
			T* tmp_data = new T[_capacity];
			for (size_t i = 0; i < pos; i++)
			{
				tmp_data[i] = _data[i];
			}
			tmp_data[pos] = val;
			for (size_t i = pos + 1; i < _size; i++)
			{
				tmp_data[i + 1] = _data[i];
			}
			delete[] _data;
			_data = tmp_data;
		}
		else
		{
			for (size_t i = _size; i > pos; i--)
			{
				_data[i] = _data[i - 1];
			}
			_data[pos] = val;
		}
		_size++;
	}

	void erase(size_t pos)
	{
		assert(pos < _size);
		--_size;
		for (size_t i = pos; i < _size; i++)
		{
			_data[i] = _data[i + 1];
		}
	}

	void push_back(const T& val)
	{
		insert(_size, val);
	}

	void pop_back()
	{
		erase(_size - 1);
	}

	size_t find(const T& val)
	{
		for (size_t i = 0; i < _size; i++)
		{
			if (_data[i] == val)
				return i;
		}
		return nopos;
	}

	size_t size()
	{
		return _size;
	}
private:
	T* _data;
	size_t _size;
	size_t _capacity;
	const static size_t nopos = -1;
};

void testVector()
{
	Vector<string> v;
	v.push_back("hello world1");
	v.push_back("hello world2");
	v.push_back("hello world3");
	v.push_back("hello world4");
	v.push_back("hello world5");
	v.push_back("hello world6");
	v.pop_back();
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	cout << v[v.find("hello world3")] << endl;
}