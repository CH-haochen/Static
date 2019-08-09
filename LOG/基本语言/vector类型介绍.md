# vector类型介绍

## 一 vector类型简介 

标准库：集合或者动态数组

vector里面不能装引用，指针可以

```c++
std::vector<int &> vjihe; // 引用是个别名，不是个对象。不是对象不能往vector里放
```

## 二 定义和初始化vector对象

### 2.1 空vector

```c++
std::vector<std::string> mystr; // 创建一个string类型的空的vector对象（容器），目前这个mystr里不包含任何元素
```

### 2.2 元素拷贝的初始化方式

```c++
std::vector<std::string> mystr2(mystr); //把mystr元素拷贝给了mystr2
std::vector<std::string> mystr3 = mystr; //把mystr元素拷贝给了mystr3
```

### 2.3 c++11中，用列表初始化方法给值，用{}

```c++
std::vector<std::string> mystr4 = { "aaa", "bbb", "ccc" };
```

### 2.4 创建指定数量的元素。有元素数量概念的东西，一般会用圆括号

```c++
std::vector<int> ijihe(15, -200); //创建15个int类型的元素，每个元素的值是-200

std::vector<int> ijihe(15); //15个元素怒，每个元素都为0
```

### 2.5 多种初始化方式，()一般表示对象中元素数量这个概念。{}一般表示元素内容的概念

要想正常的通过{}初始化，那么{}里面的值的类型，必须要跟vector后边这个<>里面的元素类型相同

```c++
std::vector<int> i1(10); //表示10个元素，每个元素是0
std::vector<int> i1{ 10 }; //表示1个元素，元素是10
std::vector<std::string> i1{ "hello" }; //表示1个元素，元素是hello
std::vector<std::string> i2{ 10 }; //表示10个元素，每个元素是""
```

## 三 vector对象上的操作

最常用的是不知道vector里有多少个元素。需要动态增加/减少

（a） 判断是否为空 empty()

（b） push_back(); 常用方法，添加元素到vector末尾

（c） size(); 返回元素个数

（d） clear();  移除所有元素，将容器清空。 只是size变了，capacity是没变的

（e） v[n];  返回v中第n个元素

（f） = ;  赋值

（g） ==, !=

两个vector相等：元素数量相同，对应位置的元素值也得一样。否则就是不等

（h）范围for的应用

```c++
std::vector<int> i1 = { 1,2,3,4,5 };
for (auto &x : i1)
{
    i1.push_back(888); //导致输出彻底乱套
    std::cout << x << std::endl;
}
```

结论：在for语句中（遍历一个容器等等类似操作中），千万不要改动vector容器的容量，增加/删除都不可以