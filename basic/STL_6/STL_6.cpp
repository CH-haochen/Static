// STL_6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 算法

#include "pch.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <map>


//void myfunc(int i)
//{
//	std::cout << i << std::endl;
//}

bool myfunc(int i, int j)
{
	//return i < j; //从小到大排序
	return i > j; //从大到小排序
}

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
	//一 算法概述：理解为函数模板（全局）
	//比如：查找，排序等等
	//算法的前两个形参的类型，一般都是迭代器类型，用来表示容器中的元素的一个区间

	std::list<int> mylist = { 100, 200,300 };
	std::list<int>::iterator iterbg = mylist.begin();
	std::list<int>::iterator itered = mylist.end(); //最后一个元素的下一个位置
	//算法名(iterbg,itered) ,传递进去的应该是一个 前闭后开的区间[begin(), end())

	//算法是一种搭配迭代器来使用的全局函数；算法跟具体容器没关联，只跟迭代器有关联

	//二 算法内部一些处理
	//算法会根据传递进来的迭代器来分析出迭代器种类(五种之一)，不同的种类迭代器，算法会有不同的处理


	//三一些典型算法举例
	//当有成员函数和全局函数(算法)同时存在时，优先考虑使用成员函数
	//算法头文件 #include <algorithm>
	//3.1 for_each:

	

	std::vector<int> myvector = { 1,2,3,4,5 };
	std::for_each(myvector.begin(), myvector.end(), myfunc);


	//3.2 find
	std::vector<int> myvector = { 1,2,3,4,5 };
	std::vector<int>::iterator finditer = std::find(myvector.begin(), myvector.end(), 40);
	if (finditer != myvector.end())
	{
		//找到了
	}
	else 
	{
		//没找到
	}

	std::map<int, std::string> mymap;
	mymap.insert(std::make_pair(1, "老李"));
	mymap.insert(std::make_pair(2, "老赵"));
	mymap.insert(std::pair<int, std::string>(3, "老李"));
	auto iter = mymap.find(2); //优先使用自己的成员函数
	if (iter != mymap.end())
	{
		//找到了
	}

	//3.3 find_if
	//找大于15的第一个数
	std::vector<int>::iterator result = std::find_if(myvector.begin(), myvector.end(), [](int val) { //lambda表达式也是可调用对象
		if (val > 15)
			true;
		return false;
	});

	if (result != myvector.end())
	{
		//找到了
	}

	//3.4 sort
	std::vector<int> myvector = { 2,1, 6,4,5 };
	std::sort(myvector.begin(), myvector.end()); //缺省按照从小到大的顺序排列
	std::sort(myvector.begin(), myvector.begin()+3);  //只有前三个元素参与排序

	//若要从大到小排序，我们可以写自定义比较函数，这个函数返回bool
	std::sort(myvector.begin(), myvector.end(), myfunc); //缺省按照从小到大的顺序排列
	A mya;
	std::sort(myvector.begin(), myvector.end(), mya); //缺省按照从小到大的顺序排列



    std::cout << "Hello World!\n"; 
}
