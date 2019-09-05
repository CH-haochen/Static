#include "ca.h"

//“显式实例化”  手段中的 “实例化定义”，这种实例化定义只需要在一个.cpp文件中写就可以
template A<float>;  //编译器遇到这段代码就直接 实例化处理一个 A<float>

void mfunc()
{
	A<float> a(1, 2);
}