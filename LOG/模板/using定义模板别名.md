# using定义模板别名

## 一 using定义模版别名

typedef: 一般用来定义类型别名

```c++
typedef unsigned int uint_t; //相当于给unsigned int类型起了一个别名uint_t;
uint_t abc;

typedef std::map<std::string, int> map_s_i;
map_s_i mymap;
mymap.insert({"first", 1});

typedef std::map<std::string, std::string> map_s_s;
map_s_s mymap2;
mymap2.insert({"first", "firstone"});
```



希望定义一个类型，前边这部分固定不变，是std::map<std::string, 类型自己指定>

我们为了实现这种比较通用的以string为key，以任意类型为value(值)的map容器，我们不得不自己写一个类来达到这个目的

```c++
//c++98
template<typename st>
struct map_s
{
	typedef std::map<std::string, st> type; //
};

map_s<int>::type map1; //等价于 std::map<std::string, int> map1;
map1.insert({ "first", 1 });
```



```c++
//c++11
template<typename T>
using str_map_t = std::map<std::string, T>;  //str_map_t是类型别名
											//using用来给一个“类型模板”起名字（别名）用的
str_map_t<int> map2;
map2.insert({ "second", 2 });
```



using在用于定义类型(定义类型模板)的时候，是包含了typedef的所有功能的

```c++
typedef unsigned int uint_t;
using uint_t = unsigned int;

typedef std::map<std::string, int> map_s_i;//typedef定义类型的方法感觉像 定义一个变量
using map_s_i = std::map<std::string, int>;

typedef int(*FuncType)(int, int); //用typedef定义函数指针；
using FuncType = int(*)(int, int); //using定义类型的定义方法感觉像赋值
```

例子

```c++
template<typename T>
using myfunc_M = int(*)(T, T); //定义类型模板，是个函数指针模板

int realFUNC(int i, int j)
{
	return 1;
}

myfunc_M<int> pointFunc; //myfunc_M<int>是一个函数指针类型， 是一个类型名
							//pointFunc是一个函数指针
pointFunc = &realFUNC; //把函数地址赋给函数指针变量
std::cout << pointFunc(1, 1) << std::endl;
```

总结：
using中使用这种模板，既不是类模板，也不是函数模板，我们可以看成是一种新的模板类型：类型模板（模板别名）



## 二 显示指定模板参数

```c++

template<typename T1, typename T2, typename T3>
T1 sum(T2 i, T3 j)
{
	T1 result = i + j;
	return result;
}
```

```c++
auto result = sum<int>(200000000, 200000000); //显示指定了第一个T1参数int，后两个自己推断
												 //显然20亿加20亿用int保存会溢出				
auto result = sum<double, double, double>(200000000, 200000000); //手工指定的类型优先 
```

