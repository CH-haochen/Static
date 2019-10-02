// STL_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <unordered_set>

class A
{

};

int main()
{

	//一 deque和stack 顺序容器
	//deque: 双端队列。相当于动态数组，头部和尾部插入与删除数据都很快；如果往中间插入元素，那么可能会涉及到移动其他元素，效率上会比较低
	//分段连续内存

	//stack（堆栈/栈）：后进先出
	//和vector的区别：vector支持从中间插入中间删除，虽然效率不高
	//stack只支持从栈顶放入元素以及从栈顶取出(删除)元素，这种特性是stack容器设计初衷
	//deque实际上是包含着stack功能


	//二 queue 队列，这是个普通队列：先进先出

	//三 list
	//双向链表，不需要各个元素之间的内存连在一起；查找效率不突出，在任意位置插入和删除元素非常迅速
	//面试中，vector和list的区别
	//（a）vector类似于数组，它的内存空间是连续的，list双向链表，内存空间并不连续（至少不要求内存空间是连续的）
	//（b）vector从中间或者开头插入元素效率比较低，但是list插入元素效率非常高
	//（c）vector当内存不够时，会重新找一块内存，对原来内存对象做析构，在新找的内存中重新构建对象
	//（d）vector能够高效的随机存取，而list做不到这一点，比如要访问第五个元素
	//	vector内存连续，一下就能定位到第五个元素
	//	list 需要沿着一个链一直找下去，直到找到第五个元素。所以说vector随机存取比较快，而list随机存取比较慢

	//四 其他
	//4.1 forward_list 单向链表

	//4.2 set/map  关联容器，内部实现的数据结构多为红黑树
	//我们往这种容器中保存数据时，不需要我们指定数据位置，这种容器会自动的给你加入的元素根据一个算法安排一个位置
	//map: 每个元素有两项，是个键/值对，一般都是通过key找value（查找特别快）
	//通过key找value特别快，不允许key相同，如果非要key相同，要采用multimap
	std::map<int, std::string> mymap;
	mymap.insert(std::make_pair(1, "老李"));
	mymap.insert(std::make_pair(2, "老赵"));
	mymap.insert(std::pair<int, std::string>(3, "老李"));

	auto iter = mymap.find(3);
	if (iter != mymap.end())
	{
		std::cout << iter->second << std::endl;
	}


	//set不存在键值对的说法，每个元素就是一个value，元素值不能重复，如果想重复，可以采用multiset

	//4.3 unordered_set,unordered_multiset,unordered_map,unordered_multimap  
	//（哈希表）增加篮子(桶子)数量的目的就是为了防止某个篮子后边挂的元素太多，从而影响查找速度
	// 自动指定元素位置，不需要使用者手工干预
	std::unordered_set<int> myset;
	//篮子数量
	myset.bucket_count();
	








    std::cout << "Hello World!\n"; 
}


