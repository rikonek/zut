// Write a program to revert values from an array.

#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

template<std::size_t SIZE>
void print(const std::array<int,SIZE> &tab)
{
    for(const auto &tmp: tab)
    {
        cout << tmp << ":";
    }
    cout << endl;
}

int main()
{
    std::array<int,10> a={0,1,2,3,4,5,6,7,8,9};
    std::array<int,10> b=a;

    std::reverse(b.begin(),b.end());

    print(a);
    print(b);

    return 0;
}