#include "Time.h"
#include <iostream>



//普通函数，不是成员函数
void writeTime(Time &time)
{
	std::cout << time.hour << std::endl;
}


//构造函数的实现
//Time::Time(int tmphour, int tmpminute, int tmpsecond)
//{
//	hour = tmphour;
//	minute = tmpminute;
//	second = tmpsecond;
//}

//构造函数初始化列表
Time::Time(int tmphour, int tmpminute, int tmpsecond):hour(tmphour), minute(tmpminute),second(tmpsecond) 
{
	
}

Time::Time(int tmpctestvalue)
{
}

//Time::Time(int tmphour)
//{
//
//}


Time::Time()
{
	int *a = new int[100];
}


Time& Time::operator=(const Time &myTime)
{
	hour = myTime.hour;
	minute = myTime.minute;
	second = myTime.second;
	return *this; //返回了自身对象
}

Time::~Time()
{
	delete [] a;
	std::cout << "调用了析构函数" << std::endl;
}