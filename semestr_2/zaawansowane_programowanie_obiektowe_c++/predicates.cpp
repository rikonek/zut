// Implement a function that inserts values from 1 to 10 to a list 
// use function object
// use std::generate

// std::vector<int> v; 
// std::generate(b, e, how_many, Pred() -> int);

#include <iostream>
#include <algorithm>
#include <list>

struct myGen
{
    int operator()()
    {
        return ++counter;
    }

    int counter {0};
};

std::list<int> foo()
{
    std::list<int> my_list;

    // 1
    my_list.resize(10);
    std::generate(my_list.begin(), my_list.end(), myGen());

    // 2
    // std::generate_n(std::back_inserter(my_list), 10, myGen);

    // 3 lambda
    // int counter=0;
    // std::generate_n(std::back_inserter(my_list), 10, [&counter]() {
    //     return ++counter;
    // });

    return my_list;
}

int main()
{
    foo();
    return 0;
}