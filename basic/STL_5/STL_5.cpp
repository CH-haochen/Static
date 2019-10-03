// STL_5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//迭代器

#include "pch.h"
#include <iostream>
#include <vector>
#include <list>
#include <stack>

int main()
{
	//一 迭代器基本概念：二章九节
	//迭代器是一个“可遍历STL容器全部或者部分元素”的对象(行为类似于指针的对象)
	//迭代器用来表现容器中的一个位置

	//二 迭代器的分类
	//依据是迭代器的移动特性以及在这个迭代器上能够做的操作

	//（a）输出型迭代器 Ostream, inserter
	struct output_iterator_tag;
	//一步一步能往前走，并且能够通过这个种类的迭代器来改写容器中的数据
	// *iter = val; ++iter; iter++; TYPE(iter)复制迭代器

	//（b）输入型迭代器 Istream
	struct input_iterator_tag;
	//一次一个以向前的方向来读取元素，按照这个顺序一个一个返回元素值
	// *iter = val; iter->member; ++iter; iter++; iter1 == iter2; TYPE(iter)复制迭代器

	//（c）前向迭代器 Forward list, unordered containers
	struct forward_iterator_tag;
	//继承自input_iterator，多了一个iter=iter2; 给迭代器赋值

	//（d）双向迭代器 list, set, multiset, map, multimap
	struct bidirectional_iterator_tag;
	// 在前向迭代器基础上，增加了--iter; iter--;

	//（e）随机访问迭代器 array, vector, deque, string, C-type array
	struct random_access_iterator_tag;
	// 在双向迭代器基础上，增加了随机访问能力
	// iter[n], iter+=n, iter-=n, iter+n, iter-n, iter1-iter2, iter1<iter2, iter1>iter2

	//std::vector<int>::iterator iter = ......
	//std::list<int>::iterator iter = ......

	//大多数容器中都有一个::iterator,但不是所有容器都有， 比如stack，queue

    std::cout << "Hello World!\n"; 
}


