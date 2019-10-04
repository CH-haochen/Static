// knowledge_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 函数调用运算符、function类模板

#include "pch.h"
#include <iostream>
#include <map>
#include <string>
#include <functional>

void func(int i)
{
	return;
}

class A
{
public:

	/*A(int i)
	{
	
	}*/

	int operator()(int value) const
	{
		if (value < 0) return 0;
		return value;
	}

};

//普通函数
int echovalue(int value) 
{
	std::cout << value << std::endl;
	return value;
}

int echovalue()
{
	return 1;
}


int main()
{

	func(5);
	//圆括号()就是函数调用的明显标记，()有一个称呼叫做“函数调用运算符”
	//如果在类中重载了函数调用运算符(),那么就可以像使用函数一样使用该类的对象了。对象(实参)
	//如何使用函数调用运算符呢？
	//（a）定义一个该类对象
	//（b）像函数调用一样使用该对象，也就是()中增加实参列表

	int i = 200;
	A myA; //含有函数调用运算符的对象, 这个是对象定义的初始化，所以调用的是构造函数
	int result = myA(i); //这个调用的是重载的()圆括号
	//int result = myA.operator()(i);

	//结论：只要这个对象所属的类重载了()“函数调用运算符”，那么这个类对象就变成了可调用的了，而且可以调用多个版本的()
	// 这个类重载了(),那么该类的对象多了个新名字 “函数对象”

	//二 不同调用对象的相同调用形式
	//函数echovalue和类A的重载的()，这两个东西，调用参数和返回值相同，就叫做“调用形式相同”

	std::map<std::string, int(*)(int)> myoper; //<string, 函数指针>
	myoper.insert({ "ev", echovalue });
	
	//三 标准库function类型介绍
	//function 类模板： 要提供的模板参数来表示该function类型能够表示的“对象的调用形式”

	std::function<int(int)> f1 = echovalue; //函数
	std::function<int(int)> f2 = myA; //类对象，因为类中有()重载
	std::function<int(int)> f2 = A();
	//调用一下
	f1(5);
	std::cout << f2(3) << std::endl;

	//改造一下map

	std::map<std::string, std::function<int(int)>> myoper = {
		{"ev", echovalue},
		{"bt", myA}
	};

	std::function<int(int)> f1 = echovalue; //如果echovalue有重载，就无法放到function<>类型的对象中
	//我们可以通过定义函数指针来解决
	int(*fp)(int) = echovalue; //定义函数指针，不会产生二义性，因为函数指针里有对应的参数类型和返回值类型
	std::function<int(int)> f1 = fp; //直接塞进去函数指针而不是函数名echovalue

    std::cout << "Hello World!\n"; 
}
