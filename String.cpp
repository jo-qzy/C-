#include <iostream>

using namespace std;

class String
{
public:
	String(const char* str = "")
	{
		int size = strlen(str);
		_str = new char[size + 1];
		_capacity = size + 1;
		_size = size;
		char* cur = _str;
		while (*cur++ = *str++);
	}

	String(const String& s)
		:_str(NULL)
	{
		String temp(s._str);
		swap(_str, temp._str);
		_size = temp._size;
		_capacity = temp._capacity;
	}

	~String()
	{
		delete[] _str;
	}

	String operator+(const String& s)
	{
		String temp = *this;
		temp.append(s._str);
		return temp;
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			String temp = s;
			swap(_str, temp._str);
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

	String& operator+=(const char* str)
	{
		insert(_size, str);
		return *this;
	}

	char operator[](const size_t pos)const
	{
		if (pos > _size)
		{
			return '\0';
		}
		return *(_str + pos);
	}

	String& insert(const size_t pos, const char* str)
	{
		if (pos <= _size)
		{
			int len = strlen(str);
			if (_size + len >= _capacity)
			{
				expand(_size + len);
			}
			const char* end = _str + _size;
			int i = 0;
			for (i = _size + len; i >= (int)pos + len; i--)
			{
				*(_str + i) = *end--;
			}
			end = str + len - 1;
			for (; i >= (int)pos; i--)
			{
				*(_str + i) = *end--;
			}
			_size = _size + len;
		}
		return *this;
	}

	String& insert(const size_t pos, const char ch)
	{
		char* str = new char[2];
		*(str + 0) = ch;
		*(str + 1) = '\0';
		insert(pos, str);
		delete[] str;
		return *this;
	}

	String& erase(const size_t pos, const size_t count = 1)
	{
		if (pos <= _size)
		{
			if (pos + count >= _size)
			{
				*(_str + pos) = '\0';
				_size = pos;
			}
			else
			{
				char* front = _str + pos;
				char* back = _str + pos + count;
				while (*front++ = *back++);
				_size -= count;
			}
		}
		return *this;
	}

	void clear()
	{
		*(_str + 0) = '\0';
		_size = 0;
	}

	String& push_back(const char ch)
	{
		return insert(_size, ch);
	}

	String& pop_back()
	{
		return erase(_size - 1);
	}

	String& append(const char* str)
	{
		return insert(_size, str);
	}

	size_t size()const
	{
		return _size;
	}

	friend ostream& operator<<(ostream& out, String& s);
private:
	void expand(size_t size)
	{
		char* temp = new char[size + 1];
		char* temp_cur = temp;
		char* _str_cur = _str;
		while (*temp_cur++ = *_str_cur++);
		swap(_str, temp);
		_capacity = size + 1;
	}

private:
	char* _str;
	int _size;
	int _capacity;
};

ostream& operator<<(ostream& out, String& s)
{
	out << s._str << endl;
	return out;
}

int main()
{
	String s1;
	String s2 = "hello ";
	string g,h;
	
	//insert测试
	s1.insert(0, 'h');
	s1.insert(1, "ello");
	cout << s1;//输出友元函数测试

	//+=测试
	s1 += " world";
	cout << s1;

	//删除
	s1.erase(0, 6);
	cout << s1;
	
	//pop_back和push_back测试
	s1.pop_back();
	s1.push_back('d');
	cout << s1;

	//基本运算符操作重载
	s2 = s2 + s1;
	cout << s2;

	system("pause");
	return 0;
}