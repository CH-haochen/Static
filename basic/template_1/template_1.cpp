// template_1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 模板概念，函数模板定义，调用

#include <iostream>

//int funcadd(int a, int b)
//{
//	int result = a + b;
//	return result;
//}
//
//double funcadd(double a, double b)
//{
//	double result = a + b;
//	return result;
//}

template<typename T>
T funcadd(T a, T b)
{
	T result = a + b;
	return result;
}

template<int a, int b>
int funcadd2()
{
	return a + b;
}

template<typename T, int a, int b>
int funcadd3(T c)
{
	int addhe = (int)c + a + b;
	return addhe;
}

template<unsigned L1, unsigned L2>  //本例中仍旧没有类型参数，只有非类型参数
inline //模板函数可以是inline的
int charscomp(const char(&p1)[L1], const char(&p2)[L2])
{
	return strcmp(p1, p2);
}

int main()
{

	//一 概述
	//vector vector<int>
	//（1）所谓泛型编程 是以独立于任何特定类型的方式编写代码。使用泛型编程时，我们需要提供具体程序实例所操作的类习惯或者值
	//（2）模版是泛型编程的基础。模版是创建类或者函数的蓝图或者公式。我们给这些蓝图或者公式提供足够的信息，让这些蓝图或者公式真正的转变具体的类或者函数，这种转变发生在编译时
	//（3）模版支持 将 类型作为参数的程序设计方式，从而实现了对泛型程序的直接支持。也就是说，c++模版机制运行在定义类、函数时将类型作为参数

	//模板一般分为函数模板和类模板，本节主要是函数模板

	//二 函数模板的定义
	//（1）模版定义使用template关键字开头的，后边跟<>，<>里面叫 模版参数列表（模版实参），如果模板参数列表里有多个参数，则用逗号分开
	//<>里必须至少得有一个模板参数，模板参数前面有个typename/class（不是用来定义的）关键字
	//如果模板参数列表里面有多个模板参数，那就要用多个typename/class：<typename T, typename Q>
	//（2）模板参数列表里面表示在函数定义中用到的“类型”或者“值”，也和函数参数列表类似
	//那我们用的时候，有的时候得指定 模版实参 给它，指定的时候我们要用<>把模板实参包起来。有的时候，又不需要我们指定模版实参给它
	//系统自己能够根据一些信息推断出来，后续会举例
	//（3）funcadd这个函数声明了一个名字为T的类型参数。这里注意，T实际是类型，这个T到底代表说啥类型，编译器会在编译的时候根据针对funcadd的调用决定


	//三 函数模版的使用
	//函数模板调用和函数调用区别不大，调用的时候，编译器会根据你调用这个函数模板时的实参去推断模板参数列表里的参数（形参）的类型
	//注意措辞：模板参数，有时候是推断出来的。是根据你调用这个函数的时候函数的实参来推断的
	//当然有的时候，光凭借函数实参是推断不出来模版参数，我们需要用<>来主动提供模版参数了

	//template<typename T>
	//T funcadd(T a, T b)
	int he = funcadd(1, 3); //3，1系统认为是int，所以编译器能推断出来模板的形参是int
	double he2 = funcadd(1.1f, 3.1f);
	std::cout << he2 << std::endl;


	//四 非类型模板参数
	//因为T前面有一个typename/class，这表示T代表一个类型，是一个类型参数
	//那么在模板参数列表里边，还可以定义非类型参数，非类型参数代表的是一个值
	//既然非类型参数代表一个值，那么我们肯定不能用typename/class这种关键字来修饰这个值
	//我们当然要用以往学习过的传统类型名来指定非类型参数了。如果如果非类型参数S如果是个整型，int S

	//template<typename T, int S>
	//T funcadd(T a, T b)
	//当模板被实例化时，这种非类型模板参数的值，或者是用户提供的，或者是编译器推断的，都有可能
		//但是，这些值必须都得是常量表达式，因为实例化这些模板是编译器在编译的时候来实例化的
	
	int result = funcadd2<12, 13>();  //显示的指定模板参数--在尖括号中提供额外的信息
	std::cout << result << std::endl;

	int a = 12;
	int result = funcadd2<a, 13>(); //这不可以。非类型模板参数 值必须是在编译时就能确定的

	/*template<typename T, int a, int b>
	int funcadd3()*/
	int result = funcadd3<int, 11, 12>(13);
	int result2 = funcadd3<double, 11, 12>(13); //系统会 以我们用<>传递进去的类型(double)为准，而不是用13来推断什么类型


	int result3 = charscomp("test2", "test"); //没有提供非类型模板参数，系统会根据test2的长度6个，test长度是5个，(末尾\0) 取代L1,L2
   
	//结论:
	//模板定义并不会导致编译器生成代码，只要在我们调用这个函数模板时，编译器为我们实例化了一个特定版本的函数后，编译器才会生成代码
	//编译器生成代码的时候，需要能够找到函数的函数体，所以，函数模板的定义通常都是在.h文件中
	
	
	std::cout << "Hello World!\n"; 
}


