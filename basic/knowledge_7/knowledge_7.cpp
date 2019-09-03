// knowledge_7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 可调用对象

#include "pch.h"
#include <iostream>

void myfunc(int tv)
{
	std::cout << "myfunc(int tv)函数执行了" << std::endl;
}

class TC
{
public:
	void operator()(int tv)
	{
		std::cout << "operator()(int tv)函数执行了, tv=" << tv << std::endl;
	}

	void ptfunc(int tv)
	{
		std::cout << "ptfunc(int tv)函数执行了, tv=" << tv << std::endl;
	}

};

class TC2
{
public:
	using tfpoint = void(*)(int); //定义一个函数指针类型
	static void mysfunc(int tv) //静态成员函数
	{
		std::cout << "mysfunc(int tv)静态成员函数执行了, tv=" << tv << std::endl;
	}
	operator tfpoint() { return mysfunc; }
};

int main()
{
	//一 可调用对象
	//1 函数 2 重载了()运算符的类的对象
	//1.1 函数指针
	void(*pmf)(int) = &myfunc; //定义一个函数指针pmf并给了初值
	pmf(15); //调用函数，这就是个可调用对象

	//1.2 具有operator()成员函数的类的对象(仿函数)
	// 仿函数的定义：仿函数（functor）,它的行为类似于函数的东西（something that performs a function）
	// c++仿函数是通过在类中重载()运算符实现。又称函数对象(function object):能行使函数功能的类
	TC tc;
	tc(15); //调用的是()操作符，这也是个可调用对象，等价于tc.operator()(20)

	//1.3 可被转换为函数指针的类对象（仿函数/函数对象）
	TC2 tc2;
	tc2(50); //先调用tfpoint, 再调用mysfunc:这也是个可调用对象。等价于tc2.operator TC2::tfpoint()(50);
	
	//1.4 类成员函数指针
	TC tc;
	void (TC::*myfpointpt)(int) = &TC::ptfunc; //类成员函数指针变量myfpointpt定义并给初值
	(tc.*myfpointpt)(68);

	//1.5 总结
	//（a）看成对象
	//（b）我们可以对其使用()调用运算符，如果a是可调用对象，那么我们就可以编写a(param...)代码
	//
    std::cout << "Hello World!\n"; 
}
