# RTTI、dynamic_cast、typeid、虚函数表

## 一 RTTI是什么（Run Time Type Identification）：运行时类型识别

通过运行时类型识别，程序能够使用基类的指针或者引用来检查这邪恶指针或者引用所指的对象的实际派生类型

```c
Human *phuman = new Men;
Human &q = *phuman
```

RTTI我们可以把这个称呼看成是一种系统提供给我们的一种能力，或者一种功能。这种功能或者能力是通过2个运算符来体现

（1）dynamic_cast运算符：能够基类的**指针**或者**引用**安全的转换为派生类指针或者引用

（2）typeid运算符：返回指针或者引用所指对象的实际类型。

补充：要想让RTTI的两个运算符能够正常工作，那么基类中必须**至少要有一个虚函数**（因为只有虚函数，才会创建虚函数表，系统编译时才能保存派生类相应内容）。因为只有虚函数存在，这两个运算符才会使用指针或者引用所绑定的对象的动态类型（你new的类型）

## 二 dynamic_cast运算符

若父类指针想调用子类的成员函数，怎么做？

```c
Human *phuman = new Men;
Men *p = (Men *)phuman;
p->testfunc();
```

如果dynamic_cast能够转换成功，说明这个指针实际上是要转换到的那个类型。这个运算符能够帮我们做安全检查

```c++
Human *phuman = new Men;
Men *pmen = dynamic_cast<Men*>(phuman);
if(pmen != nullptr)
{
    cout << "phuman实际上是个Men类型"<< endl;
    //这这里操作Men里面的成员函数，都能被安全的调用
}
else
{
    cout << "phuman不是个Men类型"< endl;
}
```

引用类型，如果用dynamic_cast转换失败，则系统会抛出一个std::bad_cast异常

```c++
Human *phuman = new Men;
Human &q = *phuman;
try
{
	Men menbm = dynamic_cast<Men &>(q);
    cout << "phuman实际上是个Men类型"<< endl;
    //这这里操作Men里面的成员函数，都能被安全的调用
}
catch(std::bad_cast)
{
	cout << "phuman不是个Men类型"< endl;
}
```

## 三 typeid运算符

typeid(类型【指针/引用】)；也可能typeid(表达式)

拿到对象类型信息，typeid就会返回一个 常量对象的引用，这个常量对象 是一个标准库类型 type_info(类/类类型)

```c++
Human *phuman = new Men;
Human &q = *phuman;
cout << typeid(*phuman).name() << endl; //class Men
cout << typeid(q).name() << endl; //class Men

int b = 120;
cout << typeid(b).name() << endl;  //int
```

typeid主要是为了比较两个指针是否指向同一种类型的对象

（1）两个指针定义的类型相同（human）,不管他们new的啥，typeid都相等

```c++
Human *phuman = new Men;
Human *phuman2 = new Women;
if(typeid(phuman) == typeid(phuman2))
{
    cout << "phuman 和 phuman2 是同一种类型【指针定义】" << endl;
}
```

比较对象时，看的是new出来的是哪个对象或者该指针指向的是哪个对象，和定义该指针时定义的类型没关系

```c
Human *phuman = new Men;
Human *phuman2 = new Men;
if(typeid(*phuman) == typeid(*phuman2)) //千万不要把*落下
{
    cout << "phuman 和 phuman2 指向的对象是同一种类型" << endl;
}
if(typeid(*phuman) == typeid(Men)) //千万不要把*落下
{
    cout << "phuman指向Men" << endl;
}
```

切记：只有当基类有虚函数时，编译器才会对typeid()中的表达式求值，否则如果某个类型不含有虚函数，则typeid()返回的是表达式的静态类型（定义时的类型）

## 四 type_info类

typeid会返回一个 常量对象的引用，这个常量对象 是一个标准库类型 type_info(类/类类型)

（a）.name：名字

```
Human *phuman = new Men;
const type_info p &tp = typeid(*phuman);
cout << tp.name() << endl; //class Men
```

（b）==，!=

（b）==，!=

## 五 RTTI与虚函数表

c++中，如果类中函数虚函数。编译器就会对该类产生一个虚函数表

虚函数表里有很多项，每一项都是一个指针，每个指针指向都是这个类中的各个虚函数的入口地址

虚函数表项中，第一个表项很特殊，它指向的不是虚函数的入口地址，它指向的实际上是咱们这个类所关联的type_info对象。

```c
Human *phuman = new Men;
const type_info p &tp = typeid(*phuman);
```

phuman对象里有一个我们看不见的指针，这个指针指向的是这个对象所在的类Men里的虚函数表