// Implement a function that inserts values from 1 to 10 to a list 
// - use std::generate
// - use function object
// - use lambda

#include <iostream>
#include <list>
#include <algorithm>

int gen()
{
    static int i=0;
    return ++i;
}

void insert(std::list<int> &l)
{
    std::generate(1, 10, gen);
}

int main()
{
    std::list<int> l;
    insert(l);
    return 0;
}