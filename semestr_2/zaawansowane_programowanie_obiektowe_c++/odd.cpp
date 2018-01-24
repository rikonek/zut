// Implement a function that 
// works on std::vector<int> 
// counts odd elements

#include <iostream>
#include <algorithm>
#include <vector>

int odd(std::vector<int> v)
{
    int num_items = std::count_if(v.begin(), v.end(), [](int i) {
        return i%2==0;
    });
    return num_items;
}

int main()
{
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7 };
    std::cout << odd(v) << std::endl;
    return 0;
}