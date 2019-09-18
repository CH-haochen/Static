# new/delete探秘，只能指针概述，share_ptr基础

## 一 new/delete探秘

### 1.1 new,delete是什么

sizeof(关键字/运算符),不是个函数

new,delete(关键字/运算符),不是个函数

malloc/free(主要用于c语言编程中)，而new/delete用于c++编程：这两对儿都用于动态在堆中分配/释放内存

new/delete比malloc/free干事情更多

```c++
A *pa = new A(); //构造函数被调用
delete pa;	//析构函数被调用
```

new/delete具备对 堆上所分配内存进行初始化/释放(反初始化)的能力，而这些能力是malloc/free所不具备的

### 1.2 operator new()和operator delete()

```c++
int *pi = new int;
delete pi;
```

#### 1.2.1 new干了两个事情

(a)分配内存(通过operator new()来分配内存) 

(b)调用构造函数来初始化内存

#### 1.2.2 delete干了两个事情

(a)调用析构函数

(b)释放内存(调用operator delete()来释放内存)

### 1.3 基本new如何机率分配的内存大小供delete使用

```c++
//不同的编译器new内部有不同的实现方式
int *p = new int; //4字节
delete p; //删除的时候，编译器怎么知道要回收的是4字节，new内部有记录机智，记录了分配出去多少内存
```

### 1.4 申请和释放一个数组

```c++
int *p = new int(100); //分配4字节，给int = 100
int *p = new int[2]; //int数组，有两个元素，泄露8字节

A a;
int ilen = sizeof(a); //类对象肯定有地址，你就得至少占1个字节的地方

A *pA = new A(); //泄露1字节
A *pA = new A[2](); //这里泄露6字节，而不是2字节，多出来4字节
int *p = new int[2]; //int数组，有两个元素，泄露8字节，并没有多出来字节
//疑问： 为什么动态给类型A分配内存对象数组时多出来4个字节，而给内置类型int动态分配内存对象数组时没有多出来
//       因为需要额外字节记录数组内元素个数叭

//new[] 应该用delete[]释放
//内置类型
int *p = new int[3]; //
delete p; //没有用delete[]，似乎也可以直接释放p这个int数组，没有发生内存泄露
delete[] p; //这种释放方法才是规范的，绝对没有问题的
//类类型
A *pA = new A[2](); //泄露6字节，2个字节代表类对象数组占用的，额外4字节我们纳闷这4字节从哪里来
delete pA; //系统报告异常
delete[] pA; //这种写法是最规范的，没有问题的
```

### 1.5 为什么new/delete、new[]/delete[]要配对使用

内置类型比如int不需要调用析构函数，所以new[]的时候并没有多分配出4字节

对于int类型，new[], delete p 或者 delete[] p，效果一样

结论：如果一个对象（内置对象int,float,包括类对象），使用new[]来分配内存，却用单独的delete来释放内存，那么这个对象需要满足的条件是：对象的类型要么是内置类型或者 无自定义的析构函数的类类型

对象的类型要么是内置类型或者 无自定义的析构函数的类类型

```c++
A *pA = new A[2](); //如果没析构函数，这里就分配了2个字节
delete []pA; //为什么自己一提供析构函数，不用delete[]来释放new[]出来的内存就报异常呢？
//a)调用一次A的析构函数而不是2次，至少是表示有内存泄露
//b)调用operator delete(pA);释放内存
```

## 二 智能指针总述

c++ 标准库有四种智能指针 std::

auto_ptr(c++98); unique_ptr; shared_ptr; weak_ptr

帮助进行动态分配对象(new出来的对象)的生命周期的管理。能够有效防止内存泄露

目前auto_ptr已经完全被unique_ptr取代，大家不要再使用 auto_ptr;c++11标准中反对使用auto_ptr

这三种只能指针都是类模板，我们可以将new获得地址赋给他们

（a）shared_ptr: 共享式指针。多个指针指向同一个对象，最后一个指针被销毁时，这个对象会被释放

weak_ptr是辅助shared_ptr工作的

（b）unique_ptr: 独占式指针；同一个时间内，只有一个指针能够指向该对象

当然，该对象的所有权还是可以移交出去的

你忘记delete的时候，智能指针帮助你delete

## 三 shared_ptr基础

共享所有权，不是被一个shared_ptr拥有，而是被多个shared_ptr之间相互协作；shared_ptr有额外开销

工作原理：引用计数，每个shared_ptr的拷贝都指向相同的内存。所以，只有最后一个指向该内存(对象)的shared_ptr指针不需要再指向该对象时，那么这个shared_ptr才会去析构所指向的对象

最后一个指向该内存对象的shared_ptr在什么情况下会释放该对象(shared_ptr所指向的对象)呢？

（a）这个shared_ptr被析构的时候

（b）这个shared_ptr指向其他对象时

类似于垃圾回收机制

类模板，用到<>, <>里，就是指针可以指向的类型，后边再跟智能指针名

格式： shared_ptr<指向的类型> 智能指针名

### 3.1 常规初始化(shared_ptr和new配合)

```c++
std::shared_ptr<int> pi; //指向int的智能指针，名字pi，但目前指向为空，空指针，nullptr
std::shared_ptr<int> pi(new int(100)); //pi指向一个值为100的int型数据
std::shared_ptr<int> pi2 = new int(100); //不行，智能指针是explicit，不可以进行隐式类型转换，必须用直接初始化形式

//裸指针可以初始化shared_ptr，但不推荐。智能指针和裸指针不要穿插用
int *pi = new int;
std::shared_ptr<int> p1(pi);

std::shared_ptr<int>(new int);
```

### 3.2 make_shared函数： 标准库里的函数模板，安全，高效的分配和使用shared_ptr;

它能够在动态内存(堆)中分配并初始化一个对象，然后返回指向此对象的shared_ptr

```c++
std::shared_ptr<int> p2 = std::make_shared<int>(100); //这个shared_ptr指向一个值为100的整型内存
std::shared_ptr<std::string> p3 = std::make_shared<std::string>(5, 'a'); //5个字符生成的字符串
//类似于string mystr(5, 'a');
std::shared_ptr<int> p4 = std::make_shared<int>(); //p4指向一个int，int里保存的值是0（值初始化）
p4 = std::make_shared<int>(400); //p4指向一个新int，int里保存的是400；p4首先释放刚才指向的值为0的内存，然后指向这个值为400的内存

auto p5 = std::make_shared<std::string>(5, 'a'); //用auto比较简单
```

