# unique_ptr续

## 一 返回unique_ptr

虽然unique_ptr智能指针不能拷贝，但是，当这个unique_ptr将要被销毁，是可以拷贝的。最常见用法就是从函数返回一个unique_ptr

```c++
unique_ptr<string> tuniqp()
{
	unique_ptr<string> pr(new string("I love China"));
	return pr; //从函数返回一个局部的unique对象。三章十四节讲过移动构造函数
				//返回这种局部对象，导致系统给我们生成一个临时unique_ptr对象，调用unique_ptr的移动构造函数
	//或者
	//return unique_ptr<string> pr(new string("I love China"));
}

unique_ptr<string> ps;
ps = tuniqp(); //可以用ps来接，则临时对象直接构造在ps里，如果不接，则临时对象会被释放，同时会释放掉所指向的对象内存
```

## 二 指定删除器 delete:默认删除器

### （a）指定删除器

格式： unique_ptr<指向的对象类型，删除器> 智能指针变量名

删除器，可调用对象。比如函数、类重载了()

我们学习过了shared_ptr删除器，比较简单 shared_ptr<int> p(new int(), mydelete);

unique_ptr删除器相对复杂一点，多了一步，先要在类型模板参数中传递进去类型名，然后在参数中再给具体的删除其函数名

```c++

void mydelete(string *pdel)
{
	delete pdel;
	pdel = nullptr;
}

//a.1
typedef void(*fp)(string *);  //定义一个函数指针类型，类型名为fp
unique_ptr<string, fp> ps1(new string("I love China"), mydelete);

//a.2
using fp2 = void(*)(string *); //用using定义一个函数指针类型，类型名为fp2
unique_ptr<string, fp2> ps1(new string("I love China"), mydelete);

//a.3
typedef decltype(mydelete)* fp3; //这里多了一个*,因为decltype返回的是函数类型void(string *)
//加*表示函数指针类型，现在fp3应该void*(string *)
unique_ptr<string, fp3> ps1(new string("I love China"), mydelete);

//a.4
unique_ptr<string, decltype(mydelete)*> ps1(new string("I love China"), mydelete);

//a.5 lambda表达式
auto mydela = [](string *pdel) { //把lambda表达式理解为class
    delete pdel;
    pdel = nullptr;
};
unique_ptr<string, decltype(mydela)> ps1(new string("I love China"), mydela);
```

### （b）指定删除器额外说明

shared_ptr: 就算两个shared_ptr指定的删除器不相同，只要他们所指向的对象相同，那么这两个shared_ptr也属于同一个类型
unique_ptr: 指定unique_ptr中的删除器会影响unique_ptr类型，所以从灵活性来讲，shared_ptr设计的更灵活

shared_ptr，删除器不同，但指向类型一样的shared_ptr，可以放到同一个容器里. unique_ptr, 删除器不同，那么就等于整个unique_ptr类型不同。这种类型不同的unique_ptr智能指针是没有办法放到同一个容器里的

## 三 尺寸问题：通常情况下，unique_ptr尺寸和裸指针一样

```c++
string *p;
int ilenp = sizeof(p); //4字节
unique_ptr<string> ps(new string("I love China"));
int len = sizeof(ps); //4字节
```

如果你增加了自己的删除器，则unique_ptr尺寸可能增加也可能不增加

（a）如果lambda表达式这种删除器，尺寸没变化

（b）定义一个函数作为删除器，尺寸发生变化

## 四 智能指针总结

### 4.1 智能指针背后的设计思想

智能指针主要目的：帮助我们释放内存，以防止我们忘记释放内存时造成的内存泄露

c++98 auto_ptr == unique_ptr

### 4.2 auto_ptr为什么被废弃

auto_ptr c++98时代的智能指针，具有unique_ptr一部分特性

不能在容器中保存，也不能从函数中返回auto_ptr

```c++
auto_ptr<string> ps3(new string("I love China")); 
auto_ptr<string> ps2 = ps3; //ps2指向字符串，ps3变成空了
//用ps3（你没有意识到ps3已经空了），代码就会崩溃，这也是auto_ptr用法上的一个陷阱 
```

### 4.3 智能指针的选择

（a）如果程序要是用多个指向同一个对象的指针，应该选shared_ptr
（b）如果程序不需要多个指向同一个对象的指针，应该首选unique_ptr

