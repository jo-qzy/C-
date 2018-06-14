#include <iostream>
#include <vector>

using namespace std;

//����
void test1()//�˽�����
{
	int a = 10;
	int* p = &a;
	int& b = a;

	cout << "a.value:" << a << endl;
	cout << "b.value:" << b << endl;

	cout << "a.address:" << &a << endl;
	cout << "b.address:" << &b << endl;

	a += 5;

	cout << "a.value:" << a << endl;
	cout << "b.value:" << b << endl;
}

void test2()//const����
{
	int d1 = 10;
	const int& d2 = d1;

	d1 += 5;
	//d2 += 5; �˾�Ƿ���bû��Ȩ���޸�a

	const int d3 = 10;
	//int& d4 = d3; �Ƿ���Ȩ��ֻ����С���ܷŴ�

	const int& d5 = 5;//�Ϸ�����Ϊ����Ҳ�пռ䣬���ǳ��������޸ģ����Ա�����const

	double d6 = 1.5;
	//int& d7 = d6; �Ƿ�������������ʱ���Ͳ�ͬ����Ҫת����d6ת��Ϊ��ʱ���������г����ԣ���������
	const int& d8 = d6;//����ͬd5һ��
}


//����
void swap(int left, int right)//��ͨ����
{
	//��������������ǲ�����ɽ������ݵ������
	//����ֻ�ǰ���ʱ����������
	int temp = left;
	temp = left;
	left = right;
	right = temp;
}

void swap(int& left, int& right)//���ô���
{
	//��Ȼ����һ�����Ǵ����õ����ã��ܹ���������
	int temp = left;
	temp = left;
	left = right;
	right = temp;
}

int getNumber(const vector<int> arr)//�����ã����ǲ����������鰡ͬ־��
{
	return arr.back();
}

void swap(int *left, int *right)//ָ�봫��
{
	int temp = *left;
	temp = *left;
	*left = *right;
	*right = temp;
}


//���÷���ֵ
int& add(int a, int b)//�����ʹ�����÷���ֵ
{
	int sum = a + b;
	return sum;
}

int addNormal(int a, int b)//��ͨ��ֵ���ط�ʽ
{
	int sum = a + b;
	return sum;
}

int& getMaxiumNum(int& a, int& b)//��ȷ�����÷���
{
	//����a��b�еĽϴ�ֵ������a��b�ǲ������ô���ģ����Կ�����Ϊ���÷���ֵ����
	return a > b ? a : b;
}

void test3()
{
	int* p = 0;
	int& a = *p;
	int b = 2;
	//swap(a, b);
}

int main()
{
	test3();
	int x1 = 5, x2 = 10;
	add(x1, x2);
	addNormal(x1, x2);
	return 0;
}