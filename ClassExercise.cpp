//说明：这个部分代码是为了熟悉c++中各类函数而写的，通过日期类的练习来熟悉

#pragma warning(disable:4996)

#include <iostream>
#include <assert.h>
#include <vector>

using namespace std;

class Date {
public:
    //构造函数
    Date(int year = 1970, int month = 1, int day = 1)
    {
        if (invalidDate(year, month, day) == true)
        {
            _year = year;
            _month = month;
            _day = day;
        }
        else
        {
            cout << "error" << endl;
        }
    }

    //拷贝构造
    Date(const Date & d)
    {
        _year = d._year;
        _month = d._month;
        _day = d._day;
    }

    void setDate(int year, int month, int day)
    {
        if (invalidDate(year, month, day) == true)
        {
            _year = year;
            _month = month;
            _day = day;
        }
        else
        {
            cout << "日期非法，重新输入" << endl;
        }
    }

    void show() {
        cout << _year << "-" << _month << "-" << _day << endl;
    }

    int getMonthDay(int year, int month)
    {
        assert(month > 0 && month < 13);
        static vector<int> monthday = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int day = monthday[month];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
        {
            day++;
        }
        return day;
    }

    bool invalidDate(int year, int month, int day)
    {
        if (year > 0 && month > 0 && month < 13 && day <= getMonthDay(year, month) && day > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool operator==(const Date& d)
    {
        return _year == d._year && _month == d._month && _day == d._day;
    }

    bool operator!=(const Date& d)
    {
        return !(*this == d);
    }

    bool operator>(const Date& d)
    {
        if (_year != d._year)
        {
            return _year > d._year;
        }
        if (_month != d._month)
        {
            return _month > d._month;
        }
        return _day > d._day;
    }

    bool operator<(const Date& d)
    {
        //赋用一下大于和等于
        return !(*this > d) && !(*this == d);
    }

    bool operator>=(const Date& d)
    {
        return !(*this < d);
    }

    bool operator<=(const Date& d)
    {
        return !(*this > d);
    }

    Date& operator=(const Date& d)
    {
        if (this != &d)
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        return *this;
    }

    Date operator+(const int day)
    {
		//获取每个月的天数进行加
        if (day < 0)
        {
            return *this - (-day);
        }
        Date ret = *this;
        ret._day += day;
        while (ret._day > getMonthDay(ret._year, ret._month))
        {
            ret._day -= getMonthDay(ret._year, ret._month);
            if (++ret._month == 13)
            {
                ret._month = 1;
                ret._year++;
            }
        }
        return ret;
    }

    Date operator-(const int day)
    {
		//获取每个月前一个月的天数进行减
        if (day < 0)
        {
            return *this + (-day);
        }
        Date ret = *this;
        ret._day -= day;
        while (ret._day <= 0)
        {
            if (--ret._month == 0)
            {
                ret._month = 12;
                ret._year--;
            }
            ret._day -= getMonthDay(ret._year, ret._month);
        }
        return ret;
    }

    int operator-(const Date& d)
    {
		//计算日期与日期的差，用小的加加直到天数相同
        int flag = 1;
        Date smaller = d;
        Date bigger = *this;
        int count = 0;
        if (*this < d)
        {
            smaller = *this;
            bigger = d;
            flag = -1;
        }
        while (smaller != bigger)
        {
            ++smaller;
            count++;
        }
        return count;
    }

    void operator+=(const int day)
    {
        *this = *this + day;
    }

    void operator-=(const int day)
    {
        *this = *this - day;
    }

    Date operator++()
    {
        Date ret = *this;
        *this += 1;
        return ret;
    }

    Date& operator++(int)
    {
        *this += 1;
        return *this;
    }

    Date operator--()
    {
        Date ret = *this;
        *this -= 1;
        return ret;
    }

    Date& operator--(int)
    {
        *this -= 1;
        return *this;
    }

private:
    int _year;
    int _month;
    int _day;
};

class Array {
public:
    Array()
    {
        a = (int *)malloc(sizeof(int) * 10);
    }

    ~Array()
    {
        if (a != NULL)
        {
            free(a);
            a = NULL;
        }
    }
private:
    int * a;
};

void printUI()
{
    cout << "1.日期相差天数" << endl;
    cout << "2.日期加天数(负值为减天数)" << endl;
    cout << "0.退出" << endl;
}

int main()
{
    Date d1;
    Date d2;
    cout << "日期" << endl;
    int year = 0, month = 0, day = 0;
    int choice = 0;
    cout << "日期计算器" << endl;
    while (1)
    {
        cin >> choice;
        if (choice == 0)
        {
            break;
        }
        switch(choice)
        {
        case 1:
            cout << "输入第一个日期(格式:xxxx-xx-xx)" << endl;
            scanf("%d-%d-%d", &year, &month, &day);
            d1.setDate(year, month, day);
            cout << "输入第二个日期(格式:xxxx-xx-xx)" << endl;
            scanf("%d-%d-%d", &year, &month, &day);
            d2.setDate(year, month, day);
            cout << "相差天数为:" << d1 - d2 << endl;
            break;
        case 2:
            cout << "输入日期(格式:xxxx-xx-xx)" << endl;
            scanf("%d-%d-%d", &year, &month, &day);
            d1.setDate(year, month, day);
            cout << "输入需要加的天数((负值为减天数)" << endl;
            cin >> day;
            d1 += day;
            cout << "加上" << day << "后的日期为:";
            d1.show();
            break;
        default:
            cout << "无此选项" << endl;
            break;
        }

    }
    return 0;
}