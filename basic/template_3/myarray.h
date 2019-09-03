#pragma once
#include <iostream>

template<typename T=std::string, int size = 10>
class myarray
{
private:
	T arr[size];

public:
	void myfunc();
};

template<typename T, int size>
void myarray<T, size>::myfunc()
{
	std::cout << size << std::endl;
}