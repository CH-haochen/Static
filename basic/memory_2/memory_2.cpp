// memory_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
// new 细节探秘 重载类内operator new、delete


#include "pch.h"
#include <iostream>

int main()
{
	//一 new内存分配细节探秘
	//我们注意到，一块内存的回收，影响的范围很广，远远不是10字节，而是一大片
	//分配内存这个事儿，绝不是简单的分配出去4个字节，而是在这4个字节周围，编译器做了很多处理，比如分配出去的字节数等等



    std::cout << "Hello World!\n"; 
}



