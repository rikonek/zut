// Implement a function that
// works on a container holding a string type
// remove all strings that contains at least one number

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> a { "A1", "b", "C", "d2", "3"};

    std::remove(a.begin(), a.end(), [](std::string x) {
        for(std::string &y: x)
        {
            // isdigit
            std::cout << y;
        }
    });
    // std::remove(a.begin(), a.end(), "b");

    for(std::string &b: a)
    {
        std::cout << b << std::endl;
    }

    return 0;
}