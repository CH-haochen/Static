// template_8.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//可变参数模板续、模板模板参数

#include "pch.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <list>

//class B
//{
//public:
//	//...
//};
//
//class A
//{
//public:
//	B b; //A中包含B对象
//};

//
//template<typename... Args> class myclasst {}; //主模板
//
//template<>
//class myclasst<> //0个模板参数的特化版本
//{
//	myclasst()
//	{
//		printf("myclasst() 执行了，this= %p\n", this);
//	}
//
//};

//template<typename First, typename... Others>
//class myclasst<First, Others...> : private myclasst<Others...>
//{
//public:
//	myclasst() : m_i(0)
//	{
//		printf("myclasst() 执行了，this= %p\n", this);
//	}
//	myclasst(First parf, Others...paro) :m_i(parf), myclasst<Others...>(parf...)
//	{
//		std::cout << "m_i=" << m_i << std::endl;
//	}
//
//	First m_i;
//};

//template<typename First, typename... Others>
//class myclasst<First, Others...> 
//{
//public:
//	myclasst() : m_i(0)
//	{
//		printf("myclasst() 执行了，this= %p\n", this);
//	}
//	myclasst(First parf, Others...paro) :m_i(parf), m_o(paro...)
//	{
//		std::cout << "m_i=" << m_i << std::endl;
//	}
//
//	First m_i;
//	myclasst<Others...> m_o; //组合关系(复合关系）
//};


//void func()
//{
//	myclasst<int, float, double> myc;
//	myclasst<int, float, double> myc(12, 13.5f, 23);
//	//范例取材：标准库中的tuple(元组)
//}


//
////mycount用于统计，从0开始，mymaxcount表示参数数量
//template<int mycount, int mymaxcount, typename... T>
//class myclasst
//{
//public:
//	static void mysfunc(const std::tuple<T...> &t)
//	{
//		std::cout << "value = " << std::get<mycount>(t) << std::endl;
//		myclasst<mycount + 1, mymaxcount, T...>::mysfunc(t); //递归调用
//	}
//};
//
////需要有一个特化版本，用于结束递归调用
//template<int mymaxcount, typename... T>
//class myclasst<mymaxcount, mymaxcount, T...>
//{
//public:
//	static void mysfunc(const std::tuple<T...> &t)
//	{
//	
//	}
//
//};
//
//template<typename... T>
//void myfunct(const std::tuple<T...> &t) //可变参函数模板
//{
//	myclasst<0, sizeof...(T), T...>::mysfunc(t);
//}
//
//void func()
//{
//	std::tuple<float, int, int> mytuple(12.5f, 100, 52); //一个tuple（元组）：一堆各种东西的组合
//	/*std::cout << std::get<0>(mytuple) << std::endl;
//	std::cout << std::get<1>(mytuple) << std::endl;
//	std::cout << std::get<2>(mytuple) << std::endl;*/
//	myfunct(mytuple);
//}

template<
		typename T,  //类型模板参数
		template<class> class Container //这就是一个模板 模板参数
		//template<typename W> typename Container  //效果相同
		>
class myclass
{
public:
	T m_i;
	Container<T> myc; //Container作为一个类模板来使用的（因为它屁股后面代码<T>）
						//要明白，如果你要想把Container当成一个类模板来使用，你就必须把它弄成“模板模板参数”这种写法
	myclass()
	{
		for (int i = 0; i < 10; i++)
		{
			myc.push_back(i);
		}
	}
};

template<typename T> using MYVec = std::vector<T, std::allocator<T>>; //写法套路固定
template<typename T> using MYList = std::list<T, std::allocator<T>>;

void func()
{
	myclass<int, MYVec> myvceobj; //本意是往容器中塞入元素，元素类型为int
}

int main()
{
	//一 可变参数模板
	//1.1 通过递归组合方式展开参数包
	//组合关系（复合关系）：类A和类B之间就是一种组合关系
	//1.2 通过tuple和递归调用展开参数包
	//这种展开参数包的方式需要写类的特化版本，有一定难度
	//实现思路：计数器从0开始，每处理一个参数，计数器+1，一直把所有参数处理完。最后搞一个模板偏特化，作为递归调用结束

	//1.3 总结 
	//获取参数包里参数的方式有很多种，一般都离不开递归手段


	//二 模板 模板参数
	//这表示这是个模板参数，这个模板参数本身，又是一个模板

    std::cout << "Hello World!\n"; 
}
