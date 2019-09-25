// ptr_4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// weak_ptr概述

#include "pch.h"
#include <iostream>

int main()
{
	//一： weak_ptr概述
	//weak:弱
	//强指的就是shared_ptr, 弱指的就是weak_ptr
	//weak_ptr: 也是个类模板，也是个只能指针。这个智能指针指向一个由shared_ptr管理的对象。但是weak_ptr这种指针不控制所指向对象的生命周期
	//换句话来说，将weak_ptr绑定到shared_ptr上并不会改变shared_ptr的引用计数(更确切的说，weak_ptr的构造和析构不会增加或者减少所指向对象的引用计数)
	//当shared_ptr需要释放所指定对象的时候照常释放，不管是否有weak_ptr指向该对象。weak这个意思“弱”
	//能力弱（弱共享/弱引用：共享其他的shared_ptr所指向的对象），控制不了所指对象的生存期

	//这个弱引用的作用： 可以理解成监视shared_ptr(强引用)的生命周琦用的，是一种对shared_ptr的扩充
		//weak_ptr不是一种独立的智能指针，不能用来操作所指向的资源，所以它看起来像一个shared_ptr的助手
	//weak_ptr能够监视到它所指向的对象是否存在

	//1.1 weak_ptr的创建
	//创建一个weak_ptr的时候，一般使用一个shared_ptr来初始化
	auto pi = std::make_shared<int>(100); //shared_ptr
	std::weak_ptr<int> piw(pi); //piw若共享pi，pi引用计数(强引用计数)不改变，但是弱引用计数会改变(弱引用计数从0变为1)
	//强引用计数才能决定对象的生存期，弱引用计数对对象生存期没有影响
	std::weak_ptr<int> piw;
	piw = pi;
	std::weak_ptr<int> piw2;
	piw2 = piw; //把weak_ptr赋给另一个weak_ptr，现在pi是一个强引用，piw和piw2是两个弱引用
	//lock()： 功能就是检查weak_ptr所指向的对象是否存在，如果存在，那么这个lock它就能够返回一个指向该对象的shared_ptr(指向对象的强引用计数加1)
	//        如果它所指向的对象不存在，lock会返回一个空的shared_ptr


	
	auto pi2 = piw.lock();
	if (pi2 != nullptr)
	{
		//所指向对象存在
		*pi2 = 12;
	}

	//weak_ptr可以判断指向的对象是否存在

	//二 weak_ptr常用操作 
	//2.1 use_count(): 获取与该弱指针共享对象的其他shared_ptr的数量，或者说获得当前所观测资源的强引用计数
	auto pi = std::make_shared<int>(100);
	auto pi2(pi);
	std::weak_ptr<int> piw(pi);
	int isc = piw.use_count();
	std::cout << isc << std::endl; //2

	//2.2 expried()： 是否过期的意思。若该指针的use_count()为0(表示该弱指针所指向的对象已经不存在了)，则返回True，否则返回False
		//换句话说，这个函数用来判断 所观测的资源是否已经被释放
	pi.reset();
	pi2.reset();
	if (piw.expired())
	{
		std::cout << "对象已过期" << std::endl;
	}

	//2.3 reset()
	//将该若引用指针设置为空，不影响指向该对象的强引用数量，但指向该对象的弱引用数量会减少1
	piw.reset();

	//2.4 lock()
	auto p1 = std::make_shared<int>(43);
	std::weak_ptr<int> pw;
	pw = p1;
	if (!pw.expired())
	{
		auto p2 = pw.lock(); //返回一个shared_ptr，并且此时强引用计数为2
		if (p2)
		{
			//do something...
			//...
			//离开这个范围，强引用计数 会恢复为1
		}
	}
	else
	{
		//已经过期
		//...
	}

	//三 尺寸问题
	//weak_ptr<int> pw;
	//weak_ptr的尺寸和shared_ptr尺寸一样大，是裸指针的2倍
	std::weak_ptr<int> pw;
	int *p;
	int len1 = sizeof(p); //4个字节，是个裸指针
	int len2 = sizeof(pw); //8个字节，两个裸指针

	auto pi = std::make_shared<int>(100);
	std::weak_ptr<int> piw(pi);

	//第一个裸指针 指向的是这个只能指针所指向的对象
	//第二个裸指针 指向一个很大的数据结构(控制块),这个控制块有：
			//1:所指对象的强引用计数
			//2:所指对象的弱引用计数
			//3:其他数据，比如自定义的删除器的指针等等


    std::cout << "Hello World!\n"; 
}

