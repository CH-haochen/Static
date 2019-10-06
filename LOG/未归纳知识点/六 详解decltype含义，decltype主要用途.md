# 六 详解decltype含义，decltype主要用途

## 一 decltype含义和举例: 用于推导类型

decltype: 对于一个给定的变量名或者表达式，decltype能够告诉你该名字或者表达式的类型

auto a = 10; //我们并不想用表达式的值初始化这个变量

decltype:
（1）decltype的自动类型推断会发生在编译器
（2）decltype不会真正计算表达式的值

### 1.1 decltype后的圆括号中是个变量

```c++
const int i = 0;
const int &iy = i;
auto j1 = i; //j1=int;
decltype(i) j2 = 15; //j2 = const int.
decltype(iy) j3 = j2; //j3 = const int &
```

```c++
class CT
{
public:
	int i;
	int j;
};

decltype(CT::i) a; //a = int
CT tmpct;
decltype(tmpct) tmpct2; //tmpct2 = CT 

```

### 1.2 decltype后的圆括号中非变量(是表达式)

decltype会返回表达式的结果对应的类型

```c++
decltype(8) kkk = 5; //kkk=int
int i = 0;
int *pi = &i;
int &iy = i;
decltype(iy + 1) j; //j = int 
decltype(pi) k; //k = int *
decltype(*pi) k2 = i; //k2 = int &
//decltype后边是个非变量的表达式，并且表达式可以作为等号左边内容，返回的就是类似int &的左值引用

decltype((i)) iy3 = i; //如果在变量名额外增加了一层或者多层括号(),那么编译器就会把这个变量当成一个表达式
					//又因为 变量(表达式)可以作为等号左边的内容，最终iy3 = int &

//结论： decltype((变量))的结果永远是个引用
```

### 1.3 decltype后的圆括号中是函数

```c++
int testf()
{
	return 10;
}

decltype(testf()) tmpv = 14; //tmpv的类型就是函数testf()的返回类型 int
decltype(testf) tmpv2; //tmpv2 = int(void), 这个有返回类型，有参数类型，代表一种可调用对象

std::function<decltype(testf)> ftmp = testf;
//它所代表的可调用对象是一个int(void)
```

## 二 decltype主要用途

### 2.1 应付可变类型，一般decltype主要用途还是应用在模版编程中

```c++
template<typename T>
class CT
{
public:
	//typename T::iterator iter; //迭代器类型
	decltype(T().begin()) iter;
	void getbegin(T& tmpc)
	{
		iter = tmpc.begin();
	}
};

using contype = const std::vector<int>;
contype myarr = { 10,30,50 };
CT<contype> ct;
ct.getbegin(myarr);
```

### 2.2 通过变量表达式抽取变量类型

```c++
std::vector<int> ac;
ac.push_back(1);
ac.push_back(2);
std::vector<int>::size_type mysize = ac.size();
decltype(ac)::size_type mysize2 = mysize; //抽取ac的类型 std::vector<int>
```

### 2.3 auto结合decltype构成返回类型后置语法

```c++
auto func(int a, int b) ->int { ... };
```



```c++
auto add(int i, int j)->decltype(i + j)
{
	return i + j;
}

int &tf(int &i)
{
	return i;
}

double tf(double &i)
{
	return i;
}

template <typename T>
auto FuncTmp(T &tv)->decltype(tf(tv))  //auto在这里没有自动类型推断的含义，这里它只是返回类型后置语法的组成部分
{
	return tf(tv);
}

int i = 19;
std::cout << FuncTmp(i) << std::endl; //19
double d = 29.1f;
std::cout << FuncTmp(d) << std::endl; //29.1
```

