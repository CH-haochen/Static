// class_12.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

int calc(const std::string &strsource, char ch) //strsource这个形参就绑定到了string临时对象上
{
	const char *p = strsource.c_str();
	int icount = 0;
	//..............
	return icount;
}

int main()
{
	//产生临时对象的情况和解决：三种情况和解决方案
	//（1）以传值的方式给函数传递参数
	//     解决方案：传引用
	//（2）类型转换生成的临时对象/隐式类型转换以保证函数调用成功
	// CTempValue sum;
	// sum = 1000;  这里产生了一个真正的临时对象
	//（a）用1000这个数字创建了一个类型为CTempValue的临时对象
	//（b）调用拷贝赋值运算符把这个临时对象里面的各个成员值赋给了sum对象
	//（c）销毁这个临时创建的CTempValue对象
	// 解决方案：
	// CTempValue sum = 1000; //把定义对象和给对象赋初值放在一行上
	//							为sum对象预留了空间。用1000构造sum对象，而且是直接构造在sum对象预留空间里

	// 隐式类型转换以保证函数调用成功
	char mystr[100] = "I love China";
	int result = calc(mystr, 'h'); //char[] string
	//c++语言只会为const引用(const string &strsource)产生临时变量，而不会为非const引用(string &strsource)这种参数产生临时变量

	//（3）函数返回对象的时候
	//CtempValue Double(CTempValue &ts)
	//{
		//CtempValue temp;
		//temp.val1 = ts.val1 * 2;
		//temp.val1 = ts.val1 * 2;
		//return temp;
	//}

	//CtempValue ts1(10, 20); //因为返回临时对象导致占用了一个拷贝构造函数和一个析构函数
	//Double(ts1);
	//CtempValue ts3 = Double(ts1);

	//Double() 函数引起的消耗
	//CtempValue tmpm; 会消耗一个构造函数和一个析构函数
	//return tmpm; 产生临时对象，占用一个拷贝构造函数和析构函数

	//CtempValue Double(CTempValue &ts)
	//{
		//return CtempValue(ts.val1 * 2, ts.val2 * 2);
	//}


	//再举一例：类外运算符重载








    std::cout << "Hello World!\n"; 
}

