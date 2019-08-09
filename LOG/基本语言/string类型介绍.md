# string类型介绍

## 一 简介

## 二 stirng类型简介

c++标准库中的类型，代表一个可变长字符串

string这个类型，看成一个类类型（类似于struct）

char str[100] = "I love China"; //c语言用法

## 三 定义和初始化string对象

```c++
std::string s1; //默认初始化、s1 = ""；""空串，表示里面没有字符
std::string s2 = "I love China"; //把 I love China这个字符串拷贝到了s2代表的一段内存中。拷贝时不包括末尾的\0
std::string s3("I love China"); //跟s2的写法效果 一样
std::string s4 = s2; //把s2的内容拷贝到了s4所代表的一段内存中

int num = 6;
std::string s5(num, 'a'); //aaaaaa。这种方式不太推荐，因为徽章系统内部创建临时对象
```

## 四 string对象上的操作

（a）判断是否为空empty()，

返回布尔值

（b）size()/length()

返回字节/字符数量 代表改字符串的长度。unsigned int

（c）s[n] 

返回s中的第n个字符(n是个整型值)，n代表的是一个位置，位置从0开始，到.size()-1

如果用下标n超过这个范围的内容，或者本来就是一个空字符串，也用s[n]访问，会产生不可预测的结果

（d）s1+s2 

字符串的连接，返回连接后的结果，得到一个新的string对象

（e）s1 = s2 

字符串对象赋值，用s2里面的内容取代原来s1里面的内容

（f）s1 == s2 

判断连个字符串是否相等。大小写敏感。相等：长度相同，字符全相同

（g）s1 != s2 

判断字符串是否不相等

（h）s.c_str() 

返回一个字符串s中的内容指针。返回一个指向正规c字符串的指针常量，也就是以\0结尾的

这个函数的引入是为了与c语言兼容，在c语言中没有string类型，所以我们得通过string类对象的c_str()成员函数把string对象转换成c语言中的字符串格式

（i）读写string对象

```c++
stirng s1;
cin >> s1;
cout << s1;
```

（j）字面值和string相加

```c++
std::string s1 = "abc";
std::string s2 = "adsf";
std::string s3 = s1 + " and " + s2;

std::string s4 = "abc" + "def"; //语法上不允许
std::string s5 = "abc" + s1 + "def"; //中间夹一个string对象，语法上就允许
std::string s5 = "abc" +  "def" + s1; //错误，两个字符串不能挨着相加，否则就会语法报错
```

（k）范围for针对string的使用

```c++
// string 可以看成是一个字符序列
std::string s1 = "I love China";
for (auto &c : s1)
{
    std::cout << c << std::endl;
}
```

