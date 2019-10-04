// STL_8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 适配器概念

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class A
{
public:
	bool operator()(int i)
	{
		return 40 < i; //希望大于40的元素被统计
	}
};


int main()
{
	//一 适配器概念
	//把一个既有的东西 进行适当的改造， 比如增加点东西，或者减少点东西，就构成了一个适配器
	//三种适配器： 容器适配器， 算法适配器，迭代器适配器

	//二 容器适配器（累模板）
	//2.1 stack:堆栈，是属于阉割版的deque
	//2.2 queue:队列，是属于阉割版的deque

	//三 算法适配器(函数适配器)：最典型的就是绑定器(binder)
	//3.1 绑定器
	//https://en.cppreference.com/w/
	//http://www.cplusplus.com/


	std::vector<int> myvector = { 50, 15,60,30,25 };
	//统计某个值出现的次数
	int cishu = std::count(myvector.begin(), myvector.end(), 30);

	//统计vector中大于40的元素出现的次数
	A mya;
	int cishu = std::count_if(myvector.begin(), myvector.end(), mya);

	//如果使用系统自带函数对象，需要使用绑定器
	//std::bind(std::less<int>(), 40, std::placeholders::_1);
					//less<int>的operator()的第一个参数绑定为40，那这样调用less<int>这个可调用对象时
					//第二个参数，就用这里的placeholders::_1表示，在调用这个函数时，被传入的第一个参数所取代
	/*auto bf = std::bind(std::less<int>(), 40, std::placeholders::_1);
	bf(19);*/

	cishu = std::count_if(myvector.begin(), myvector.end(), bind(
																std::less<int>(), //临时对象
																40,
																std::placeholders::_1
																));
	//（a）bind：函数适配器中的绑定器
	//（b）less<int>(): 是个函数对象(仿函数)，这里是个临时对象
	//（c）count_if: 是个算法



	//四 迭代器适配器
	//4.1 reverse_iterator: 反向迭代器
	std::vector<int> iv = { 100,200,300 };
	for (std::vector<int>::reverse_iterator riter = iv.rbegin(); riter != iv.rend(); riter++)
	{
		std::cout << *riter << std::endl;
	}

    std::cout << "Hello World!\n"; 
}

