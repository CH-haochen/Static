// basic_9.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// static_cast


#include "pch.h"
#include <iostream>

int main()
{
	//一 隐式类型准换：系统自动进行，不需要程序开发人员介入
	int m = 3 + 45.6;  //48.600000000，把小数部分截掉，也属于隐式转换
	double n = 3 + 45.6;

	//二 显示类型转换（强制类型转换）
	//int k = 5 % 3.2; //语法错
	int k = 5 % (int)3.2; //OK,c语言风格的强制类型转换
	int k = 5 % int(3.2); //函数风格的强制转换（c语言风格）
	
	//c++强制类型转换为4种
	//这四种强制类型转换，分别用于不同的目的，每一个都有一个不同的名字
	//目的：提供更丰富的含义和功能，方便维护检查
	//（a）static_cast
	//（b）dynamic_cast
	//（c）const_cast
	//（d）reinterpret_cast
	//这四个强制类型转换都被称呼为“命名的强制类型转换”
	//通用形式
	//强制类型转换名<type>(express)
	//强制类型转换名，是上边的abcd四个名字之一
	//type:转换的目标类型
	//express：你要转换的值(要转换的是谁)
	//2.1 static_cast: 静态转换，大家就理解为“正常转换”，编译的时候就会进行类型转换的检查
					// 代码中要保证转换的安全性和正确性，static_cast含义跟c语言中的强制类型转换这种感觉差不多
					// c风格的强制类型转换，以及编译器能够进行的隐式类型转换，都可以用static_cast类显示完成
	//可用于
	//（a）相关类型转换，比如整型和实型之间的转换
	double f = 100.34f;
	int i = (int)f; //c风格
	int i2 = static_cast<int>(f); //c++风格
	
	//（b）子类转成父类类型（继承关系），也能用这个static_cast
	class A {};
	class B : public A {};
	B b;
	A a = static_cast<A>(b); //把子类转成父类对象

	//（c）void * 与其他类型指针之间的转换，void*:无类型指针：可以指向任何指针类型（万能指针）
	int i = 10;
	int *p = &i;
	void *q = static_cast<void *>(p);  //int * 转void*
	int *db = static_cast<int *>(q);

	//不可用于：
	//一般不能用于指针类型之间的转换，比如int *转double *,float *转double* 等等

	//2.2 dynamic_cast:主要应用于 运行时类型识别和检查。
	//		主要用于父类型和子类型之间转换用的（父类型指针指向子类型对象，然后用dynamic_cast把父类型指针忘子类型转）
	//		第三章第十节细讲

	//2.3 const_cast: 去除指针或者引用的const属性。改转换能够将const性质转换掉
	//			编译时就会进行类型转换
	//const int ai = 90;
	////int ai2 = const_cast<int>(ai); //ai不是指针也不是引用，不能转
	//const int *pai = &ai;
	//int *pai2 = const_cast<int *>(pai); //语法正确
	//*pai2 = 123; //这种写值行为，是属于一种未定义行为，大家不要这么干
	//std::cout << ai << std::endl;
	//std::cout << *pai << std::endl;

	////c语言风格
	//const int ai = 90;
	//int *pai = (int *)&ai;
	//*pai = 120; //未定义行为

	//2.4 reinterpret_cast:编译的时候就会进行类型转换的检查
	//reinterpret: 重新解释。（将操作数内容解释为另一种不同的类型【能把操作数的类型都转了】）
	//处理无关类型的转换。也就是两个转换类型之间没有什么关系。就等于可以乱转，自由转。怎么转都行，很随意
	//常用语如下两种转换：
	//（a）将一个整型（地址）转换成指针，一种类型指针转换成另一种类型指针，按照转换后的内容重新解释内存中的内容
	//（b）也可以从一个指针类型转换成一个整型
	int i = 10;
	int *pi = &i;
	int *p2 = reinterpret_cast<int *>(&i);
	char *pc = reinterpret_cast<char *>(pi);

	int i = 10;
	int *pi = &i;
	void *pvoid = reinterpret_cast<void *>(pi);
	int *pi2 = reinterpret_cast<int *>(pvoid);

	//被认为是危险的类型转换，随便转，怎么搞都行，编译器都不报错
	int iv1 = 100;
	long long lv1 = 8898899400; //8字节的。 十六进制： 2 126A 6DC8
	int *piv1 = (int *)iv1; // c语言风格； 0x00000064
	int *piv2 = reinterpret_cast<int *>(iv1); // 0x00000064
	piv2 = reinterpret_cast<int *>(lv1); //0x126a6dc8  把前面的2丢了，因为piv2是4字节
	long long ne = reinterpret_cast<long long>(piv2); //指针类型转整型

	//总结：
	//（1）强制类型转换，不建议使用。强制类型转换能够抑制编译器报错
	//（2）认识就行，方便读别人代码
	//（3）资料说：reinterpret_cast危险，使用const_cast意味着设计缺陷
	//（4）如果要用类型转换，就不要再使用c语言风格的类型转换了，要用c++风格
	//（5）一般static_cast和reinterpret_cast就能够很好的取代c语言类型转换了



    std::cout << "Hello World!\n"; 
}
