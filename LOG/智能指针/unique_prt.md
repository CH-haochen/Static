# unique_prt

## 一 unique_ptr概述

独占式的概念（专属所有权）： 同一时刻，只能有一个unique_ptr指针指向这个对象（这块内存）

当这个unique_ptr被销毁的时候，它所指向的对象也被销毁

格式：unique_ptr<指向的对象类型> 智能指针变量名

### 1.1 常规初始化(unique_ptr和new配合)

```c++
std::unique_ptr<int> pi; //可以指向int对象的一个空智能指针
std::unique_ptr<int> pi2(new int(100)); //此时pi2指向一个值为105的int对象
```

### 1.2 make_unique函数

c++11中没有，c++14中才有的make_unique: 不支持指定的删除器语法，如果不用删除器，建议优先使用， 更高的性能

```c++
std::unique_ptr<int> p1 = std::make_unique<int>(100);
auto p2 = std::make_unique<int>(200);
```

## 二 unique_ptr常用操作

### 2.1 unique_ptr不支持的操作(独占式)

```c++
unique_ptr<string> ps1(new string("I love China"));
unique_ptr<string> ps2(ps1);  //该智能指针不支持拷贝动作(定义时初始化)
unique_ptr<string> ps3 = ps1; //该智能指针不支持拷贝动作(定义时初始化)
unique_ptr<string> ps4;
ps4 = ps1; //独占式智能指针不支持赋值操作
```

### 2.2 移动语义

```c++
unique_ptr<string> ps1(new string("I love China"));
unique_ptr<string> ps2 = std::move(ps1); //移动完后，ps1为空，ps2指向原来ps1所指
```

### 2.3 release()

放弃对指针的控制权(切断了智能指针和其所指向对象之间的联系),返回裸指针，将该智能指针置空。返回的这个裸指针外贸可以手工delete来释放，也可以用来初始化另外一个只能指针，或者给另外一个智能指针赋值

```c++
unique_ptr<string> ps1(new string("I love China"));
unique_ptr<string> ps2(ps1.release());

ps2.release(); //会导致内存泄露

//人工释放就不会泄露了
string *temp = ps2.release();
delete temp;
```

### 2.4 reset()

reset()不带参数的情况： 释放智能指针所指向的对象，并将只能指针置空

```c++
unique_ptr<string> ps1(new string("I love China"));
ps1.reset();
if (ps1 == nullptr)
{
    cout << "ps1被置空" << endl;
}
```

reset()带参数情况：释放该智能指针所指向的对象，并让该智能指针指向新对象

```c++
unique_ptr<string> ps2(new string("I love China2"));
ps1.reset(ps2.release()); //reset释放ps1指向的对象内存，让ps1指向ps2所指向的内存，同时ps2置空
ps1.reset(new string("I love China3"));
```

### 2.5 =nullptr： 释放智能指针所指向的对象，并将智能指针置空

```c++
unique_ptr<string> ps1(new string("I love China"));
ps1 = nullptr;
```

### 2.6 指向一个数组

```c++
unique_ptr<int[]> ptarray(new int[10]); //注意，数组这里要跟上{]
ptarray[0] = 10;
ptarray[1] = 11;

//当自己定义一个类对象时，并且用智能指针初始化类对象数组，一定不要忘记[]，否则如果有自己的析构函数，会报异常
//unique_ptr<A[]> ptarray(new A[10]);
```

### 2.7 get()

返回智能指针中保存的裸指针，考虑到有些函数参数需要的是内置裸指针，所以引入该函数

```c++
unique_ptr<string> ps1(new string("I love China"));
string *ps = ps1.get();
*ps = "this is a test";
//千万不要delete ps，否则产生不可预料的后果
```

### 2.8 * 解引用

获取该智能指针指向的对象，可以直接操作

```c++
unique_ptr<string> ps1(new string("I love China"));
*ps1 = "this is a test";
```

### 2.9 swap() 

交换两个智能指针所指向的对象

```c++
unique_ptr<string> ps1(new string("I love China"));
unique_ptr<string> ps2(new string("I love China2"));
std::swap(ps1, ps2);
ps1.swap(ps2);
```

### 2.10 智能指针名字作为判断条件

```c++
unique_ptr<string> ps1(new string("I love China"));
if (ps1)
{
    cout << "ps1不为空" << endl;
}
```

### 2.11 转换成shared_ptr类型

如果unique_ptr为右值，就可以将它赋值给shared_ptr。因为shared_ptr包含一个显式构造函数，可用于将右值unique_ptr转换为shared_ptr，shared_ptr将接管原来unqie_ptr所拥有的对象

```c++
auto myfunc()
{
	return unique_ptr<string>(new string("I love China")); //这是个右值，返回的是临时对象，所以为右值
}

shared_ptr<string> pss1 = myfunc();

unique_ptr<string> ps(new string("I love China"));
shared_ptr<string> pss1 = std::move(ps);
```

