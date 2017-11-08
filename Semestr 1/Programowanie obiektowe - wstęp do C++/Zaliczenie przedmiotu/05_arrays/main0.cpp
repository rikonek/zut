// Write a program to concatenate two tables.

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
    std::array<int,10> b={9,8,7,6,5,4,3,2,1,0};
    std::array<int,a.size()+b.size()> c={0};

    std::merge(a.begin(),a.end(),b.begin(),b.end(),c.begin());

    print(a);
    print(b);
    print(c);

    return 0;
}