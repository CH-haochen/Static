# shared_ptr常用操作、计数、自定义删除器等等

## 一 shared_ptr引用计数的增加和减少

### 1.1 引用计数的增加

每个shared_ptr都会记录有多少个其他的shared_ptr指向相同的对象

```c++
auto p6 = std::make_shared<int>(100);
auto p7(p6); //智能指针定义时的初始化，p7和p6指向了相同的对象，此对象目前有两个引用者
```

在如下情况下，所有指向这个对象的share_ptr引用计数都会增加1

(a)像上面这样，用p6来初始化p7这个智能指针

(b)把智能指针当做实参往参数里传递

```c++
void myfunc(std::shared_ptr<int> tmpPtr)
{
	return;
}

void myfunc2(std::shared_ptr<int> &tmpPtr) //如果参数为引用，则智能指针的引用计数不会增加
{
	return;
}

myfunc(p7);
```

(c)作为函数的返回值 

```c++
std::shared_ptr<int> myfunc3(std::shared_ptr<int> &tmpPtr)
{
	return tmpPtr;
}

auto p8 = myfunc3(p7); //引用计数会变成3，这是因为有p8来接这个临时的智能指针
myfunc3(p7); //如果没有变量来接这个临时的智能指针，则临时智能指针生命周期到了，引用计数从3恢复到2

```

### 1.2 引用计数的减少

（a）给shared_ptr赋予新值，让该shared_ptr指向一个新对象

```c++
p8 = std::make_shared<int>(200); //p8指向新对象，计数为1，p6，p7指向的对象计数恢复为2
p7 = std::make_shared<int>(300); //p7指向新对象，计数为1，p6指向的对象计数恢复为1
p6 = std::make_shared<int>(400); //p6指向新对象，计数为1，p6，p7指向的内存被释放
```

（b）局部的shared_ptr离开其作用域

```c++
void myfunc(std::shared_ptr<int> tmpPtr)
{
	return;
}

auto p6 = std::make_shared<int>(100); //目前p6所指向的对象只有p6一个引用者
auto p7(p6); //p7和p6指向相同的对象，引用计数为2
myfunc(p7); //进入函数体myfunc中是3个引用计数，从myfunc中退出时引用计数恢复为2个
```

（c）当一个shared_ptr引用计数从1变成0，则它会自动释放自己所管理(指向)的对象

```c++
auto p9 = std::make_shared<int>(100);
auto p10 = std::make_shared<int>(100);
p9 = p10; //给p9赋值会让p9指向p10所指向的对象，该对象引用计数变成2，而原来p9所指向的对象引用计数会从1变成0，从而导致内存被释放
```

## 二 shared_ptr指针常用操作

### 2.1 use_count(): 返回多少个只能指针指向某个对象，主要用于调试目的

```c++
std::shared_ptr<int> myp(new int(100));
int icount = myp.use_count(); //1
std::shared_ptr<int> myp2(myp);
icount = myp.use_count(); //2
```

### 2.2 unique(): 是否该智能指针独占某个指向的对象，也就是若只有一个智能指针指向某个对象，则unique()返回true，否则返回False

就是看引用计数是否为1

```c++
std::shared_ptr<int> myp(new int(100));
if (myp.unique())
{
    std::cout << "unique OK" << std::endl;//进到这里
}
else
{
    std::cout << "unique No" << std::endl;
}

std::shared_ptr<int> myp2(myp);
if (myp.unique())
{
    std::cout << "unique OK" << std::endl;
}
else
{
    std::cout << "unique No" << std::endl;//进到这里
}

std::shared_ptr<int> myp3;
if (myp3.unique())
{
    std::cout << "unique OK" << std::endl;
}
else
{
    std::cout << "unique No" << std::endl; //进到这里
}
```

### 2.3 reset(): 恢复(复位/重置)的意思

（a）reset()不带参数时

若pi是唯一指向该对象的指针，那么释放pi所指向的对象，并将pi置空

```c++
std::shared_ptr<int> pi(new int(100));
pi.reset();
if (pi == nullptr)
{
    std::cout << "pi被置空" << std::endl;
}
```

若pi不是唯一指向该对象的指针，那么不释放pi所指向的对象，但指向该对象的引用计数会减少1，同时将pi置空

```c++
std::shared_ptr<int> pi(new int(100));
auto pi2(pi);
pi.reset();
```

（b）reset()带参数时(一般是一个new出来的指针)时

若pi是唯一指向该对象的指针，则释放pi指向的对象，让pi指向信对象

```c++
std::shared_ptr<int> pi(new int(100));
pi.reset(new int(1));
```

若pi不是唯一指向该对象的指针，则不释放pi指向的对象，但指向该对象的引用计数会减少1，同时让pi指向新对象

```c++
std::shared_ptr<int> pi(new int(100));
auto pi2(pi);
pi.reset(new int(1)); //释放原内存，指向新内存
```

也可以对null指针初始化

```c++
std::shared_ptr<int> p;
p.reset(new int(1)); //释放p所指向的对象，让p指向新对象，因为原来p为空的，所以就等于啥也没释放。直接指向新对象
```

### 2.4 *解引用：获得p指向的对象

```c++
std::shared_ptr<int> p(new int(100));
std::cout << *p << std::endl; //100
```

### 2.5 get()：考虑到有些第三方库的函数的参数需要的是一个内置裸指针而不是智能指针

p.get(): 返回p中保存的指针(裸指针)，小心使用，如果智能指针释放了所指向的对象，那么返回的这个裸指针也就变得无效了

```c++
std::shared_ptr<int> myp(new int(100));
int *p = myp.get();
*p = 45;
//delete p;  //p是用智能指针管的，千万不要这么干，不然系统会报告异常，产生不可预料的结果
```

### 2.6 swap(): 交换两个智能指针所指向的对象

```c++
std::shared_ptr<std::string> ps1(new std::string("I love China1"));
std::shared_ptr<std::string> ps2(new std::string("I love China2"));
std::swap(ps1, ps2);
ps1.swap(ps2);
```

### 2.7 = nullptr

（a）将所指向的对象 引用计数减1，若引用计数变为0，则释放智能指针所指向的对象

（b）将智能指针置空

```c++
std::shared_ptr<std::string> ps1(new std::string("I love China"));
std::shared_ptr<std::string> ps2(ps1);
ps1 = nullptr;
```

### 2.8 智能指针名字作为判断条件

```c++
std::shared_ptr<std::string> ps1(new std::string("I love China"));
if (ps1)
{
    std::cout << "ps1指向一个对象" << std::endl;
}
else
{
    std::cout << "ps1为空" << std::endl;
}
```

### 2.9 指定删除器以及数组问题

（a）指定删除器

一定时机帮我们删除所指向的对象; delete: 将delete运算符号作为默认的资源析构方式

我们可以指定自己的删除器取代系统提供的默认删除器，当智能指针需要删除所指向的对象时，编译器就好调用我们自己定义的删除器来删除

shared_ptr指定删除器方法比较简单，一般只需要在参数中添加具体的删除器函数名即可

```c++
//我们的删除器，删除整型指针用的，当智能指针引用计数为0，就会自动调用该删除器来删除对象
void myDelete(int *p)
{
	//写一些日志
	delete p; //既然你自己提供了删除器来取代智能指针的缺省删除器，你就有义务自己来删除所指向的对象(引用计数为0时)
}

std::shared_ptr<int> p(new int(100), myDelete);
std::shared_ptr<int> p2(p); //两个引用计数
p2.reset(); //剩1个引用计数，p2为nullptr
p.reset(); //因为此时只有1个引用计数，所以要释放指向的对象，调用外贸的删除器myDelete，同时p置空
```

删除器可以是一个lambda表达式

```c++
std::shared_ptr<int> ps(new int(123), [](int *p) {
    delete p;
});
```

有些情况，默认删除器处理不了(用shared_ptr管理动态数组)，需要外贸提供自己制定的删除器

```c++
std::shared_ptr<int> ps(new int[10], [](int *p) {
    delete []p;
});

class A
{
    public:
    A() {};
    ~A() {};
};

std::shared_ptr<A> ps2(new A[10]); //这种使用默认delete会报异常， 因为系统释放ps2是delete ps2指向的裸指针，而不是delete []ps2，这种情况下就需要自己定义删除器
std::shared_ptr<A> ps2(new A[10], [](A *p) {
    delete []p;
});


//可用default_delete来做删除器，default_delete是标准库里的模板累
std::shared_ptr<A> pA(new A[10], std::default_delete<A[]>());

//还有一种，最新标准，在定义的时候，在尖括号中加[]
std::shared_ptr<A[]> pA(new A[10]);

std::shared_ptr<int[]> pAA(new int[10]);
pAA[0] = 12;
pAA[1] = 15;
```

写个函数模板来封装shared_ptr数组

```c++
template<typename T>
std::shared_ptr<T> make_shared_array(size_t size)
{
	return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

std::shared_ptr<int> printArr = make_shared_array<int>(5);
std::shared_ptr<A> printArr = make_shared_array<A>(15);
```

（b）指定删除器额外说明

就算是两个shared_ptr指定了不同的删除器，只要他们所指向的对象类型相同，那么这两个shared_ptr也属于同一个类型

```c++
auto lambda1 = [](int *p)
{
    //日志。。
    delete p;
};

auto lambda2 = [](int *p)
{
    //日志。。
    delete p;
};

std::shared_ptr<int> p1(new int(100), lambda1);
std::shared_ptr<int> p2(new int(200), lambda1);
p2 = p1; //p2 会先调用lambda2把自己所指向的对象释放，然后指向p1所指的对象。p1指向的对象引用计数为2
//整个main执行完毕后，还会调用lambda1来释放p1,p2共同指向的对象

//类型相同，就代表可以放到元素类型为该对象类型的容器里来
std::vector<std::shared_ptr<int>> pvec{ p1,p2 };
```

