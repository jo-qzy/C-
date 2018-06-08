#include <iostream>
#include <vector>

using namespace std;

//引用
void test1()//了解引用
{
	int a = 10;
	int& b = a;

	cout << "a.value:" << a << endl;
	cout << "b.value:" << b << endl;

	cout << "a.address:" << &a << endl;
	cout << "b.address:" << &b << endl;

	a += 5;

	cout << "a.value:" << a << endl;
	cout << "b.value:" << b << endl;
}

void test2()//const引用
{
	int d1 = 10;
	const int& d2 = d1;

	d1 += 5;
	//d2 += 5; 此句非法，b没有权限修改a

	const int d3 = 10;
	//int& d4 = d3; 非法，权限只能缩小不能放大

	const int& d5 = 5;//合法，因为常量也有空间，但是常量不能修改，所以必须有const

	double d6 = 1.5;
	//int& d7 = d6; 非法，由于在引用时类型不同，需要转换，d6转换为临时变量，具有常属性，不能引用
	const int& d8 = d6;//理由同d5一致
}


//传参
void swap(int left, int right)//普通传参
{
	//这个函数很明显是不能完成交换数据的任务的
	//交换只是把临时变量给换了
	int temp = left;
	temp = left;
	left = right;
	right = temp;
}

void swap(int& left, int& right)//引用传参
{
	//虽然代码一样但是传参用的引用，能够交换两数
	int temp = left;
	temp = left;
	left = right;
	right = temp;
}

int getNumber(const vector<int> arr)//常引用，但是不能引用数组啊同志们
{
	return arr.back();
}

void swap(int *left, int *right)//指针传参
{
	int temp = *left;
	temp = *left;
	*left = *right;
	*right = temp;
}

int& Add(int a, int b)//引用返回值
{
	int ret = a + b;
	return ret;
}

int main()
{
	int x1 = 5, x2 = 10;
	test1();
	return 0;
}