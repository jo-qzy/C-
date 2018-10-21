//题目：不能使用循环、递归、乘法、除法、移位操作，求1~n的和
//1.骚操作1,：借助构造函数和静态成员变量完成，新建多少个对象，就有多少次构造函数调用
class my_add
{
public:
	static int sum, count;
	my_add()
	{
		count++;
		sum += count;
	}
    ~my_add()
    {
        count = sum = 0;
    }
};
int my_add::count = 0;
int my_add::sum = 0;
class Solution {
public:
	int Sum_Solution(int n) {
		my_add* get_add = new my_add[n];
		int sum = my_add::sum;
		delete[] get_add;
		return sum;
	}
};
//2.骚操作2：借助模板偏特化在编译时便完成计算，但是这个数不能太大
//而且这个方法有一些限制，那就是必须在程序运行前给好n，自测能算到650左右
template<int N>
class Add_1toN
{
public:
	enum { Ret = Add_1toN<N - 1>::Ret + N };
};

template<>
class Add_1toN<1>
{
public:
	enum { Ret = 1 };
};

int main()
{
	int ret = Add_1toN<100>;
	return 0;
}