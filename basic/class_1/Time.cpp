#include "Time.h"

void Time::initTime(int tmphour, int tmpminute, int tmpsecond)
{
	hour = tmphour;
	minute = tmpminute;
	second = tmpsecond;
	
}

//构造函数的实现
Time::Time(int tmphour, int tmpminute, int tmpsecond)
{
	hour = tmphour;
	minute = tmpminute;
	second = tmpsecond;
}

//构造函数初始化列表
Time::Time(int tmphour, int tmpminute, int tmpsecond):hour(tmphour), minute(tmpminute),second(tmpsecond) 
{

}

Time::Time()
{

}

Time::Time(int tmphour)
{

}

void Time::addhour(int tmphour) const
{
	//hour = tmphour;
}