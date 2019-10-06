九 lambda表达式捕获模式的陷阱分析和展示

## 一 捕获列表中的&

捕获外部作用域中的所有变量，并作为引用在lambda表达式中使用

按照引用这种捕获方式，会导致lambda表达式包含绑定到局部变量的引用

```c++
std::vector<std::function<bool(int)>> gv;

void myfunc()
{
	srand((unsigned)time(NULL));
	int tmpvalue = rand() % 6; //产生一个0-5之间的随机数
	gv.push_back([&](int tv) {
		if (tv & tmpvalue == 0) //如果tv是tmpvalue的倍数
		{
			return true;
		}
		return false;
	
	});
}

int main()
{
    myfunc();
	std::cout << gv[0](10) << std::endl; //非法调用，因为在tmpvalue作用域外调用lambda表达式  
}

```

## 二 形参列表可以使用auto

```c++
c++14允许 [](auto tv){};
```

## 三 成员变量的捕获问题

```c++
class AT
{
public:
	int m_tmpvalue = 8;
	void addItem()
	{
		gv.push_back([=](int tv) { //= 就等于有this
			if (tv & m_tmpvalue == 0)  //this->m_tmpvalue
			{
				return true;
			}
			return false;

		});
	}
};

AT *pat = new AT();
pat->addItem();
std::cout << gv[0](10) << std::endl;
delete pat;
//lambda表达式执行正确与否，取决于pat对象是否存在

//我们首先要明确一点：捕获这个概念，只针对于在总创建lambda表达式的作用域内可见的 非静态 局部变量（包括形参）
//m_tmpvalue并不是非静态局部变量。是AT类的成员变量，成员变量是不能被捕获到的
//this:指向对象本身。所以这里用的[=]捕获的是this指针值
```

如何让lambda表达式不依赖对象呢？创建一个拷贝

```c++
class AT
{
public:
	int m_tmpvalue = 8;
	void addItem()
	{
		auto tmpvalueCopy = m_tmpvalue; //作为副本

		gv.push_back([=](int tv) { //= 就等于有this
			if (tv & tmpvalueCopy == 0)  //this->m_tmpvalue
			{
				return true;
			}
			return false;
		});
	}
};

AT *pat = new AT();
pat->addItem();
delete pat; //这样就算先删也没事儿
std::cout << gv[0](10) << std::endl;

```

## 四 广义lambda捕获： c++14 generalized lambda capture

```c++
class AT
{
public:
	int m_tmpvalue = 8;
	void addItem()
	{

		gv.push_back([abc = m_tmpvalue](int tv) { //将m_tmpvalue复制到闭包里来
			if (tv & abc == 0)  
			{
				return true;
			}
			return false;

		});
	}
};
```

## 五 静态局部变量

静态局部变量不能被捕获，但是可以在lambda中使用

但是这种对static变量的使用有点类似于按引用捕获的效果

```c++
void myfunc()
{
	srand((unsigned)time(NULL));
	//int tmpvalue = rand() % 6; //产生一个0-5之间的随机数
	static int tmpvalue = 6; //静态变量是不需要捕获
	gv.push_back([](int tv) {
		std::cout << tmpvalue << std::endl;
		if (tv & tmpvalue == 0) //如果tv是tmpvalue的倍数
		{
			return true;
		}
		return false;
	});
	tmpvalue++;
}

myfunc();
gv[0](10); //5
```

