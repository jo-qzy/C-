#include <iostream>

using namespace std;

class Date
{
public:
	Date(int year = 1970, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}

	void showDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	void showDate()const
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	inline void testDate()
	{
		//在类内的函数默认为内联函数，所以在这里写inline和不写没有区别
		return;//什么也不做就是说明一下
	}

	friend void setDate(Date& d);
private:
	int _year;
	int _month;
	int _day;
};

void setDate(Date& d)
{
	d._year = 2000;
}

int main()
{
	Date d1;
	const Date d2;

	d2.showDate();//const修饰的类调const修饰的函数
	
	setDate(d1);//友元函数
	system("pause");
	return 0;
}