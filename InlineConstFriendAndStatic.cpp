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
		//�����ڵĺ���Ĭ��Ϊ��������������������дinline�Ͳ�дû������
		return;//ʲôҲ��������˵��һ��
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

	d2.showDate();//const���ε����const���εĺ���
	
	setDate(d1);//��Ԫ����
	system("pause");
	return 0;
}