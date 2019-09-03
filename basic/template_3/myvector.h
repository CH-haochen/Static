#pragma once
#ifndef  __MYVECTOR__
#define  __MYVECTOR__

//定义类模版
template<typename T> //名字为T的模版参数，用来表示myvecotr这个容器所保存的元素类型
class myvector
{
public:
	typedef T* myiterator; //迭代器  类型成员

public:
	myvector(); //构造函数
	myvector & operator = (const myvector&); //赋值运算符重载。在类模版内部使用模版名不需要提供模版参数
	//myvector<T> & operator = (const myvector<T>&); //赋值运算符重载。在类模版内部使用模版名不需要提供模版参数

public:
	myiterator mybegin(); //迭代器的起始位置
	myiterator myend(); //迭代器最后一个元素的下一个位置

public:
	void myfunc() {}; //把成员函数的函数体（函数具体实现）放在类模版的定义中
	void myfunc2();
};

//普通函数
template<typename T>
void myvector<T>::myfunc2()
{
	//...
	return;
}


//构造函数
template<typename T>
myvector<T>::myvector()
{
	//...

}

template<typename T>
myvector<T>& myvector<T>::operator=(const myvector&) //<T>表示返回的是一个实例化了的myvector
{
	//...
	return *this;

}


template<typename T>
//typename的必须性
//（a） ::第二个用法，访问类型成员myiterator（typedef）
//  typename这里的目的（用处）就是显式的告诉编译器myiterator是一个类型
typename myvector<T>::myiterator myvector<T>::mybegin()
{
	//......
}

#endif // ! __MYVECTOR__
