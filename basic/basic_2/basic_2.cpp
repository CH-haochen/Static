// basic_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//auto 头文件防御，引用，常量

#include "pch.h"
#include <iostream>
#include "head1.h"
#include "head2.h"

int main()
{
	//一 局部变量及初始化
	//随时用到随时定义


	//int abc = 5; //定义的时候初始化
	//int adb{ 5 };
	//std::cout << abc << std::endl;

	//int a[]{ 1,3,4 }; //注意这里没用等号,{}

	//int abc = 3.5f; //丢了.5，被系统截断
	//int adb{ 3.5f }; //无法编译成功，系统执行了一个从浮点数向整数的转换
 //   std::cout << "Hello World!\n"; 

	//二 auto 变量的自动类型推断
	// auto可以在声明变量的时候根据变量初始值的类型自动为此变量选择匹配的类型；（声明时要赋予初值(初始化）
	// auto自动类型推断发生在编译期间，所以使用auto不会造成程序效率降低
	auto bvalue = true; //bool
	auto ch = 'a';

	//三 头文件防卫式声明
	std::cout << g_globalh1 << std::endl;
	std::cout << g_globalh2 << std::endl;

	//#ifdef, ifndef 条件编译
	//#ifndef 标识符  //当标识符没有定义过(没有用#define定义过)，则对程序段进行编译
		//程序段
	//#endif

	//四 引用
	//引用理解成： 为变量起了另外一个名字，一般用&符号表示。起完别名后，这别名和变量本身我们就看成是同一个变量
	int value = 10;
	int &refval = value; //value的别名就说refval，&在这里不是求地址运算符，只是起标识作用
						//定义引用，并不额外占用内存，或者理解成，引用和原变量占用同一块内存（只是认为）
						//定义引用的时候必须初始化，不然你给谁起别名

	refval = 3;
	std::cout << value << std::endl;
	std::cout << refval << std::endl;

	//int &refval2;
	//int &refval3 = 10; //引用 必须绑定到变量上去，绑定到对象也可以。不能绑定到常量上去
	//float &refval2 = value;  不可以，类型要相同

	int a = 3;
	int &b = a; //引用，注意&符号在 = 的左边
	int *p = &a; //注意&符号在 = 的右边

	//五 常量 ： 不变的量
	// const：表示不变的意思
	const int var = 7; //一种承诺，表示这个变量的值我不会去改变（命名常量）
	//var = 15; 编译时报错，编译器会检查这个const承诺

	//强行改，没有意义
	/*int &var2 = (int &)var;
	var2 = 18;*/

	//std::cout << var << std::endl; //7
	//std::cout << var2 << std::endl; //18

	//constexpr 关键字： c++11才引入，它也是个常量的概念。在编译的时候求值，肯定能提升性能
	constexpr int var = 1;
	std::cout << var << std::endl;


	return 0;
}

