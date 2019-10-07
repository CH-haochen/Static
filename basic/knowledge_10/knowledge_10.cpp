// knowledge_10.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 可变参数函数、initializer_list、省略号形参

#include "pch.h"
#include <iostream>
#include "stdarg.h"



void printvalue(std::initializer_list<std::string> tmpstr)
{
	for (auto beg = tmpstr.begin(); beg != tmpstr.end(); ++beg)
	{
		std::cout << (*beg).c_str() << std::endl;
	}

	//范围for语句
	for (auto &tmpitem : tmpstr)
	{
		std::cout << tmpitem.c_str() << std::endl;
	}
	std::cout << tmpstr.size() << std::endl;
}

class CT
{
public:
	CT(const std::initializer_list<int> &tmpvalue)
	{

	}
};

double sum(int num, ...) //num传递进来的可变参数的数量
{
	va_list valist; //创建一个va_list的变量
	
	double sum = 0;
	va_start(valist, num); //使valist指向起始的参数
	for (int i = 0; i < num; i++)
	{
		//遍历参数
		sum = sum + va_arg(valist, int); //参数2说明返回的类型为int
	}
	va_end(valist); //释放va_list
	return sum;
}


void functest(const char *msg, ...)
{
	va_list valist;
	int csgs = std::atoi(msg); //拿到可变参数数量
	va_start(valist, msg);
	int paramcout = 0;
	while (paramcout < csgs)
	{
		char *p;
		p = va_arg(valist, char*);
		printf("第%d个参数是:%s\n", paramcout, p);
		paramcout++;
	}
	va_end(valist);
}


int main()
{
	//一 可变参数函数
	//这种能够接收非固定个数参数的函数就是可变参数函数
	//initializer_list标准库类型，该类型能够使用的前提条件是 所有的实参类型相同

	//二  initializer_list(初始化列表)
	//如果一个函数，它的实参数量不可预知，但是所有的参数的类型相同，我们就可以使用这个initializer_list类型的形参来接收
	//initializer_list 也是一个类模板
	//我们把initializer_list理解成某种类型值的数组。这个类模板里指定的类型模板参数就是这个数组里保存的数据的类型
	std::initializer_list<int> myarray; //数组，元素类型是list，空列表(空数组)

	std::initializer_list<int> myarray2 = {12, 14, 16, 18, 20};

	//注意initializer_list中的元素，永远是常量值，不能被改变
	
	//2.1 begin()、end()遍历、size()获取元素个数
	printvalue({"aa", "bb", "cc"}); //若要往initializer_list形参传递值的一个序列，则必须要把这个序列放到{}里括起来作为一个整体

	//2.2 拷贝和赋值
	//拷贝、赋值一个initializer_list对象，不会拷贝列表中的元素。原来对象和拷贝或者赋值出来的对象共享列表中的元素
	std::initializer_list<std::string> myarray3 = { "aa", "bb", "cc" };
	std::initializer_list<std::string> myarray4(myarray3);

	//2.3 初始化列表做构造函数参数
	CT ct1 = { 10,29,30 };

	//三 省略号形参（...）：可变参数函数
	//省略号形参一般无法正确处理类类型对象，能正确处理int，char*
	
	//这种省略形参式的可变参数函数，虽然参数数量不固定，但是函数的所有参数是存储在线性连续的栈空间中
	//而且带...的可变参函数必须至少要有一个普通参数，外贸就可以通过这个普通参数来寻址后续的所有可变参数的类型以及值
	//#include "stdarg.h"

	std::cout << sum(3, 100, 200, 300) << std::endl;
	
	functest("3", "aa", "bb", "cc");

	//注意：
	//（a）至少有一个有效形参，形参不能是完全的...
	//（b）...形参只能出现在参数列表的最后一个位置
	//（c）...之前的逗号,可以省略
	//（d）如果有多个普通参数，那么va_stat(varlist,msg),第二个参数必须绑...之前的那个参数
	//（e）不建议在c++中使用...

    std::cout << "Hello World!\n"; 
}

