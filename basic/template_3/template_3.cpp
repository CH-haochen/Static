﻿// template_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 用typename场合、默认模板参数、趣味写法分析


#include <iostream>
#include "myvector.h"
#include "myarray.h"

template<typename T>
typename T::size_type getlength(const T &c)
{
	if (c.empty())
		return 0;
	return c.size();
}

//函数指针要想当做 函数的参数就需要
typedef int(*FunType)(int, int); //定一个函数指针类型

int mf(int a, int b)
{
	//...一些代码
	return 1;
}

void testfunc(int i, int j, FunType funcpoint)//funcpoint就是函数指针
{
	//我就可以通过函数指针调用函数
	int result = funcpoint(i, j); //相当于调用函数，mf
	std::cout << result << std::endl;
}


class TC
{
public:
	TC() { std::cout << "TC()构造函数执行" << std::endl; }
	TC(const TC& tc) { std::cout << "TC()拷贝构造函数执行" << std::endl; }

	int operator()(int v1, int v2)
	{
		return v1 + v2;
	}
};

//template<typename T, typename F>
//void testfunc2(const T &a, const T &b, F funcpoint)
//{
//	int result = funcpoint(a, b);
//	std::cout << result << std::endl;
//}

//template<typename T, typename F = FunType>
//void testfunc2(const T &a, const T &b, F funcpoint = mf)
template<typename T, typename F=TC>
void testfunc2(const T &a, const T &b, F funcpoint=F())
{
	int result = funcpoint(a, b);
	std::cout << result << std::endl;
}

int main()
{

	//一 typename的使用场合
	//（1）在模板定义里，表明其后的模板参数是类型参数
	//typename
	//template<typename T, int a, int b>  //typename后边跟的是一个类型
	//int funcaddv2() {}

	//（2）使用类的类型成员，用typename来标识这是一个类型
	//::作用域运算符  访问类中的静态成员的时候， 类名::静态成员名
	//int Time::mystatic = 5;
	//::还可以用来访问类型成员
	//typename的第二个用法：通知编译器，一个名字代表的是一个类型。这里的typename不能换成class

	//std::string mytest = "I love China";
	//std::string::size_type size= getlength(mytest);


	//二 函数指针做其他函数的参数
	testfunc2(3, 4, mf);

	//三 函数模板趣味用法举例

	testfunc2(3, 4, TC());

	//四 默认模版参数
	//（a）类模版，类模版名后边必须用<>来提供额外的信息 <>表示这是一个模板
	myarray<> abc;   //完全用模板参数的缺省值
	myarray<int> def; //提供一个非缺省值，只提供一个，另外一个(第二个参数)用的是缺省值

	//（b）函数模板：老标准只能为类模板提供默认模版参数，c++11新标准可以为函数模板提供默认参数
	testfunc2(3, 4);
	//（1）同时给模板参数和函数参数提供缺省值
	//（2）注意写法 F function = F()
	//（3）TC重载()



	std::cout << "Hello World!\n"; 
}
