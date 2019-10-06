# 八 lambda表达式，for_each、find_if

## 一 lambda表达式用法简介

也是一种可调用对象

lambda表达式，它定义了一个匿名函数，并且可以捕获一定范围内的变量

```c++
auto f = [](int a)->int { //后置返回类型
    return a + 1;
};

std::cout << f(1) << std::endl;
```

特点：

（a）是个匿名函数，也可以理解为“可调用的代码单元”，或者理解为“未命名的内联函数”

（b）它也有一个返回类型，一个参数列表，一个函数体

（c）与函数不同的是，lambda表达式可以在函数内部定义，这个是常规函数做不到的

格式：

[[捕捉列表]](参数列表)->返回类型｛函数体｝;

（a）这是一个返回类型后置语法(lambda表达式的返回类型后置是必须的，这个语法就这么规定)
	因为很多时候lambda表达式返回值特别明显，所以允许lambda表达式返回类型省略，编译器可以自动推导
	lambda参数可以有默认值 auto f = [](int a =10)

大家要注意，编译器不是总能推断出返回类型，如果不能它就会报错，这个时候就要显示的给后置返回类型了

（b）没有参数的时候，参数列表可以省略，甚至()也能省略，所以如下这些格式都合法

```c++
auto f1 = []() {return 1; };
auto f2 = [] {return 2; };
```

（c）捕获列表[]和函数体{}不能省

（d）lambda调用方法和普通函数相同

（e）lambda表达式可以不返回任何类型，就是void

```c++
auto f3 = [] {};
```

（f）函数体末尾的分号不能省略

## 二 捕获列表： [捕获列表]：通过捕获列表来捕获一定范围内的变量

（a）[] 不捕获任何变量，但不包括静态局部变量。

```c++
int i = 9;
auto f1 = [] {
    return i; //报错(无法捕获外部变量)
};

//lambda可以直接使用局部静态变量
static int j = 9;
auto f1 = [] {
    return j; //报错(无法捕获外部变量)
};
```

（b）[&] 捕获外部作用域中所有变量，并作为引用在函数体内使用

```c++
int i = 9;
auto f1 = [&] {
    i = 5; //因为&的存在，那么就允许给i赋值，从而就改变了i的值
    return i;
};
```

（c）[=]: 捕获外部作用域中所有变量，并作为副本（按值）在函数中使用，也就是可以 用它的值，但不许给它赋值

```c++
int i = 9;
auto f1 = [=] {
    //i = 5; //非法
    return i;
};
```

（d）[this]: 一般用于类中，捕获当前类中的this指针，让lambda表达式有和当前类成员函数同样的访问权限

如果[]中已经使用了 & 或者 =， 那么默认就已经使用了this，说白了，捕获this的目的就是为了在lambda中使用当前类的成员函数和成员变量

```c++
class CT
{
public:
	int m_i = 5;
	void myfunct(int x, int y)
	{
		auto mylambda1 = [this] {
			return m_i; // 因为有了this，这个访问合法的，用&,=也行
		};
		std::cout << mylambda1() << std::endl;
	}

};

CT ct;
ct.myfunct(3, 4);

```

（e）[变量名]  如果是多个变量名，则彼此用,分割。

[变量名]表示按值捕获变量名代表的变量，同时不捕获其他变量

```c++
class CT
{
public:
	int m_i = 5;
	void myfunct(int x, int y)
	{
		auto mylambda1 = [this, x, y] {
			int z = x + y; //此处才能用x,y
			return m_i; // 因为有了this，这个访问合法的，用&,=也行
		};
		std::cout << mylambda1() << std::endl;
	}

};
```

[&变量名]表示按引用捕获变量名代表的变量，同时不捕获其他变量

```c++
class CT
{
public:
	int m_i = 5;
	void myfunct(int x, int y)
	{
		auto mylambda1 = [this, x, y] {
			x = 5;
            y = 10;
			return m_i; // 因为有了this，这个访问合法的，用&,=也行
		};
		std::cout << mylambda1() << std::endl;
	}

};
```

（f）[=, &变量名]

按值捕获所有外部变量，但按引用捕获&中所指的变量，这里这个=必须写在开头位置，开头这个位置表示 默认捕获方式

也就是说，这个捕获列表，第一个位置表示的是默认捕获方式(隐式捕获方式)，后续其他的都是显示捕获方式

（g）[&, 变量名]

 按引用捕获所有外部变量，但按值捕获后面指的变量，这里这个&必须写在开头位置，开头这个位置表示 默认捕获方式

**总结**：lambda表达式对于能访问的外部变量控制的非常细致

## 三 lambda表达式延迟调用易出错细节分析

```c++
int x = 5;
auto f1 = [=] { //当遇到auto这一行，也就是在捕获的这个时刻，x的值就已经被赋值到了这个f中了
    return x;
};
x = 10;
std::cout << f1() << std::endl;  //我们认为是10但实际是5
```

也就是说，凡是按值捕获的外部变量，在lambda表达式定义的这个时刻，所有这些外部变量值就被赋值了一份存储在lambda表达式变量中

解决办法就是按引用来捕获

```c++
int x = 5;
auto f1 = [&] { 
    return x;
};
x = 10;
std::cout << f1() << std::endl;  //10
```

## 四 lambda表达式中的mutable(易变的)

```c++
int x = 5;
//即使是按值捕获，也能修改
auto f = [=] () mutable //注意要加mutable，则()参数列表之外的这个圆括号不能省略
{
    x = 6;
    return x;
};
```

## 五 lambda表达式的类型及存储

c++11中，lambda表达式的类型被称呼为“闭包类型”

闭包：函数内的函数(可调用对象)  本质上就是lambda表达式创建的运行时期的对象

lambda表达式是一种比较特殊的，匿名的，类类型[闭包类]的对象

我们可以任务它是一个带有operator()的类类型对象，也就是仿函数

所以，我们也可以用std::function和std::bind来保存和调用lambda表达式

```c++
std::function<int(int)> f1 = [](int i) {return i; };
```

lambda表达式这种语法，是我们可以就地定义匿名函数

不捕获任何变量的lambda表达式，可以转换成一个普通的函数指针

```c++
using functype = int(*) (int);
functype fp = [](int tv) {return tv; };
```

### 5.1 语法糖概念

```c++
//语法糖：一种便捷写法
int a[5];
a[0] = 1; //便捷写法(语法糖)
*(a+1)=3; //a[1]=3
```

## 六 lambda表达式再演示和优点总结

### 6.1 for_each()

```c++
std::vector<int> myvec = { 1,2,3,4,5 };
std::for_each(myvec.begin(), myvec.end(), myfunc);

std::vector<int> myvec = { 1,2,3,4,5 };
int isum = 0;
std::for_each(myvec.begin(), myvec.end(), [&isum](int val) {
    isum += val;
});
std::cout << "sum=" << isum << std::endl;
```

### 6.2 find_if简介

```c++
//用来查找一个东西，
std::vector<int> myvec = { 1,2,3,4,5 };
int isum = 0;
auto result = std::find_if(myvec.begin(), myvec.end(), [](int val) {
    std::cout << val << std::endl;
    if (val > 15)
        return true;
    return false; //只要返回false，那么find_if就不停的变量myvector，一直到返回true或者遍历完为止
});
//find_if的调用返回一个迭代器，指向第一个满足条件的元素，如果这样的元素不存在，则这个迭代器会指向myvector.end()
```

