// knowledge.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 二 万能引用universal reference

#include "pch.h"
#include <iostream>

template<typename T>
void func(const T &abc)
{
	return；
}

//void myfunc(int && tmp)

//修改为函数模板后，我们看到的事实：
//（1）tmp既能接受左值，又能接受右值了
//（2）tmp的类型是T&&
//从编译没报错来看，T被推断出来的应该不仅仅是int型(int &&tmp, 导致tmp只能接受右值)
template<typename T>
void myfunc(T&& tmp) //&&是属于tmp类型的一部分，和T类型没有关系
{
						//T&& 或者 tmp才是万能引用，而单独的T不是万能引用8
	std::cout << tmp << std::endl;
}

template<typename T>
class mytestC
{
public:
	void testfunc(T&& x) {}; //这个x是个右值引用，而不是万能引用，因为成员函数没有推断，是在创建类的时候推断

	template<typename T2>
	void testfunc2(T&& x) {}; //万能引用，进行了推断

};

int main()
{
	// 一 类型区别基本概念
	func(10);  //T是什么类型，abc是什么类型，T的类型和abc类型往往不太
				//T的类型是int， abc:  const int &
				//（1）调用函数模板时给的参数10会对T的类型产生影响
				//（2）abc的类型会对T的类型产生影响
	
	//二 universal reference 万能引用/未定义引用 基本认识
	myfunc(10); //右值ok
	int i = 100;
	myfunc(i); // myfunc()为普通函数时，错，右值引用不能绑左值
				// myfunc()为函数模板时，对

	//万能引用语境
	//（a）必须是函数模板
	//（b）必须是发生了模板类型推断并且函数模板形参的样子是： T&&；  auto也存在万能引用的概念
	// T&& : 就是万能引用

	//万能引用和右值引用解释起来的区别
	//（a）右值 引用得传递右值，否则编译器报错
	//（b）万能引用作函数参数时，外贸可以传递给它左值，也可以传递给它右值
	//		如果我们传递进去了左值，那么这个万能引用就变成了左值引用
	//		如果我们传递进去了右值，那么这个万能引用就变成了右值引用
	// T&& 就是一个万能引用类型

	//判断题
	//（1）void func(int &&tmp) //右值引用。因为没有模板
	//（2）template<typename T> void func(T&& tmp); //万能引用
	//（3）template<typename T> void func(std::vector<T> && tmp); //右值引用。因为T没和&&连在一起

	//三 万能引用资格的剥夺和辨识
	//（1）剥夺：const修饰词会剥夺一个引用成为万能引用的资格，成为右值引用
	//（2）辨认
    std::cout << "Hello World!\n"; 
}


