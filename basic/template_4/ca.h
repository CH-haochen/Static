#pragma once
template<typename C> //类的模板参数C
class A
{
public:
	template<typename T2>
	//A(T2 v1, T2 v2)  //构造函数我们也引入自己的模板，和整个类的模板C没有关系
	//{
	//
	//}
	A(T2 v1, T2 v2);
	template<typename T>
	void myft(T tmpt) //成员函数模板
	{
		std::cout << tmpt << std::endl;
	}

	void myftpt();

	C m_ic;
};


template<typename C> //先跟类的模板参数列表
template<typename T2> //再跟构造函数自己的模板参数列表
A<C>::A(T2 v1, T2 v2)
{
	std::cout << v1 << v2 << std::endl;
}