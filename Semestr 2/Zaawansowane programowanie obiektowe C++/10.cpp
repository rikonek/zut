// Provide a operator<< that can work on any std::vector

#include <iostream>
#include <vector>

template<typename T>
std::ostream &operator << (std::ostream &output, const std::vector<T> &tab)
{
    for(auto element: tab)
    {
        output << element;
    }
    return output;
}

int main()
{
    std::vector<int> i;
    // std::vector<char> c;
    // std::vector<std::string> s;

    std::cout << "hello" << std::endl;
    std::cout << i << std::endl;
    // std::cout << c << std::endl;
    // std::cout << s << std::endl;
}