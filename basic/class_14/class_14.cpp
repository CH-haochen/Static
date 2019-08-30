// class_14.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//继承的构造函数、多重继承、虚继承

#include "pch.h"
#include <iostream>

//class A
//{
//public:
//	A() {}
//	//A(int i, int j, int k){}
//	A(int i, int j, int k=5) {}
//
//};
//
//class B : public A
//{
//public:
//	/*B(int i, int j, int k) : A(i, j, k)
//	{
//
//	}*/
//	using A::A; //继承A的构造函数。 using：就让某个名字在当前作用域内可见
//				//遇到这条代码的时候，会把基类的每个构造函数，都生成一个与之对应的派生类构造函数
//				//b(构造函数形参列表。。。):A(照抄的构造函数形参列表){} 函数体为空
//				//B(int i, int j, int k) : A(i, j, k){}
//	//如果基类A的构造函数有默认参数的话，那么编译器遇到这种using A::A的时候，就会帮咋那么在派生类B中构造出多个构造函数来
//	//（a）第一个构造函数是带有所有参数的构造函数
//	//（b）其余的构造函数，每个分别省略掉 一个默认参数
//	//	B(int i, int j, int k) : A(i, j, k){}
//	//	B(int i, int j) : A(i, j){}
//	//如果类B，只含有using A::A从A类继承来的构造函数的话，那么编译器是会给它合成默认的构造函数的
//};


class Grand
{
public:
	Grand(int i) :m_valuegrand(i) 
	{
		std::cout << "Grand构造函数执行" << std::endl;
	}

	virtual ~Grand() 
	{
		std::cout << "Grand析构函数执行" << std::endl;
	}

	void myInfo()
	{
		std::cout << m_valuegrand << std::endl;
	}

public:
	int m_valuegrand;

public:
	static int m_static; //声明一个静态成员
};

//为了能够使用，我们定义这个静态成员变量（分配内存）
int Grand::m_static = 5; //如果你在代码中不用m_static,那么你可以不定义，如果代码中用到m_static，则必须定义，否则会出错

//class A : public Grand //继承自爷爷类
class A : virtual public Grand //类A从Grand虚继承
{
public:
	A(int i) :Grand(i), m_valuea(i)  //每个子类的构造函数，负责解决自己父类的初始化问题
	{
		std::cout << "A构造函数执行" << std::endl;
	}

	virtual ~A()
	{
		std::cout << "A析构函数执行" << std::endl;
	}

	void myInfo()
	{
		std::cout << m_valuea << std::endl;
	}

public:
	int m_valuea;

};

//class A2 : public Grand //继承自爷爷类
class A2 : virtual public Grand //类A2从Grand虚继承
{
public:
	A2(int i) :Grand(i), m_valuea2(i)  //每个子类的构造函数，负责解决自己父类的初始化问题
	{
		std::cout << "A2构造函数执行" << std::endl;
	}

	virtual ~A2()
	{
		std::cout << "A2析构函数执行" << std::endl;
	}

	void myInfo()
	{
		std::cout << m_valuea2 << std::endl;
	}

public:
	int m_valuea2;

};

class B  
{
public:
	B(int i) : m_valueb(i)
	{
		std::cout << "B构造函数执行" << std::endl;
	}

	virtual ~B()
	{
		std::cout << "B析构函数执行" << std::endl;
	}

	void myInfo()
	{
		std::cout << m_valueb << std::endl;
	}

public:
	int m_valueb;
};

//类C，同时继承父类A和父类B
//class C : public A, public B
class C : public A, public A2, public B
{
public:
	/*C(int i, int j, int k) :A(i), A2(i), B(j), m_valuec(k) */
	C(int i, int j, int k) :A(i), A2(i), B(j),Grand(i), m_valuec(k) //虚基类时，孙子C来初始化爷爷Grand
	{
		std::cout << "C构造函数执行" << std::endl;
	}

	virtual ~C()
	{
		std::cout << "C析构函数执行" << std::endl;
	}

	void myInfoC()
	{
		A::myInfo(); //调用A的myInfo函数
		B::myInfo(); //调用B的myInfo函数
		//std::cout << m_valuec << std::endl;
	}

public:
	int m_valuec;
};


//class A
//{
//public:
//	A(int tv) {}
//
//};
//
//class B
//{
//public:
//	B(int tv) {}
//
//};
//
//class C : public A, public B
//{
//public:
//	using A::A; //继承A的构造函数 C(int tv):A(tv){}
//	using B::B; //继承A的构造函数 C(int tv):B(tv){}
//	//如果一个类从它的基类中继承了相同的构造函数，这个类必须为该构造函数定义它自己的版本
//	C(int tv) : A(tv), B(tv) {}
//};

int main()
{
	//一 继承的构造函数
	//一个类只继承其直接基类（父类）的构造函数。默认、拷贝、移动构造函数是不能被继承的
	//B ad(3, 4, 5);
	//如果基类含有多个构造函数，则多数情况下，派生类会继承所有这些构造函数，但如下例外情况：
	//（1）如果你在派生类中定义的构造函数与基类构造函数有相同的参数列表，那么从基类中继承来的构造函数会被你在派生类中的定义覆盖掉
	//（2）默认、拷贝、移动构造函数 不会被继承
	//B ad(3, 4);


	//二 多重继承
	//（2.1）多重继承概述
	//如果从多个父类来产生出子类：多重继承
	/*C ctest(10, 20, 50);
	ctest.myInfoC();*/
	//ctest.myInfo();  //非法。要增加作用域，明确的告诉系统调用的是父类A还是父类B的成员函数
	//ctest.A::myInfo();
	//如果在自己的类中定义了myInfo，则就会覆盖掉父类中的同名函数

	//派生类会包含每个基类的子对象


	//2.2 静态成员变量
	//静态成员属于类，不属于对象

	//C ctest(10, 20, 50);
	//Grand::m_static = 1; //可以用类名来引用静态变量
	//A::m_static = 2;
	//C::m_static = 4;
	//ctest.m_static = 19; //可以用对象名来引用静态变量
	
	//2.3 派生类构造函数与析构函数
	//（a）构造一个派生类对象将同时构造并初始化所有基类子对象
	//（b）派生类的构造函数初始化列表只初始化它的直接基类。每个类的构造函数都负责初始化它的直接基类，就会让所有类都得到初始化
	//（c）派生类构造函数初始化列表将实参分别传递给每个直接基类；基类的构造顺序跟“派生列表”中基类的出现顺序一致
	//						派生列表 class C : public A, public B 先构造A，再构造B
	
	//

	//C ctest(10, 20, 50);
	
	//2.4 从多个父类继承构造函数
	//子类要定义同参数的构造函数 自己的版本

	//三 类型转换
	//基类指针可以指向一个派生类对象
	/*Grand *pg = new C(1, 2, 3);
	A *pa = new C(1, 2, 3);
	B *pb = new C(1, 2, 3);*/

	//四 虚基类（virtual base class），虚继承（虚派生）
	//派生列表中，同一个基类只能出现一次，但是如下两种情况例外
	//（a）派生类可以通过它的两个直接基类分别继承同一个间接基类
	//（b）直接继承某个基类，然后通过另一个基类间接继承该类
	C ctest(10, 20, 50);
	//导致Grand被构造了两次，继承2次Grand是多余的，占空间，名字冲突
	ctest.m_valuegrand = 18; //非法，名字冲突
	//虚基类：无论这个类在继承体系中出现多少次，派生类中，都只会包含唯一一个共享的虚基类子内容
	//这种虚继承只对C类有意义，其实对C的父类A，A2没有意义
	//换句话来说，A,A2从Grand类虚继承，只影响到从A，A2这些类中进一步派生出来的类C，而对A，A2本身没有什么影响
	//每个Grand的子类都要虚继承Grand类，那么才能保证Grand的孙类能够虚继承Grand
	//只要子类中都加virtual继承，那么Grand类自然就成为了“虚基类”
	//virtual：表达一种意愿：表示后续从（类A，A2）派生的类中应该共享虚基类Grand的同一份实例

	//说明两点
	//（1）现在是C类初始化Grand类，如果以后C类有个孩子，则由C类的孩子初始化Grand类；换句话说，虚基类Grand是由最低层派生类来初始化
	//（2）初始化顺序问题：先初始化虚基类部分，然后再按照派生列表中出现顺序来初始化其他类

	//五 总结
	//小心虚继承，不太提倡使用
	//简单，不容易出现二义性，实在必要，才使用多重继承。能用单一继承解决的问题就不要用多重继承了
}
