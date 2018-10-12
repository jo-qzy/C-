#pragma once
#include <iostream>
#include "VectorTemplate.h"
//要使用本头文件需要配合本仓库内另一个文件"VectorTemplate.h"使用，请先下载
//下载地址：https://github.com/jo-qzy/CPlusPlus/blob/master/VectorTemplate.h

template <class T, class container = Vector<T>>

class Stack
{
public:
	void push(const T& val)
	{
		_con.push_back(val);
	}

	void pop()
	{
		_con.pop_back();
	}

	const T& top()
	{
		return _con.back();
	}

	size_t size()
	{
		return _con.size();
	}

	bool empty()
	{
		return _con.empty();
	}
private:
	container _con;
};

void testStack()
{
	Stack<string> s;
	s.push("hello world1");
	s.push("hello world2");
	s.push("hello world3");
	s.push("hello world4");
	s.push("hello world5");
	s.push("hello world6");
	s.pop();
	cout << s.top() << endl;
	cout << s.empty() << endl;
}