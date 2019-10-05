// knowledge_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 理解模版类型推断，查看类型推断结果


#include "pch.h"
#include <iostream>

template<typename T>


int main()
{
	//总结：
	//（1）推断中，引用类型实参的引用类型等于不存在
	//（2）万能引用，实参为左值或者右值，推断的结果不同
	//（3）按值传递的实参，传递给形参时const属性不起作用，则传递过去的指针则另当别论
	//（4）数组或者函数类型在类型推断中被看做是指针，出发函数模板的形参是个引用




    std::cout << "Hello World!\n"; 
}

