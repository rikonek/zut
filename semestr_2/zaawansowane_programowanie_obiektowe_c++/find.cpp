// Implement a function that
// works on std::vector<int> 
// finds all occurrences of N
// return a vector of indexes of N's

#include <iostream>
#include <algorithm>
#include <vector>

std::vector<std::size_t> find(const int &value, const std::vector<int> &v)
{
    std::vector<std::size_t> ret;
    auto iterator = std::find(v.begin(), v.end(), value);
    while(iterator != v.end())
    {
        ret.push_back(std::distance(v.begin(), iterator));
        iterator++;
        iterator = std::find(iterator, v.end(), value);
    }
    return ret;
}

int main()
{
    std::vector<int> v { 0, 1, 0, 1 };
    auto f = find(0, v);
    std::cout << f.size() << std::endl;
    return 0;
}