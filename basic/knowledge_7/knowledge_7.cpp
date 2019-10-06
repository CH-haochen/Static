// knowledge_7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 可调用对象

#include "pch.h"
#include <iostream>
#include <functional>

void myfunc(int tv)
{
	std::cout << "myfunc(int tv)函数执行了" << std::endl;
}

class TC
{
public:
	void operator()(int tv)
	{
		std::cout << "operator()(int tv)函数执行了, tv=" << tv << std::endl;
	}

	void ptfunc(int tv)
	{
		std::cout << "ptfunc(int tv)函数执行了, tv=" << tv << std::endl;
	}

	static int stcfunc(int tv)
	{
		std::cout << "stcfunc(int tv)函数执行了, tv=" << tv << std::endl;
		return tv;
	}

};

class TC2
{
public:
	using tfpoint = void(*)(int); //定义一个函数指针类型
	static void mysfunc(int tv) //静态成员函数
	{
		std::cout << "mysfunc(int tv)静态成员函数执行了, tv=" << tv << std::endl;
	}
	operator tfpoint() { return mysfunc; }
};

class CB
{
	std::function<void()> fcallback;
public:
	CB(const std::function<void()> &f) : fcallback(f)
	{
		int i;
		i = 1;
	}
	void runcallback(void)
	{
		fcallback();
	}

};

class CT
{
public:
	void operator()()
	{
		std::cout << "operator" << std::endl;
	}
};


void mycallback(int cs, const std::function<void(int)> &f)
{
	f(cs);
}

void runfunc(int x)
{
	std::cout << x << std::endl;
}


void myfunc1(int x, int y, int z)
{
	std::cout << x << y << z << std::endl;
}

void myfunc2(int &x, int &y)
{
	x++;
	y++;
}

class CT
{
public:
	void myfunpt(int x, int y)
	{
		std::cout << x << y << std::endl;
		m_a = x;
	}
	int m_a = 0;

public:
	void operator()()
	{
		
	}
};


int main()
{
	//一 可调用对象
	//1 函数 2 重载了()运算符的类的对象
	//1.1 函数指针
	void(*pmf)(int) = &myfunc; //定义一个函数指针pmf并给了初值
	pmf(15); //调用函数，这就是个可调用对象

	//1.2 具有operator()成员函数的类的对象(仿函数)
	// 仿函数的定义：仿函数（functor）,它的行为类似于函数的东西（something that performs a function）
	// c++仿函数是通过在类中重载()运算符实现。又称函数对象(function object):能行使函数功能的类
	TC tc;
	tc(15); //调用的是()操作符，这也是个可调用对象，等价于tc.operator()(20)

	//1.3 可被转换为函数指针的类对象（仿函数/函数对象）
	TC2 tc2;
	tc2(50); //先调用tfpoint, 再调用mysfunc:这也是个可调用对象。等价于tc2.operator TC2::tfpoint()(50);
	
	//1.4 类成员函数指针
	TC tc;
	void (TC::*myfpointpt)(int) = &TC::ptfunc; //类成员函数指针变量myfpointpt定义并给初值
	(tc.*myfpointpt)(68);

	//1.5 总结
	//（a）看成对象
	//（b）我们可以对其使用()调用运算符，如果a是可调用对象，那么我们就可以编写a(param...)代码
	//


	//二 std::function （可调用函数包装器）
	//std::function是个类模板，用来装各种可调用对象，不能装类成员函数指针
	//特点：就是能够通过给它指定模板参数，它就能够用统一的方式来处理函数
	//2.1 绑定普通函数
	std::function<void(int)> f1 = myfunc;
	f1(100);

	//2.2 绑定类的静态成员函数
	std::function<int(int)> fs2 = TC::stcfunc; 
	std::cout << fs2(10) << std::endl;

	//2.3 绑定仿函数
	TC tc3;
	std::function<void(int)> f3 = tc3;

	//2.4 小范例演示
	CT ct; //可调用对象
	CB cb(ct); //cb需要可调用对象做参数来构造
	cb.runcallback();

	for (int i = 0; i < 10; i++)
	{
		mycallback(i, runfunc); //runfunc(i)
	}


	//三 std::bind绑定器
	//能够将对象以及相关的参数绑定到一起，绑定完后可以直接调用，也可以用std::function进行保存，在需要的时候调用
	//格式：
	//std::bind(待绑定的函数对象/函数指针/成员函数指针，参数绑定值1，参数绑定值2....)
	
	//总结：
	//（a）将可调用对象和参数绑定到一起，构成一个仿函数,所以可以直接调用
	//（b）如果函数有多个参数，可以绑定一部分参数，其他参数在调用的时候指定
	auto bf1 = std::bind(myfunc1, 10, 20, 30);
	bf1(); //执行myfunc1函数

	//表示绑定myfunc1的第三个参数为30，myfunc1的第一个参数和第二个参数分别由调用bf2时的第一，第二个参数指定
	//std::placeholders::_1, 占位符
	auto bf2 = std::bind(myfunc1, std::placeholders::_1, std::placeholders::_2, 30);
	bf2(10, 20); //执行myfunc1函数 10 20 30
	auto bf2 = std::bind(myfunc1, std::placeholders::_1, std::placeholders::_1, 30);
	bf2(10, 20); //执行myfunc1函数 10 10 30
	auto bf2 = std::bind(myfunc1, std::placeholders::_2, std::placeholders::_1, 30);
	bf2(10, 20); //执行myfunc1函数 20 10 30


	int a = 2;
	int b = 3;
	auto bf3 = std::bind(myfunc2, a, std::placeholders::_1);
	bf3(b); 
	std::cout << a << b << std::endl;  //a=2, b=4
								//这说明：bind对于预先绑定的函数参数是通过值传递的，所以这个a实际上是值传递
								//bind对于不事先绑定的参数，通过std::placeholder传递的参数，是通过引用传递的




	CT ct; 
	auto bf5 = std::bind(&CT::myfunpt, ct, std::placeholders::_1, std::placeholders::_2);
	bf5(10, 20); //上行第二个参数ct，会导致调用CT的拷贝构造函数来生成了一个CT类型的临时对象，作为std::bind返回值（bind返回仿函数类型对象）
					//后续的myfuncpt调用修改的是这个临时对象的m_a值，并不影响真实的ct对象m_a值
			

	auto bf5 = std::bind(&CT::myfunpt, &ct, std::placeholders::_1, std::placeholders::_2);
	bf5(10, 20); //上行第二个参数ct前面如果加了&, 就不生成临时的CT对象了，后续myfuncpt调用修改的就是ct对象m_a了
				//这说明此时bind返回的对象就是ct本身


	//bind和function的配合使用
	CT ct;
	std::function<void(int, int)> bfc6 = std::bind(&CT::myfunpt, ct, std::placeholders::_1, std::placeholders::_2);
	bfc6(10, 20);

	//把成员变量地址当函数一样绑定，绑定的结果放在std::function<int &(void)>里保存
	std::function<int &()> bf7 = std::bind(&CT::m_a, &ct);
	bf7() = 60;

	//四 总结
	//（a）bind思想 所谓的延迟调用，将可调用对象统一格式，保存起来，需要的时候再调用
	//（b）std::function绑定可调用对象，但类成员函数不能绑
	std::cout << "Hello World!\n"; 
}
