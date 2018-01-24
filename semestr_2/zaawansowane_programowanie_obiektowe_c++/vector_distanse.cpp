// Implement a function that
// works on std::vector<int> 
// finds a value in container and prints the index of the value

#include <iostream>
#include <vector>
#include <algorithm>

int find_index(std::vector<int> v, int element)
{
    const auto i = std::find(v.begin(), v.end(), element);

    if(i != v.end())
    {
        int index=std::distance(v.begin(), i);
        return index;
    }
    else
    {
        return -1;
    }    
}

int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(8);
    v.push_back(12);
    v.push_back(20);

    const auto i = std::find(v.begin(), v.end(), 8);

    if(i != v.end())
    {
        int index=std::distance(v.begin(), i);
        std::cout << "Find index: " << index << std::endl;
    }
    else
    {
        std::cout << "No element" << std::endl;
    }
    return 0;
}