// basic_4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 结构、权限修饰符、类简介
#include "pch.h"
#include <iostream>

int main()
{

	//二：public和private权限修饰符：public(公有)，private(私有),protected（保护）

	//三：类
	//结构和类的区别：
	//（1）类只有c++中才有这个概念，c中没有类
	//（2）结构用struct定义，类用class定义
	//（3）c++结构内部的成员变量和成员函数，默认的访问级别都是public
	//     c++类内部的成员变量和成员函数，默认的访问级别都是private
	//（4）c++结构体继承默认的是public, c++类继承默认的是private
    std::cout << "Hello World!\n"; 
}

