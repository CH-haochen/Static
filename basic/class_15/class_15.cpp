// class_15.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 类型转换构造函数、运算符、类成员指针

#include "pch.h"
#include <iostream>


class TestInt //保存0-100之间的一个数字
{
public:
	//定义一个函数指针类型，代表的函数带一个int形参，没有返回类型的
	//typedef void(*tfpoint)(int);
	using tfpoint = void(*)(int);

public:
	static void mysfunc(int v1)
	{
		int test;
		test = 1;
	}

	//新的类型转换运算符， 能将 本类类型对象 转换成一个函数指针类型
	operator tfpoint() //const不是必须加的，所以这里不加
	{
		//必须要返回一个函数指针
		return mysfunc; //函数地址（函数名）作为函数指针类型返回即可
	}

public:
	TestInt(int x = 0) :m_i(x)
	// explicit：禁止做隐式类型转换
	//explicit TestInt(int x = 0) :m_i(x) //类型转换构造函数[也是一个只带一个参数的普通构造函数]
	{
		if (m_i < 0) m_i = 0;
		if (m_i > 100) m_i = 100;
	}

	//类型转换运算符，可以把本类类型对象转换成其他类型
	operator int() const
	//explicit operator int() const //禁止隐式类型转换
	{
		return m_i;
	}

public:
	int m_i;
};

class CT1
{
public:
	CT1(int ct) {}; //类型转换构造函数
};

class CT2
{
public:
	CT2(int ct) {}; //类型转换构造函数
};

void testfunc(const CT1 &C) {}
void testfunc(const CT2 &C) {}


class CT
{
public:
	void ptfunc(int tmpvalue) { std::cout << "ptfunc普通成员函数被调用,value=" << tmpvalue << std::endl; }
	virtual void vituralfunc(int tmpvalue) { std::cout << "virtual虚成员函数被调用,value=" << tmpvalue << std::endl; }
	static void statictfunc(int tmpvalue) { std::cout << "static静态成员函数被调用,value=" << tmpvalue << std::endl; }

	int m_a; //普通成员变量 属于对象
	static int m_stca; //声明，静态成员变量，属于类
};

int CT::m_stca = 1; //静态成员变量的定义

int main()
{


	//我们需要通过 转换构造函数 和 类型转换运算符 来做到 类型转换
	//一 类型转换构造函数， 比如， 他们能够把一个数字 转换成 一个 类对象
	//构造函数；
	//（1）以类名为函数名
	//（2）没有返回值
	//有一种构造函数，叫“类型转换构造函数”，主要能力是：它可以将某个其他的数据类型转换成该类类型的对象
	//类型转换构造函数的特点：
	//（a）只有一个参数，该参数又不是本类的const引用，该参数其实就是待转换的数据类型。所以待转换的数据类型，都不应该是本类类型
	//（b）在类型转换构造函数中，我们要指定转换的方法（在这个函数中要干什么）

	//TestInt ti = 12;  //隐式类型转换，将数字12转换成了TestInt对象（调用了类型转换构造函数）
	//					//编译器用12这个数字通过调用TestInt的类型构造函数来创建一个临时的TestInt对象，并把这个对象构造到ti这个预留空间里去
	//TestInt ti2(22);   //调用了类型转换构造函数，但这里没有进行隐式类型转换，只是调用了一个参数的构造函数


	//二 类型转换运算符（类型转换函数）能力和类型转换构造函数能力相反
	// 是特殊的成员函数，它能够将一个类类型对象 转成 某个其他数据类型
	//格式
	//operator type() const;
	//（a）const是可选项，const表示一般不应该改变待转换对象内容，但不是必须有const
	//（b）type: 表示要转换成的某种类型。只要是能够作为函数返回的类型，都可以；数组指针，函数指针，引用等等类型也都可以
	//（c）类型转换运算符，没有形参（形参列表为空），因为类型转换运算符都是隐式执行的，所以根本也没有办法给它传递参数。
	//		同时，也不能指定返回类型，但是，它却能返回一个type指定的类型的值的
	//（d）必须定义为类的成员函数

	TestInt ti = 12;
	TestInt ti2;
	ti2 = 6; //编译器用6生成临时的TestInt对象（调用TestInt类型转换构造函数），又调用赋值运算符把临时对象的内容给了ti2；
	
	//int k = ti2 + 5; //11  调用operator int() const将ti2转换成了int，再和5做加法晕死，结果给k
						//ti2转int 是隐式类型转换
	int k = static_cast<int>(ti2) + 5; //显式调用。
	int k2 = ti2.operator int() + 5; //显式调用。

	//2.1 显示的类型转换运算符 explicit
	int k = static_cast<int>(ti2) + 5; //显式调用。
	int k2 = ti2.operator int() + 5; //显式调用。

	//2.2 有趣范例，类对象转换为函数指针
	TestInt myi(12);
	myi(123); //看起来是个可调用对象的感觉。相当于调用了两个函数
				//（1）类型转换运算符[转换成函数指针类型] （2）通过函数指针调用具体的参数
	(myi.operator TestInt::tfpoint())(123);


	//三 类型转换的二义性问题
	TestInt aa;
	int abc = aa + 12; //二义性
	//建议 在一个类中，尽量只出现一个类型转换运算符

	//testfunc(101); //二义性，因为101是个int类型，可以转换成CT1对象，也可以转换成CT2对象

	//四 类成员函数指针
	//是个指针，指向类成员函数
	//4.1 对于普通成员函数 的函数指针
	//格式：  类名::*函数指针变量名  来声明普通成员函数指针
	//		 &类名::成员函数名      来获取类成员函数地址   “这个是真正的内存地址”
	void (CT::*myfpointpt)(int);   //一个类成员函数指针变量的定义，变量名字为myfpointpt
	myfpointpt = &CT::ptfunc;	   //类成员函数指针变量myfpointpt被赋值
	//注意：成员函数是属于类的，不属于类对象，只要有类在就有成员函数地址在
	//但是，你若要使用这个成员函数指针，就必须要把他绑定到一个类对象上才能调用
	//使用函数指针的格式：  “类对象名.*函数指针变量名”来调用,如果是个对象指针，则调用格式“指针名->*函数指针变量名”来调用
	CT ct, *pct;
	pct = &ct;
	(ct.*myfpointpt)(100);  //对象ct，调用指针变量myfpointpt所指向的成员函数：ptfunc
	(pct->*myfpointpt)(100); //ptc所指的对象，调用指针变量myfpointpt所指向的成员函数：ptfunc


	//4.2 对于虚函数
	void (CT::*myfpointvirtual)(int) = &CT::vituralfunc; //“这个是真正的内存地址”
	//也必须要绑定到类对象上才能调用
	(ct.*myfpointvirtual)(100);  //对象ct，调用指针变量myfpointvirtual所指向的成员函数：vituralfunc
	(pct->*myfpointvirtual)(200); //ptc所指的对象，调用指针变量myfpointvirtual所指向的成员函数：vituralfunc

	//4.3 对于静态成员函数
	//使用 “*函数指针变量名”来声明静态成员函数指针，使用“&类名::成员函数名”来获取类成员函数地址。这个也是真正的地址
	//定义一个静态的类成员函数指针并赋值
	void(*myfpointstatic)(int) = &CT::statictfunc;
	myfpointstatic(100);

	//五 类成员变量指针
	//5.1 对于普通成员变量
	int CT::*mp = &CT::m_a;  //定义一个类成员变量指针，大家这里注意这种写法
							//0x00000004，并不是真正意义上的指针
							//它不是指向内存中某个地址，而是该成员变量，与该类对象指针之间的偏移量
	CT ctestmp; //当生成类对象时，如果这个类中有虚函数表，则对象中，就会有一个指向这个虚函数表的指针，这个指针占有4个字节
	ctestmp.*mp = 190; //通过类成员变量指针来修改成员变量值，等价于ct.ma=190;

	//5.2 对于静态成员变量
	//这种指向静态成员变量的指针，是有真正的内存地址的
	int *stcp = &CT::m_stca; //定义一个静态成员变量指针
	*stcp = 798; //等价于CT::m_stca = 798
    std::cout << "Hello World!\n"; 
}
