#include <iostream>

using namespace std;

class Date
{
public:
	Date(int year = 1970, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{
		count++;//统计构造函数调用次数
	}

	void showDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	void showDate()const
	{
		//const修饰函数，当有const变量传入，会自动将this指针变为const
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	inline void testDate()
	{
		//在类内的函数默认为内联函数，所以在这里写inline和不写没有区别
		return;//什么也不做就是说明一下
	}
	
	ostream& operator<<(ostream& out)
	{
		//重载<<，这个输出实在是太奇怪了，还是用友元吧
		out << _year << "-" << _month << "-" << _day << endl;
		return out;
	}

	friend void setDate(Date& d);
	friend ostream& operator<<(ostream& out, Date& d);

	static void printCount()
	{
		cout << count << endl;
	}
private:
	int _year;
	int _month;
	int _day;
	
	static int count;
};

void setDate(Date& d)
{
	d._year = 2000;
}

ostream& operator<<(ostream& out, Date& d)
{
	//友元函数的输出重载
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}

int Date::count = 0;

int main()
{
	Date d1;
	const Date d2;

	d2.showDate();//const修饰的类调const修饰的函数
	
	setDate(d1);//友元函数
	
	d1 << cout;//类内重载，用起来怪怪的
	cout << d1;//友元函数重载<<，正常多了
	
	Date::printCount();//输出一下静态变量，这里的静态变量统计的是构造函数调用的次数
	
	system("pause");
	return 0;
}