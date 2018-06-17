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
		char* cur = _str;
		while (*cur++ = *str);
	}

	String(const String& s)
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

private:
	char* _str;
	int _size;
	int _capacity;
};

int main()
{
	String s;
	return 0;
}