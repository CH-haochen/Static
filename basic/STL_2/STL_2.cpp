// STL_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//容器分类 array vector

#include "pch.h"
#include <iostream>
#include <array>
#include <string>
#include <vector>

int main()
{
	//stl组成部分：容器，迭代器，算法，分配器，其他
	//一 容器的分类
	//STL中的容器分为三大类
	//（1）顺序容器: 放进去在哪里，这个元素就排在哪里。 比如array,vector,dqueue, list ,forward_list
	//（2）关联容器：树，哈希表，元素是 键/值 对，特别适合做查找。你能控制插入的内容，但一般不能控制插入的位置。map,set
	//（3）无序容器：c++11里推出，元素的位置不重要，重要的是这个元素是否在这个容器里面。也属于一种关联容器，哈希表来实现
	// unordered_set,unordered_map...

	//二 容器的说明和应用事项例
	//2.1 array 是个顺序容器，其实是个数组，内存空间连续，大小是固定的
	std::array<std::string, 5> mystring = { "I","LOVE", "China" };
	std::cout << "size= " << mystring.size() << std::endl; //5
	mystring[0] = "123";
	mystring[3] = "678";

	//2.2 vector
	//（a）往屁股后边增加元素和从屁股删除元素都很快
	//（b）往中间插入元素可能导致很多后续的元素要执行重新构造，析构。效率会非常低
	//（c）查找速度应该不会太快

	//vector容器内存也是挨着的，vector容器有一个“空间”的概念，每一个空间可以装一个元素
	//容器里有多少个元素可以用size()来看，而这个容器里有多少个空间，可以用capacity()
	//capacity()一定不会小于size(),vector容器中空间的数量一定不会小于元素的数量
	
	//用reverse可以预留空间，前提是你预先知道这个容器最多会容纳多少个元素

	std::vector<A> myveca;
	myveca.reserve(10); //预留10个空间

	
	






    std::cout << "Hello World!\n"; 
}


