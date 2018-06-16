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
		count++;//ͳ�ƹ��캯�����ô���
	}

	void showDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	void showDate()const
	{
		//const���κ���������const�������룬���Զ���thisָ���Ϊconst
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	inline void testDate()
	{
		//�����ڵĺ���Ĭ��Ϊ��������������������дinline�Ͳ�дû������
		return;//ʲôҲ��������˵��һ��
	}
	
	ostream& operator<<(ostream& out)
	{
		//����<<��������ʵ����̫����ˣ���������Ԫ��
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
	//��Ԫ�������������
	out << d._year << "-" << d._month << "-" << d._day << endl;
	return out;
}

int Date::count = 0;

int main()
{
	Date d1;
	const Date d2;

	d2.showDate();//const���ε����const���εĺ���
	
	setDate(d1);//��Ԫ����
	
	d1 << cout;//�������أ��������ֵֹ�
	cout << d1;//��Ԫ��������<<����������
	
	Date::printCount();//���һ�¾�̬����������ľ�̬����ͳ�Ƶ��ǹ��캯�����õĴ���
	
	system("pause");
	return 0;
}