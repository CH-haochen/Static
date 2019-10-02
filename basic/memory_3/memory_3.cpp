// memory_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 内存池

#include "pch.h"
#include <iostream>

class A
{
public:
	static void *operator_new(size_t size);
	static void operator_delete(void *phead);
	static int m_iCount; //分配计数统计，每new一次，就统计一次
	static int m_iMallocCount; //每malloc一次，就统计一次

private:
	A *next;
	static A* m_FreePosi; //总是指向一块可以分配出去的内存的首地址
	static int m_sTrunkCount; //一次分配多少倍的该类内存

};

int main()
{
	//一 内存池的概念和实现原理概述
	//malloc: 内存浪费，频繁分配小块内存，则浪费更加显得明显
	//“内存池”要解决什么问题？
	//（a）减少malloc的次数，减少malloc()调用次数就意味着减少对内存的浪费
	//（b）减少malloc的调用次数，会有一些速度和效率上的提升，但提升并不明显

	//“内存池的实现原理”：
	//（a）用malloc申请一大块内存，当你要分配的时候，我从这一大块内存中一点一点的分配给你，当一大块内存分配的差不多的时候，
	//		我再用malloc再申请一大块内存，然后再一点一点的分配给你

	//减少内存浪费，提高运行效率

	//二 针对一个类的内存池 实现演示代码
	




    std::cout << "Hello World!\n"; 
}


