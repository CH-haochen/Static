#pragma once

class Time
{
public:
	int hour;
	int minute;
	int second = 0;
	int *a;

public:
	//构造函数
	Time();
	Time(int tmphour);
	Time(int tmphour, int tmpminute, int tmpsecond);


	Time& operator=(const Time& myTime); //重载的赋值运算符

	~Time();
};

void writeTime(Time &time);
