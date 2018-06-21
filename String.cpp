#include <iostream>

using namespace std;

class String
{
public:
	//Member Function

	//构造函数(constructor)
	String(const char* str = "")
	{
		int size = strlen(str);
		_str = new char[size + 1];
		_capacity = size + 1;
		_size = size;
		char* cur = _str;
		while (*cur++ = *str++);//strlen拷贝一下
	}

	String(const String& s)
		:_str(NULL)
	{
		//拷贝构造利用构造函数进行拷贝
		String temp(s._str);
		//交换临时和this的值，当出了作用域temp自动释放
		std::swap(_str, temp._str);
		_size = temp._size;
		_capacity = temp._capacity;
	}

	//析构函数(destructor)
	~String()
	{
		//析构唯一要做的事情就是delete不能忘
		delete[] _str;
	}

	//operator=: String assignment
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			//剑指offer第一题
			String temp = s;
			std::swap(_str, temp._str);
			_size = temp._size;
			_capacity = temp._capacity;
		}
		return *this;
	}

	String& operator=(const char ch)
	{
		clear();
		insert(0, ch);
		return *this;
	}

	String& operator=(const char* str)
	{
		clear();
		insert(0, str);
		return *this;
	}

	//Capacity相关函数

	//size: Return length of string
	size_t size() const
	{
		return _size;
	}

	//length: Return length of string
	size_t length() const
	{
		return _size;
	}

	//resize: Resize string
	void resize(size_t size, char c)
	{
		//直接将字符串长度的最后一位置为'\0'就好了
		if (size >= _size)
		{
			//长度不能超过字符串
			size = _size;
		}
		*(_str + size) = '\0';
		char* cur = _str;
		while (*cur)
		{
			*cur++ = c;
		}
	}

	void resize(const size_t size)
	{
		if (size < _size)
		{
			*(_str + size) = '\0';
		}
	}

	//capacity: Return size of allocated storage
	size_t capacity()
	{
		return _capacity;
	}

	//reserve: Request a change in capacity
	void reserve(const size_t size)
	{
		expand(size);
	}

	//clear: Clear string
	void clear()
	{
		*(_str + 0) = '\0';
		_size = 0;
	}

	//empty: Test if string is empty
	bool empty() const
	{
		if (_size == 0)
		{
			return true;
		}
		return false;
	}

	//Element access

	//operator[]: Get character of string
	char& operator[](const size_t pos) const
	{
		if (pos >= _size)
		{
			return *(_str + _size);
		}
		return *(_str + pos);
	}

	//at: Get character in string
	char& at(const size_t pos) const
	{
		return (*this)[pos];
	}

	//Modifiers

	//operator+=: Append to string
	String& operator+=(const char* str)
	{
		return insert(_size, str);
	}

	String& operator+=(const String& s)
	{
		return insert(_size, s._str);
	}

	String& operator+=(const char ch)
	{
		return insert(_size, ch);
	}

	//append: Append to string
	String& append(const char* str)
	{
		return insert(_size, str);
	}

	String& append(const char ch)
	{
		return insert(_size, ch);
	}

	String& append(const String& s)
	{
		return insert(_size, s._str);
	}

	//push_back: Append character to string
	String& push_back(const char ch)
	{
		return insert(_size, ch);
	}

	//insert: Insert into string
	String& insert(const size_t pos, const char* str)
	{
		if (pos <= _size)
		{
			int len = strlen(str);
			//检查空间是否足够
			if (_size + len >= _capacity)
			{
				expand(_size + len);
			}
			const char* end = _str + _size;
			int i = 0;
			for (i = _size + len; i >= (int)pos + len; i--)
			{
				//拷贝目标串
				*(_str + i) = *end--;
			}
			end = str + len - 1;
			for (; i >= (int)pos; i--)
			{
				//拷贝后半部分串
				*(_str + i) = *end--;
			}
			_size = _size + len;
		}
		return *this;
	}

	String& insert(const size_t pos, const char ch)
	{
		//把一个字符变成一个字符的字符串，然后调用插入
		char* str = new char[2];
		*(str + 0) = ch;
		*(str + 1) = '\0';
		insert(pos, str);
		delete[] str;
		return *this;
	}

	String& insert(const String& s)
	{
		//继续赋用
		return insert(_size, s._str);
	}

	//erase: Erase characters from string
	String& erase(const size_t pos, const size_t count = 1)
	{
		if (pos <= _size)
		{
			//抹去长度超过字符串长度，直接移动尾
			if (pos + count >= _size)
			{
				*(_str + pos) = '\0';
				_size = pos;
			}
			else
			{
				//直接拷贝后半部分没有删除的字符串
				char* front = _str + pos;
				char* back = _str + pos + count;
				while (*front++ = *back++);
				_size -= count;
			}
		}
		return *this;
	}

	//replace: Replace portion of string
	String& replace(const size_t pos, size_t len, const char* str)
	{
		//检查空间
		if (pos + len >= _capacity)
		{
			expand(pos + len);
		}
		for (int i = 0; i < len; i++)
		{
			*(_str + pos + i) = *(str + i);
		}
		if (pos + len > _size)
		{
			//长度超过原串，尾部加'\0'
			_size = pos + len;
			*(_str + _size) = '\0';
		}
		return *this;
	}

	String& replace(const size_t pos, size_t len, const String& s)
	{
		return replace(pos, len, s._str);
	}

	//swap: Swap string values
	void swap(String& s)
	{
		//交换两个类
		std::swap(_str, s._str);
		std::swap(_size, s._size);
		std::swap(_capacity, s._capacity);
	}

	//pop_back: Delete last character
	String& pop_back()
	{
		return erase(_size - 1);
	}

	//String operations

	//c_str: Get C string equivalent
	char* c_str()
	{
		return _str;
	}

	//find: Find content in string
	size_t find(const char* s, size_t pos = 0) const
	{
		//查找子串，和strstr类似
		const char* start = NULL;
		const char* cur = _str;
		const char* s_cur = s;
		while (*cur)
		{
			start = cur;
			if (*cur == *s)
			{
				s_cur = s;
				while (*cur == *s_cur && *cur)
				{
					cur++, s_cur++;
				}
				if (*s_cur == '\0')
				{
					return start - _str;
				}
			}
			cur = ++start;
		}
		return npos;
	}

	size_t find(char c, size_t pos = 0) const
	{
		//找第一个出现的字母
		const char* cur = _str;
		while (*cur)
		{
			if (*cur == c)
			{
				return cur - _str;
			}
			cur++;
		}
		return std::string::npos;
	}

	//substr: Generate substring
	String substr(size_t pos = 0, size_t len = npos) const
	{
		//截断字符串
		int length = len;
		if (len = npos)
		{
			length = _size - pos;
		}
		char *str = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			*(str + i) = *(_str + pos + i);
		}
		*(str + length) = '\0';
		String temp = str;
		delete[] str;
		return temp;
	}

	String operator+(const String& s)
	{
		String temp = *this;
		temp.append(s._str);
		return temp;
	}

	friend ostream& operator<<(ostream& out, String& s);
private:
	void expand(size_t size)
	{
		//扩大空间
		char* temp = new char[size + 1];
		char* temp_cur = temp;
		char* _str_cur = _str;
		while (*temp_cur++ = *_str_cur++);
		std::swap(_str, temp);
		_capacity = size + 1;
	}

private:
	char* _str;
	int _size;
	int _capacity;

	static size_t npos;
};

size_t String::npos = -1;

ostream& operator<<(ostream& out, String& s)
{
	out << s._str;
	return out;
}


//Member function就不测了，每个函数都要用

//测试空间函数相关
void testCapacity()
{
	String s1 = "hello world";
	cout << "size->" << s1.size() << "  expect->11" << endl;
	cout << "length->" << s1.length() << "  expect->11" << endl;
	s1.resize(5);//预期结果->hello
	cout << "resize->" << s1 << "  expect->hello" << endl;
	cout << "capacity->" << s1.capacity() << "  expect->12" << endl;
	s1.reserve(1000);
	cout << "reserve->" << s1.capacity() << "  expect->1000 + 1" << endl;
	s1.clear();
	cout << "clear->" << s1 << "  expect->" << endl;
	cout << "clear->" << s1.size() << "  expect->0" << endl;
	cout << "empty->" << s1.empty() << "  expect->1" << endl;
}

void testElementAccess()
{
	//预期输出->hello world
	String s1 = "hello world";
	cout << "s1->" << s1 << endl;
	cout << "operator[]:s1[0]->" << s1[0] << "  expect->h" << endl;
	cout << "s1.at(0)->" << s1.at(0) << "  expect->h" << endl;
}

void testModifiers()
{
	String s1 = "hello ";
	String s2 = "world";
	
	//operator+=
	s1 += s2;
	cout << "s1 += s2->" << s1 << "  expect->hello world" << endl;
	
	//apend
	s1.clear();
	s1.append("hello ");
	s1.append(s2);
	cout << "append->" << s1 << "  expect->hello world" << endl;

	//pop_back and push_back
	s1.pop_back();
	s1.push_back('d');
	cout << "pop_back and push_back->" << s1 << "  expect->hello world" << endl;

	//insert
	s1 = s2;
	s1.insert(0, "hello ");
	cout << "insert->" << s1 << "  expect->hello world" << endl;

	//erase
	s1.erase(0, 11);
	cout << "erase->" << s1 << "  expect->" << endl;

	//replace
	s1 = "hello";
	s1.replace(0, 8, "my world");
	cout << "replace->" << s1 << "  expect->my world" << endl;

	//swap
	s1.swap(s2);
	cout << "swap->" << s1 << "  expect->world" << endl;
}

void testStringOperations()
{
	String s1 = "hello world";

	//c_str
	char* temp = s1.c_str();
	cout << "c_str->" << temp << "  expect->hello world" << endl;

	//find
	cout << "find->" << s1.find("ello") << "  expect->1" << endl;

	//substr
	String s2 = s1.substr(6, 5);
	cout << "substr->" << s2 << "  expect->world" << endl;
}

int main()
{
	testStringOperations();
	system("pause");
	return 0;
}