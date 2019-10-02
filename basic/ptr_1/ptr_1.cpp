// ptr_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

class A
{
public:
	A()
	{
		std::cout << "A" << std::endl;
	}

};

int main()
{
	//一 直接管理内存 new/delete
	//概念“值初始化”：用()来初始化
	std::string *mystr2 = new std::string;
	std::string *mystr3 = new std::string(); //也是空字符串，和mystr没区别

	int *point = new int;  //值未初始化
	int *point2 = new int(); //值初始化为0

	A a;
	A *pa = new A;
	A *pa2 = new A();  //是否值初始化效果一样，都是调用A的构造函数

	//new 对象的时候，能够进行“值初始化”就进行一下为好，防止它的值没有被初始化
	
	//c++11中，auto可以和new配合使用
	std::string *mystr5 = new std::string(5, 'a');
	auto mystr6 = new auto(mystr5); //mystr6 = string **
	
	//const对象也可以动态分配
	const int *pointci = new const int(100);

	//new/delete说明：
	//（a）成对儿使用，delete的作用是回收用new分配的内存（释放内存）；不是new出来的内存，是不能用delete来释放
	//（b）delete一块内存（可能多个指针指向这块儿内存），只能delete一次，不能delete多次。delete后，这块儿内存就不能使用；空指针可以删除多次，但是没什么意义

	//注意事项总结：
	//（1）new出来的千万不要忘记delete，否则内存泄露
	//（2）delete后的内存不能再使用，否则异常 
	//（3）提倡delete一个指针后，给该指针一个nullptr
	//（4）同一块内存释放两次的问题，也会报异常

	

    std::cout << "Hello World!\n"; 
}

