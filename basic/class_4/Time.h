#pragma once

class Time
{
public:
	int hour;
	int minute;
	int second = 0;

	const int ctestvalue = 80; //定义了一个常量
	//const int ctestvalue;


	mutable int testValue;
	void initTime(int tmphour, int tmpminute, int tmpsecond);

public:
	//构造函数
	Time();
	Time(int tmphour);
	Time(int tmphour, int tmpminute, int tmpsecond);

public:
	/*void addhour(int tmphour)
	{
		hour = tmphour;
	}*/

	void addhour(int tmphour) const;

public:
	//把对象自己给返回去
	Time& add_hour(int tmphour);
	Time& add_minute(int minute);

	//static int mystatic; // 声明静态成员变量，还没有分配内存，也不能在这里初始化
	static void mstaticfun(int testvalue);

	//拷贝构造函数
	Time(const Time &tmptime, int a = 56);

};

void writeTime(Time &time);
