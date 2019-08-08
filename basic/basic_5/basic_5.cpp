// basic_5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//函数新特性、内联函数、const详解

#include "pch.h"
#include <iostream>
#include "head1.h"

//void fun123(int, int); 函数声明

//void func123(int a, int b) 
//auto func123(int a, int b) ->void; //函数声明
//auto func123(int a, int b) ->void	//函数定义
//{
//
//}

//inline int myfunc(int testv) //函数定义前加inline，这个普通函数就为内联函数
//{
//	return 1;
//}

//int *myfunc()
//{
//	int temvalue = 9; //临时变量
//	return &temvalue;  //这不可以，因为函数执行完毕后，temvalue这段内存被系统回收，你不能够再使用
//}

//int &myfunc()
//{
//	int temvalue = 9; //临时变量
//	return temvalue;  //又是一个巨大隐患
//}

struct student
{
	int num;
};

void fs(const student &stu)
{
}

void fs2(const int &i)
{
}


int main()
{

	//一 函数回顾与后置返回类型
	// 函数定义中，形参如果在函数体内用不到的话，则可以不给形参变量名字，只给其类型
	// 函数声明时，可以只有形参类型，没有形参名
	// 把函数返回类型房子函数名字之前，这种写法，叫前置返回类型
	// c++11中，后置返回类型。就是在函数声明和定义中，把返回类型写在参数列表之后
	//	前面放auto，表示函数返回类型放倒参数列表之后，而放在参数列表之后的类型是通过 ->开始的 

	//二 内联函数 函数定义前加inline，这个普通函数就为内联函数
	// 函数体很小，调用又很频繁的这种函数。咱们引入inline
	//（1）inline影响编译器，在编译阶段对inline这种函数进行处理，系统尝试将调用该函数的动作替换为函数本体。通过这种方式，来提升性能
	//int abc = myfunc(5); //int abc = 1;
	//（2）inline只是我们开发者对编译器的一个建议，编译器可以尝试去做，也可以不去做，这取决于编译器的诊断功能，也就是说，决定权在编译器，我们控制不了
	//（3）内联函数的定义就要放在头文件。这样需要用到这个内敛函数的.cpp文件都能够通过#include 把这个内联函数的源代码#include进来
		// 以便找到这个函数的本体源代码并尝试将该函数的调用替换为函数体内的语句
	// 优缺点：
	// 代码膨胀的问题，所以内联函数的函数体尽量要小

	//注意：各种编译器对inline的处理各不相同。inline函数尽量简单，代码尽可能少。循环，分支，递归调用尽量不要出现在inline函数中
	// 否则的话，编译器很可能会因为你写这些代码的原因拒绝让这个函数成为inline函数

	//三 函数杂合用法总结
	//（1）函数返回类型为void，表示函数不返回任何类型。但是我们可以调用一个 返回类型是void的函数 让 它作为另一个 返回类型是void的函数的返回值
	//（2）函数返回指针和返回引用的情况
	//int *myfunc()
	//{
	//	int temvalue = 9; //临时变量
	//	return &temvalue;  //这不可以，因为函数执行完毕后，temvalue这段内存被系统回收，你不能够再使用
	//}

	//int * p = myfunc();
	//*p = 6; //你往一个不属于你的地址写了数字


	//int &myfunc()
	//{
	//	int temvalue = 9; //临时变量
	//	return temvalue;  //又是一个巨大隐患
	//}

	//int &k = myfunc();
	//std::cout << &k << std::endl;
	//k = 10; //你往一个不属于你的地址写了数字

	//int k = myfunc();
	//std::cout << &k << std::endl;
	//k = 10; //安全的

 //   std::cout << "Hello World!\n"; 
	//（3）没有形参可以保持形参列表为空()，或者int func(void);
	//（4）如果一个函数我们如果不调用的话，则该函数可以只有声明部分，没有定义部分
	//（5）普通函数，定义只能定义一次（定义放在.cpp文件中），声明可以声明多次。
	//（6）void func(int &a, int &b) 在c++中，更习惯用引用类型的形参来取代指针类型的形参

	//四 const char *、char const *、char * const 三者的区别
	//4.1 const char *p;
	char str[] = "I love China";
	const char *p; //p指向的东西不能通过p来修改
	p = str;
	//*p = 'Y'; //语法错误
	p++; //p现在指向的就是" love China"
	str[0] = 'Y';

	//4.2 char const * 等价于 const char *

	//4.3 char * const p 
	//char str[] = "I love China";
	//char * const p = str; //定义的时候必须初始化
	//						//p一旦指向了一个东西后，就不可以再指向其他东西了
	////p++; //不可以
	//*p = 'Y'; //但是可以修改p指向目标的内容

	//char str[] = "I love China";
	//const char * const p = str; //p指向的地址不能变，内容也不能变

	//引用
	int i = 100;
	const int &a = i; //代表a的内容不能通过a自己来修改
	i = 100;
	//a = 500; //不合法
	//int &b = 31; //错误
	const int &b = 31; //可以 分配了内存的

	//五 函数形参中带const
	student abc;
	abc.num = 100;
	fs(abc);

	//把形参写成const的形式有很多好处
	//（1）可以防止你无意中修改了形参值导致实参值被无意修改
	//（2）实参类型可以更灵活


}

