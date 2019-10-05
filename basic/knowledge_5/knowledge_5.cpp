// knowledge_5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 理解auto类型推断、auto应用场合


#include "pch.h"
#include <iostream>

void myfunc3(double i, int j)
{}

class CT
{
public:
	//auto m_i = 12; 

};


int main()
{
	//一 std::forward用法补充
	int ix = 12; //ix左值
	//int &&def = std::move(ix);
	int &&def = std::forward<int>(ix); //forward在这里能够把左值转换为右值

	//二 auto 类型推断
	int i = 18;			//int
	const int j = i;	//const int
	const int &k = i;	//const int &

	//auto 用于变量的自动类型推断
	//特点：
	//（a）auto自动类型推断发生在编译期，所以不会影响程序执行的性能
	//（b）auto定义变量必须立即初始化，这样才能推断
	//（c）auto使用灵魂，和指针，引用，const限定符结合使用

	//auto类型推断和函数模板类型推断非常类似
	//auto推导出来后代表一个具体类型。

	//（a）传值方式(非指针，非引用)：传值方式的auto会抛弃引用，const等限定符
	auto x = 28; //x=int, auto = int
	const auto x2 = x; //x2 = const int, auto = int

	//（b）指针或者引用类型但不是万能引用。 不会抛弃const等限定符，但是会丢弃引用
	const auto &xy = x; //xy = const int &, auto = int
	auto xy2 = xy; //xy2 = int, auto = int  传值方式：引用类型会被抛弃
	auto &xy3 = xy; //const int &, auto = const int, 引用会被丢钱，但const被保留
	auto y = new auto(100); //y = int *, auto = int*
	const auto *xp = &x; //xp = const int *, auto = int
	auto *xp2 = &x; //xp2 = int *, auto = int
	auto xp3 = &x;  //xp3 = int *, auto = int *

	//（c）万能引用类型 T&&
	auto && wnyy1 = x; //x是左值，auto = int &, wnyy1 = int &
	auto && wnyy2 = x2; //x2是左值，auto = int &, wnyy2 = const int &
	auto && wnyy3 = 100; //x3是左值，auto = int, wnyy3 =  int &&


	//三 auto类型针对数组和函数的推断
	const char mystr[] = "I love China!";//mystr = const char [14]
	auto myarr = mystr; //const char *
	auto &myarr2 = mystr; //const char (&) [14]

	int a[2] = { 1,3 };
	auto aauto = a; //aauto = int *, auto = int *

	auto tmpf = myfunc3; //void(*)(double ,int) 函数指针

	auto &tmpf = myfunc3; //void(&)(double ,int) 函数引用


	//四 auto类型std::initializer_list的特殊推断
	auto x = 10; //x = int
	auto x2(20); //x2 = int
	auto x3 = { 30 }; //x3 = std::initializer_list<int>, auto遇到={}， 推倒规则就不一样了
	auto x4{ 30 }; //x4 = int

	//std::initializer_list<int> c++引入的类型，表示某种特定的值的数组 

	//auto还可以放在函数返回类型上 

	//五 auto不适用场合
	//（1）auto不能用于函数参数，比如void func(auto i){}
	//（2）普通成员变量不可以是auto类型，但是static const auto m_si = 15；被允许

	//六 适用场合



    std::cout << "Hello World!\n"; 
}

