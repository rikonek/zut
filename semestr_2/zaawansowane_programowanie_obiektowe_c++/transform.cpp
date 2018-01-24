// Implement a function that
// works on std::vector<int> 
// replaces all value with abs(value) in the same container

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v={-1, -2, -3, -4};
    std::vector<int> x;

    std::transform(v.begin(), v.end(), std::back_inserter(x), [](int a){ return std::abs(a); });

    for(int &y: v)
    {
        std::cout << "Old: " << y << std::endl;
    }
    for(int &y: x)
    {
        std::cout << "New: " << y << std::endl;
    }

    return 0;
}