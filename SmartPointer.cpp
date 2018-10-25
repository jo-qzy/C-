#pragma once

template <class T>
class ScopedPtr
{
public:
	ScopedPtr(T* ptr = new T)
		:_ptr(ptr)
	{}

	~ScopedPtr()
	{
		delete _ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
	ScopedPtr(ScopedPtr<T>& sp) = delete;
	ScopedPtr<T>& operator=(ScopedPtr<T>& sp) = delete;
	ScopedPtr<T>& operator=(T* ptr) = delete;
protected:
	T* _ptr;
};

void testScopePtr()
{
	ScopedPtr<string> sp;
	//ScopedPtr<string> sp1(sp);//错误，拷贝构造为私有无法调用
	//sp1 = sp;//错误，=运算符重载后为私有，无法调用
	*sp = "hello world";
	cout << *sp << endl;
	sp->at(0) = 'H';//调用string类的at
	cout << *sp << endl;
}

template <class T>
class SharedPtr
{
	template <class>
	friend class WeakPtr;
public:
	SharedPtr(T* ptr = NULL)
		:_ptr(ptr)
		,_count(new size_t(1))
	{}

	SharedPtr(SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		, _count(sp._count)
	{
		(*_count)++;
	}

	~SharedPtr()
	{
		if (--(*_count) == 0)
		{
			delete _ptr;
			delete _count;
		}
	}

	SharedPtr<T>& operator=(SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			if (--(*_count) == 0)
			{
				delete _ptr;
				delete _count;
			}

			_ptr = sp._ptr;
			++(*sp._count);
			_count = sp._count;
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
	size_t *_count;
};

void testSharedPtr()
{
	SharedPtr<string> sp = new string;
	SharedPtr<string> sp1;//可以使用
	sp1 = sp;//可以使用
	*sp = "hello world";
	cout << *sp << endl;
	sp->at(0) = 'H';//调用string类的at
	cout << *sp1 << endl;
}

struct List
{
	SharedPtr<List> _next;
	SharedPtr<List> _prev;
	List()
		:_next(NULL)
		, _prev(NULL)
	{}
	~List()
	{
		cout << "~List()" << endl;
	}
};

void testSharedPtrCircularReference()
{
	//这里会无限析构，导致程序崩溃
	//循环引用问题
	SharedPtr<List> p1 = new List();
	SharedPtr<List> p2 = new List();
	p1->_next = p2;
	p2->_prev = p1;
}

template <class T>
class WeakPtr
{
public:
	WeakPtr()
		:_ptr(NULL)
	{}

	WeakPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
	{}

	WeakPtr(WeakPtr<T>& wp)
		:_ptr(wp._ptr)
	{}

	WeakPtr<T>& operator=(SharedPtr<T>& sp)
	{
		_ptr = sp._ptr;
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
protected:
	T* _ptr;
};

struct ListNode
{
	WeakPtr<ListNode> _next;
	WeakPtr<ListNode> _prev;

	~ListNode()
	{
		cout << "~ListNode()" << endl;
	}
};

// 循环引用
void TestCycle()
{
	SharedPtr<ListNode> n1 = new ListNode;
	SharedPtr<ListNode> n2 = new ListNode;

	n1->_next = n2;
	n2->_prev = n1;
}