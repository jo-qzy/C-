#include <memory>

struct TestClass
{
public:
	TestClass()
	{
		cout << "TestClass()" << endl;
	}
	~TestClass()
	{
		cout << "~TestClass()" << endl;
	}
private:
	int num;
};

template <class T>
class DeleteArray
{
	void operator()(T* ptr)
	{
		cout << "DeleteArray delete array" << endl;
		delete[] ptr;
	}
};

template <class T>
class DeleteFILE
{
	void operator()(T* ptr)
	{
		cout << "DeleteArray delete array" << endl;
		fclose(ptr);
	}
};

void test()
{

	unique_ptr<TestClass> up(new TestClass);
	unique_ptr<TestClass[]> up_group(new TestClass[10]);

	//shared智能指针管理数组，自定义删除模式
	shared_ptr<TestClass> sp_group(new TestClass[10], DeleteArray<TestClass>());
	shared_ptr<FILE> file(fopen("text.txt", "w"), DeleteFILE<FILE>());

	shared_ptr<TestClass> sp1(new TestClass);
	shared_ptr<TestClass> sp2(sp1);
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
	cout << sp1.get() << endl;
	cout << sp2.get() << endl;
}