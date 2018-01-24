// Implement a function that
// works on std::list<int> 
// inserts three random elements at the beginning of a list
// and then inserts the same list at the end. 
// list[1,2,3] => fun(list) => list[33,44,55,1,2,3,33,44,55]

#include <iostream>
#include <random>
#include <list>
#include <iterator>

void insert(std::list<int> l)
{
    std::random_device rd;
    std::cout << rd()%100 << std::endl;
    // back_inserter
    // front_inserter
    // rd()/100;
}

int main()
{
    std::list<int> l = { 1, 2, 3 };
    insert(l);
    return 0;
}