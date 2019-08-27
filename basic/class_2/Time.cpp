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
	testValue = tmphour;
}

Time& Time::add_hour(int tmphour)
{
	hour += tmphour;
	this->hour;
	return *this; //把对象自己给返回去了
}

Time& Time::add_minute(int minute)
{
	this->minute += minute;
	return *this; //把对象自己给返回去了
}

//静态成员函数实现
void Time::mstaticfun(int testvalue)
{
	//hour = testValue; //错误，因为hour成员变量是和对象相关的成员变量
	mystatic = 17; //可以，因为mystatic是和类相关的
}