# shared_ptr使用陷阱

## 一 shared_ptr使用陷阱分析

### 2.1 慎用裸指针

把一个普通裸指针绑定到了一个shared_ptr上之后，那内存管理的责任就交给这个shared_ptr了，这个时候你就不应该再用裸指针(内置指针)来访问shared_ptr所指向的内存了

```c++
int *p = new int(100); //裸指针
//proc(p); //语法错，int *p不能转换成shared_ptr<int>
std::shared_ptr<int> p2(p);
proc(p2);
*p = 45; //不能这么用，潜在的不可预料的问题，因为p指向的内存已经被释放了
*p2 = 45; //ok
```

```c++
proc(std::shared_ptr<int>(p));
*p = 45; //潜在的不可预料的问题，因为p指向的内存已经被释放了
```

```c++
//这样是合法的
std::shared_ptr<int> myp(new int(100));
proc(myp);
*myp = 45; //因为操作的不是裸指针，而是智能指针
```

```c++
//绝对要记住， 不要用裸指针初始化多个shared_ptr
int *p = new int(10);
std::shared_ptr<int> p1(p);
std::shared_ptr<int> p2(p); //p1和p2无关联了,会导致p1和p2所指向的内存被释放两次，产生异常
```

### 2.2 慎用get()返回的指针

返回只能指针指向的对象所对应的裸指针(有些函数接口可能只能使用裸指针)

get返回的指针不能delete，否则会异常

```c++
std::shared_ptr<int> myp(new int(100));
int *p = myp.get();
delete p; //不可以删除，会导致异常
```

结论： 永远不要用get得到的指针来初始化另外一个智能指针或者给另外一个智能指针赋值

### 2.3 不要把类对象指针(this)作为shared_ptr返回，改用enable_shared_from_this

```c++
class CT
{
public:
	std::shared_ptr<CT> getself()
	{
		return std::shared_ptr<CT>(this); //用裸指针初始化了多个shared_ptr的感觉
	}
};

std::shared_ptr<CT> pct1(new CT);
std::shared_ptr<CT> pct2 = pct1; //ok

std::shared_ptr<CT> pct2 = pct1->getself(); //问题出现
```

若非要这么用，用到c++标准库里边的类模板：enable_shared_from_this

```c++
class CT :  public std::enable_shared_from_this<CT>
{
public:
	std::shared_ptr<CT> getself()
	{
		return shared_from_this(); //这个就是enable_shared_from_this类中的方法，要通过此方法返回智能指针
	}
};
```


现在，在外创建CT对象的智能指针以及通过CT对象返回的this只能指针都是安全的。这个enable_shared_from_this中有一个弱指针weak_ptr，这个弱指针能够监视this，在我们调用shared_from_this()这个方法时，这个方法内部实际上是调用了这个weak_ptr()的lock()方法，大家都知道lock()方法会让shared_ptr指针计数+1， 同时返回这个shared_ptr,这个就是工作原理

### 2.4 避免循环引用， 会导致内存泄露

```c++
class CB;
class CA
{
public:
	std::shared_ptr<CB> m_pbs;
	~CA()
	{
		int test;
		test = 1;
	}
};

class CB
{
public:
	std::shared_ptr<CA> m_pas;
	~CB()
	{
		int test;
		test = 1;
	}
};

std::shared_ptr<CA> pca(new CA);
std::shared_ptr<CB> pcb(new CB);
pca->m_pbs = pcb;  //等价于指向CB对象的有两个强引用
pcb->m_pas = pca;  //等价于指向CA对象的有两个强引用

```

解决方法：一个用强引用，一个用弱引用

```c++
class CB;
class CA
{
public:
	std::shared_ptr<CB> m_pbs;
	~CA()
	{
		int test;
		test = 1;
	}
};

class CB
{
public:
	std::weak_ptr<CA> m_pas;
	~CB()
	{
		int test;
		test = 1;
	}
};

std::shared_ptr<CA> pca(new CA);
std::shared_ptr<CB> pcb(new CB);
pca->m_pbs = pcb;  //等价于指向CB对象的有两个强引用
pcb->m_pas = pca;  //因为m_pas是弱引用，所有这里指向CA的对象只有一个强引用，离开作用域之后，pca引用计数从1变成0会释放CA对象（CA的析构函数被执行）；CA的析构函数被执行(表示对象即将被释放),导致CA内的m_pbs引用计数会减1，也就是指向CB对象的引用计数减1，超出pcb作用域时指向CB的计数也会减1，最终，会有一个时刻，指向CB对象的强引用计数会从1减少到0，导致CB对象被释放

```

## 三 性能说明

### 3.1 尺寸问题

shared_ptr的尺寸是裸指针的2倍，weak_ptr尺寸是裸指针的2倍

```c++
char *p;
int ilenp = sizeof(p); //4字节
std::shared_ptr<std::string> p1;
int ilensp = sizeof(p1); //8字节， 包含两个裸指针

//第一个裸指针 指向的是这个只能指针所指向的对象
//第二个裸指针 指向一个很大的数据结构(控制块),这个控制块有：
		//1:所指对象的强引用计数
		//2:所指对象的弱引用计数
		//3:其他数据，比如自定义的删除器的指针等等
```

### 3.2 移动语义

```c++
std::shared_ptr<int> p1(new int(100));
std::shared_ptr<int> p2(std::move(p1)); //移动语义，移动构造一个新的智能指针对象p2
//p1就不再指向该对象(变成空)，引用计数依旧是1

std::shared_ptr<int> p3;
p3 = std::move(p2); //移动赋值，p2指向空，p3指向该对象，整个对象引用计数仍旧为1
```

移动肯定比复制快