// Implement a function that
// works on std::vector<int> 
// find element that is closest to 0

#include <iostream>
#include <algorithm>
#include <vector>

int closeZero(const std::vector<int> &v)
{
    if(v.empty()) return 0;
    return *(std::min_element(v.begin(), v.end(), [](auto lhs, auto rhs) {
        return std::abs(lhs) < std::abs(rhs);
    }));
}

int main()
{
    std::vector<int> v { -5, -2, 0, 1, 4 };
    std::cout << closeZero(v) << std::endl;
    return 0;
}