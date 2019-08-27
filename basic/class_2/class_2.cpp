// class_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// inline,const,mutable，this，static

#include "pch.h"
#include <iostream>
#include "Time.h"

//静态成员变量定义（分配内存）
int Time::mystatic = 15; //此处不需要加static，可以不给初值，那么系统默认给0，
//
//static int g_abc = 15; //也保存在静态存储区。限制该全局量只能够 用在本文件中
//
//void func()
//{
//	static int abc = 5; //局部静态变量
//	//...
//
//	abc = 8;
//}

int main()
{
	//一：在类定义中实现成员函数inline:类内的成员函数实现其实也叫类内的成员函数定义
	//这种直接在类的定义中实现的成员函数，会被当做inline内联函数来处理

	//二：成员函数末尾的const
	// const：常量，在成员函数屁股后面增加一个const。不但要在成员函数声明中增加const，也要在成员函数定义中增加const
	// 作用：告诉系统，这个成员函数，不会修改该对象里任何成员变量的值等等。也就是说，这个成员函数不会修改类Time的任何状态
	// 屁股后面加一个const后缀的成员函数 “常量成员函数”

	//const Time abc; //定义const对象，这种对象有限制
	//abc.initTime(12, 33, 44); //不可以，initTime并不是const成员函数，只能被飞const对象调用
	Time abc;
	abc.initTime(12, 33, 44);

	//const成员函数，则不管是const对象，还是非const，都可以调用const成员函数
		//而非const成员函数，不能够被const成员函数调用，只能被非const对象调用

	//三 mutable（不稳定，容易改变的意思），const的反义词，mutable的引入也正是为了突破const的限制
	//用mutable修饰一个成员变量，这个成员变量一旦被mutable修饰了，就表示，这个成员变量永远处于可以被修改状态
	//即便是在const结尾的成员函数中，也可以修改

	//四 返回自身对象的引用，this
	//如何理解这个this，调用成员函数时，编译器负责把这个对象的地址（&mytime）传递给这个成员函数中的一个隐藏的this形参
	//在系统角度看，任何对类成员的直接访问，都被看作是通过this做隐式调用的
	/*Time mytime;
	mytime.add_hour(3);*/

	//（a）this指针只能在成员函数中使用，全局函数、静态函数都不能使用this指针
	//（b）在普通成员函数中，this是一个指向非const对象的const指针（类型为Time，那么this就是Time *const this），表示this只能指向当前time对象
	//（c）在const成员函数中，this指针是一个指向const对象的const指针（类型为Time，this就是const Time *const this类型的指针）
	//
	//mytime.add_hour(3).add_minute(4);


	//五 static成员
	//有属于整个类的成员变量，这种成员变量就叫static成员变量
	//特点：不属于某个对象，属于整个类，我们一旦在某个对象中修改了这个成员变量的值，在其他对象中能够直接看到修改的结果
	//这种成员变量只有一个副本，对于这个成员变量的引用，我们用的是类名::成员变量名
	//成员函数前面也可以加static构成 静态成员函数。属于整个类的成员函数。调用时 类名::成员函数名
	//如何定义静态成员变量（分配内存）：我们一般会在某一个.cpp源文件的开头来定义这个静态成员变量。这样就能够保证在调用任何函数之前这个静态成员已经被初始化
	/*Time mytime1;
	mytime1.minute = 15;

	Time mytime2;
	mytime2.minute = 30;*/

	std::cout << Time::mystatic << std::endl;
	Time mytime1;
	mytime1.mystatic = 40;

	std::cout << Time::mystatic << std::endl;
	std::cout << mytime1.mystatic << std::endl;

	Time::mstaticfun(12);

    std::cout << "Hello World!\n"; 
}

