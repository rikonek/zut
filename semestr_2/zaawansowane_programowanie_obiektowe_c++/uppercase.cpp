// Implement a function that converts a string to uppercase

#include <iostream>
#include <algorithm>
#include <string>

std::string toUpper(const std::string &s)
{
    std::string buffer;
    std::transform(s.begin(), s.end(), std::back_inserter(buffer), [](auto c) {
        return std::toupper(c);
    });
    return buffer;
}

int main()
{
    std::string s="ala ma kota";
    std::cout << toUpper(s) << std::endl;
    return 0;
}