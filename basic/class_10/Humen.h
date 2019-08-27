#ifndef __HUMEN__
#define __HUMEN__

class Humen
{
public:
	Humen() {}

public:
	//拷贝构造函数
	Humen(const Humen &tmphumen) //tmphumen得到了man对象的引用，但是，humen作为基类，它只能处理基类自己的成员，无法处理派生类的成员
	{
		//
	}

	//赋值运算符
	Humen & operator=(const Humen &tmphumen)
	{
		//...
		return *this;
	}
};


#endif // 

