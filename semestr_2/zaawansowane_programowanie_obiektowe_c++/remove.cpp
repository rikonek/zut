// Implement a function that
// works on std::vector<int> 
// call std::remove() on specific value
// see what happens!

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> a {1, 2, 3, 4, 2, 5};
    auto it=std::remove(a.begin(), a.end(), 2);
    a.erase(it, a.end());

    for(int &b: a)
    {
        std::cout << b << std::endl;
    }

    return 0;
}