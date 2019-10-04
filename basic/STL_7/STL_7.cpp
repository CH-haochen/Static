// STL_7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//函数对象回顾，系统函数对象及范例

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>


class A
{
public:
	bool operator()(int i, int j)
	{
		return i > j; //从大到小排序
	}
};


int main()
{

	//一 函数对象/仿函数回顾
	//函数对象 在STL中，一般都是和算法配合使用，从而实现一些功能，这些函数对象主要用来服务于算法
	//函数对象：函数，可调用对象，lambda表达式
	std::vector<int> myvector = { 2,1, 6,4,5 };
	A mya;
	std::sort(myvector.begin(), myvector.end(), mya); //缺省按照从小到大的顺序排列
    
	//二 标准库中定义的函数对象
	//标准库中也给我们提供了很多可以现成拿来使用的函数对象，使用它之前，需要添加functional头文件
	//（a）算术运算类
	//（b）关系运算类
	//（c）逻辑运算类
	//（d）位运算类

	//三 标准库中定义的函数对象范例
	
	std::vector<int> myvector = { 2,1, 6,4,5 };
	//A mya; //自定义的函数对象
	//std::sort(myvector.begin(), myvector.end(), mya); //缺省按照从小到大的顺序排列
	std::sort(myvector.begin(), myvector.end(), std::greater<int>()); //std::greater<int>()产生临时对象，这个临时对象是系统定义的





	
	std::cout << "Hello World!\n"; 
}

