// memory_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// new delete 进一步认识

#include "pch.h"
#include <iostream>

class A
{
public:
	int m_i; //成员变量

	A()
	{
	}
};

int main()
{
	//一 总述与回顾：二章四节，五章二节

	//二 从new说起
	//2.1 new类对象时加不加括号的差别
	//2.1.1 如果是个空类，那么如下两种写法没有区别

	//2.1.2 类A中有成员变量
	//带括号的初始化会把一些和成员变量有关的内存清0，但不是整个对象的内存全部清0

	//2.1.3 当类A有构造函数，下面两种写法一样

	A *pa = new A(); 
	A *pa2 = new A;

	int *p3 = new int; //初值随机
	int *p4 = new int(); //初值0
	int *p5 = new int(100);  //初值100

	//2.2 new干了啥
	//new 可以叫 关键字/操作符
	//new 干了两个事儿： 一个是调用operator new(), 一个是调用了类A的构造函数（如果构造函数存在）

	//delete 
	//一个是调用了类A的析构函数（如果析构函数存在）， 一个是调用了operator delete();

    std::cout << "Hello World!\n"; 
}

