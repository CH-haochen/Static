// class_13.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//对象移动、移动构造函数、移动赋值运算符

#include "pch.h"
#include <iostream>

class B
{
public:
	B() : m_bm(100)
	{
		std::cout << "类B的构造函数执行了" << std::endl;
	}

	//拷贝构造函数
	B(const B &tmp) : m_bm(tmp.m_bm)
	{
		//m_bm = tmp.m_bm;
		std::cout << "类B的拷贝构造函数执行了" << std::endl;
	}

	virtual ~B()
	{
		std::cout << "类B的析构函数执行了" << std::endl;
	}

	int m_bm;
};

class A
{
public:
	//默认构造函数
	A() :m_pb(new B()) //这里会调用类B的构造函数
	{
		std::cout << "类A的构造函数执行了" << std::endl;
	}

	//拷贝构造函数
	A(const A &tmpa) : m_pb(new B(*(tmpa.m_pb))) //调用类B的拷贝构造函数
	{
		std::cout << "类A的拷贝构造函数执行了" << std::endl;
	}

	//移动构造函数
	//noexcept: 通知标准库我们这个移动构造函数不抛出任何异常（提高编译器工作效率）
	A(A &&tmpa) noexcept:m_pb(tmpa.m_pb)
	{
		tmpa.m_pb = nullptr;
		std::cout << "类A的移动构造函数执行了" << std::endl;
	}

	//拷贝赋值运算符
	A & operator=(const A &tmpa)
	{
		if (this == &tmpa)
			return *this;
		
		delete m_pb;
		m_pb = new B(*(tmpa.m_pb));
		std::cout << "类A的拷贝赋值运算符执行了" << std::endl;
		return *this;
	}

	//移动赋值运算符
	A & operator=(A &&tmpa) noexcept
	{
		if (this == &tmpa)
			return *this;

		delete m_pb;
		m_pb = tmpa.m_pb;
		tmpa.m_pb = nullptr;
		std::cout << "类A的移动赋值运算符执行了" << std::endl;
		return *this;
	}



	virtual ~A()
	{
		delete m_pb;
		std::cout << "类A的析构函数执行了" << std::endl;
	}

private:
	B *m_pb;

};


static A getA()
{
	A a;
	return a; // 临时对象, 调用拷贝构造函数
			//如果类A有移动构造函数，那么会调用移动构造函数，把a对象的数据移动给了 临时对象
}

int main()
{

	//一 对象移动的概念
	//

	//二 移动构造函数和移动赋值运算符概念
	//c++11  std::move  效率问题。
	//移动构造函数：c++11 进一步提高程序效率。
	//vector
	//说明：
	//（1）A移动B，那么A对象我们就不能再使用了
	//（2）移动：并不是把内存中的数据从 一个地址 捣腾到 另外一个地址。只是所有者变更
	// 拷贝构造函数：Time::Time(const Time &tmptime){....} //const左值引用
	// 移动构造函数：Time::Time(const Time &&tmptime)     //右值引用 &&

	//移动构造函数 和 移动赋值运算符应该完成的功能
	//（1）完成必要的内存移动，斩断原对象和内存的关系
	//（2）确保移动后原对象处于一种“即便被销毁也没有什么问题”的一种状态 A->B,确保不再使用A，而是应该去使用B

	//三 移动构造函数演示
	B *pb = new B();
	pb->m_bm = 10;
	B *pb2 = new B(*pb);

	delete pb;
	delete pb2;


	A a = getA();
	// 调用了1次 构造函数，1次拷贝构造函数， 两次析构函数 
	// 增加了移动构造函数后：调用了1次构造函数，一次移动构造函数，两次析构函数
	A a1(a); //拷贝构造函数
	A a2(std::move(a)); //移动构造函数
	A &&a3(std::move(a)); //这了没有建立新对象，根本不会调用什么移动构造函数
							//效果等同于把对象a有了一个新别名a3，后续建议用a3来操作，不要使用名字a
	A &&a4 = getA(); //从getA()返回的临时对象被a4接管了（别名）

	//四 移动赋值运算符
	A a = getA();
	A a2;
	a2 = std::move(a); //调用移动赋值运算符

	//五 合成的移动操作
	// 某些条件下，编译器能合成移动构造函数，移动赋值运算符
	//（1）有自己的拷贝构造函数，自己的拷贝赋值运算符，或者自己的析构，那么编译器就不会为它合成 移动构造函数和移动赋值运算符
	//	所以，有一些类，是没有移动构造函数和移动赋值运算符的
	//（2）如果没有自己的移动构造函数和移动赋值运算符，那么系统会调用我们自己写的拷贝构造函数和拷贝赋值运算符来代替
	//（3）只有一个类没定义任何自己版本的拷贝构造成员（没有拷贝构造函数也没有拷贝赋值运算符），且类的每个非静态成员都可以移动时，编译器才会改为该类合成移动构造函数或者移动赋值运算符
	//什么叫成员可以移动？
	//（a）内置类型是可以移动的
	//（b）类类型的成员，则这个类要有对应的移动操作相关的函数，就可以移动

	//六 总结
	//（1）尽量给类增加移动构造函数和移动赋值运算符
	//（2）尽量给移动加上noexpect
	//（3）该给nullptr的就要给nullptr，让被移动的对象随时处于一种能够被析构的状态
	//（4） 没有移动，会用拷贝代替
	

    std::cout << "Hello World!\n"; 
}


