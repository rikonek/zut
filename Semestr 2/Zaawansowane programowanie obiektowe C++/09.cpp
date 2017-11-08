#include <iostream>

template<typename T> 
void fun(T)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    int a=0;
    int& b=a;

    fun(b);

    fun(std::ref(b));
    fun(std::cref(b));
}