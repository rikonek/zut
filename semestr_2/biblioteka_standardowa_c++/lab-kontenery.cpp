// implement a template function that:
// accepts a vector of T1's
// accept a number T2
// returns a vector of elements that are std::pow'ed() 

#include <iostream>
#include <vector>
#include <cmath>

template<typename T1>
auto potega(std::vector<T1> v, int i)
{
    std::vector<T1> out;
    for(static auto& tmp: v)
    {
        std::pow(tmp, i);
    }
}

int main()
{
    return 0;
}