#pragma once
#pragma once

class Time2
{
public:
	int hour;
	int minute;
	int second = 0;

public:
	//构造函数
	Time2(); //不带参数的构造函数，默认构造函数
	//Time2() = default; //编译器能够为这种 =default创建函数体
	//Time2() = delete; //让程序员显示的禁用某个函数
	//int ptfunc() = default; //非特殊函数，不可以使用 =default
	Time2(int tmphour); //带参数的构造函数，不可以使用 =default

};

