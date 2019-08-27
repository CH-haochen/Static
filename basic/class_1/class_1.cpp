// class_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 构造函数详解

#include "pch.h"
#include <iostream>
#include "Time.h"

int main()
{
	/*Time myTime;
	myTime.initTime(11, 14, 5);*/

	//一 构造函数
	//（1）构造函数没有返回值。
	//（2）不可以手动调用构造函数，否则编译就会出错
	//（3）正常清空下，构造函数应该被声明为public。因为系统会自动调用，如果private，肯定创建不了对象了
	//（4）如果构造函数里有多个参数，那么创建对象的时候也要带上这些参数
	Time myTime = Time(12, 13, 52);

	//二 多个构造函数

	//三 函数默认参数
	//规定：
	//（1）默认值只能放在函数声明中，除非改函数没有函数声明
	//（2）在具有多个参数的函数中指定默认值事，默认参数都必须出现在非默认参数的右边，一旦摸个参数开始指定默认值，它右边的所有参数必须指定默认值
	//Time(int tmphour, int tmpminute, int tmpsecond = 12);

	//四 隐式转换和explicit
	//
	//Time myTime40 = 14;
	//
	Time myTime100 = { 16 };  //因为存在只带一个参数的构造函数，所以这种方式是可以的
	Time myTime101 = 16; 

	//如果构造函数声明中带有explicit，则这个构造函数只能用于初始化和显示类型转换
	//explicit Time(int tmphour);
	Time myTime100 = { 16 };  //不允许
	Time myTime101 = 16;
	//对于单参数的构造函数，一般都声明为explicit，除非你有特殊原因
	
	//五 构造函数初始化列表
	//（1）专业，高大上
	//（2）
    std::cout << "Hello World!\n"; 
}

