#pragma once
#include "TypeTraits.h"
#include <vector>
#include <exception>
#include <cassert>

namespace jo_qzy
{
	template<class T>
	class Vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}

		

		Vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		template<class input_iterator>
		Vector(input_iterator begin, input_iterator end)
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			assert(begin < end);
			_start = new T[end - begin];
			__my_copy(_start, begin, end - begin);
			_finish = _start + end - begin;
			_endofstorage = _finish;
		}

		Vector(size_t n, const T& val = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				_start[i] = val;
			}
			_finish = _start + n;
			_endofstorage = _start + n;
		}

		~Vector()
		{
			if (_start != nullptr)
			{
				delete[] _start;
			}
			_start = _finish = _endofstorage = nullptr;
		}

		void push_back(const T& val)
		{
			insert(_finish, val);
		}

		void pop_back()
		{
			_finish - 1;
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos <= _finish && pos >= _start);
			if (_finish == _endofstorage)
			{
				size_t _size = size();
				size_t insert_pos = pos - _start;
				size_t _capacity = ((capacity() == 0) ? 1 : capacity() * 2);
				T* tmp = new T[_capacity];
				__my_copy(tmp, _start, _size);
				std::swap(_start, tmp);
				delete[] tmp;
				_finish = _start + _size;
				_endofstorage = _start + _capacity;
				pos = _start + insert_pos;
			}
			__my_move(pos, pos + 1, _finish - pos);
			*pos = val;
			_finish++;
			return pos;
		}
		

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endofstorage - _start;
		}

		void reserve(size_t n)
		{
			size_t size = capacity();
			if (n >= size)
			{
				T* tmp = new T[n];
				//TypeTraits.hÖÐµÄº¯Êý
				__my_copy(tmp, _start, size);
				std::swap(tmp, _start);
				delete[] tmp;
				_finish = _start + size;
				_endofstorage = _start + n;
			}
		}

		void resize(size_t n)
		{

		}
	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;
	};
}

using namespace jo_qzy;

void test()
{
	Vector<int> v;

	v.push_back(1);
	Vector<int>::iterator it = v.begin();
	it++, it++;
	v.insert(it, 2);
}

void test1()
{
	vector<int> v = { 1,2,3,4,5,6 };
	//Vector<int> v = { 1,2,3,4,5,6 };
}