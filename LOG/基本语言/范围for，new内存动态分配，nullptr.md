#  范围for，new内存动态分配，nullptr

## 一 范围for语句：用于遍历一个序列	

```c++
int v[]{ 11,12,13,14,15 };
//for (auto x : v)  //把v每个元素拷贝到x中，打印x值
for (auto &x : v) //省了拷贝这个动作，提高了系统效率
{
    std::cout << x << std::endl;
}
```

## 二 动态内存分配问题

c中，供程序使用的存储空间，有程序区，静态存储区，动态存储区

### 2.1 c++中，我们把内存进一步详细分为5个区域

（1）栈：一般函数内的局部变量都会放在这里，由编译器自动分配和释放

（2）堆：程序员malloc/new分配，用free/delete来释放。忘记释放后，系统会回收

（3）全局/静态存储区：放全局变量和静态变量static。程序结束时系统释放

（4）常量存储区：“I love China”

（5）程序代码区

### 2.2 堆和栈不同的用途和区别

（1）栈：空间是有限的。这是系统  int a = 4； 分配速度快，程序员也控制不了

（2）堆：只要不超出你实际拥有的物理内存，也在操作系统运行你能够分配的最大内存大小 之内，都可以分配给你，分配速度比栈慢，你可以随时用malloc/new来分配，free/delete 非常灵活

### 2.3 malloc/free

在c语言中，用malloc和free从堆中来分配和释放内存使用。malloc和free是函数

（1）malloc(memory allocation)：动态 内存分配

一般形式：void *malloc(int Numbytes);

Numbytes:要分配的字节数。分配成功则返回指向被分配内存的指针，分配失败则返回NULL。 void * 万能指针，可以强制转换成其他任何指针

当这段分配内存不使用的时候，你应该使用free()函数来将内存释放掉，供其他地方使用

（2）free

void free(void *FirstByte)

将之前用malloc分配的内存空间还给程序（操作系统），也就是说释放了这块内存，这样这块内存就被系统回收，并在需要的时候由系统分配出去再给其他使用

```c++
int *p = NULL; //c语言写法，NULL等价于数字0
p = (int *)malloc(sizeof(int)); //在堆中分配4个字节
if (p != NULL)
{
	//分配成功
	*p = 5;
	std::cout << *p << std::endl;
	free(p);  //释放掉，千万不要忘记
}
```

```c++
char *point = NULL;
point = (char *)malloc(100 * sizeof(char)); //100个位置
if (point != NULL)
{

    //strcpy(point, "hello world"); 
    strcpy_s(point, 100, "hello world"); //更安全，如果第三个参数size超过第二个参数 ，则报错
    std::cout << *point << std::endl;
    free(point);
}
```

```c++
int *p= (int *)malloc(100 * sizeof(int)); //在堆中分配4个字节
if (p != NULL)
{
    int *q = p;
    *q++ = 1;  //==> *(q++) --> *q = 1; q++
    *q++ = 5;
    std::cout << *p << std::endl;
    std::cout << *(p+1) << std::endl;
    free(p);
}
```

### 2.4 new和delete

是运算符（标识符）。c++中，就用new/delete分配和释放内存，不再使用malloc和free

new 一般使用格式

（1） 指针变量名 = new 类型标识符;

```c++
int *myint = new int;  //p = (int *)malloc(sizeof(int));
if (myint != NULL)
{
    *myint = 8; 
    std::cout << *myint << std::endl;
    delete myint; //释放单个myint的空间
}
```

（2） 指针变量名 = new 类型标识符(初始值);  //注意这里是圆括号括起来，表示初始值

```c++
int *myint = new int(18);  
if (myint != NULL)
{
    std::cout << *myint << std::endl;
    delete myint; //释放单个myint的空间
}
```

（3） 指针变量名 = new 类型标识符[内存单元个数]; //注意，这里是[]

```c++
int *pa = new int[100];
if (pa != NULL)
{
    int *q = pa;
    *q++ = 12; //[0] = 12
    *q++ = 18; //[1] = 18

    std::cout << *pa << std::endl;
    std::cout << *(pa + 1) << std::endl;

    //释放内存了
    delete[] pa; //释放int pa数组空间
    //new的时候我们用[],那么delete就必须用[]，[]不写数组大小
}
```

额外补充知识：

（1）配对使用，有malloc成功必然有free，有new成功必然有delete

（2）free/delete，不要重复调用

malloc/free和new/delete区别：new的时候，还会调用构造函数初始化

## 三 nullptr

c++11引入新关键字

 nullptr代表的也是空指针

使用nullptr能够避免在整数和指针之间发生混淆

```C++
char *p = NULL;
char *Q = nullptr;

std::cout << typeid(NULL).name() << std::endl; //int
std::cout << typeid(nullptr).name() << std::endl;  //nullptr
```

NULL和nullptr实际上是不同的类型

结论：对于指针的初始化，和大家以往用到的和指针有关NULL的场合，能用nullptr的大家全部用nullptr取代NULL