// compare std::list and std::vector performance:

// test1: add 1 000 000 elements via push_back (ints, float and some big structure)
// test2: find specified value
// test3: insert at random position
// use std::chrono's time capturing mechanisms

#include <iostream>
#include <list>
#include <vector>
#include <chrono> 



int main()
{
    unsigned long int i;
    std::list<int> l_i;
    std::vector<int> v_i;

    auto l_start = std::chrono::system_clock::now();
    i=0;
    while(i<1000000)
    {
        l_i.push_back(i);
        i++;
    }
    auto l_end = std::chrono::system_clock::now();
    auto l_elapsed = l_end - l_start;
    std::cout << l_elapsed.count() << '\n';

    auto v_start = std::chrono::system_clock::now();
    i=0;
    while(i<1000000)
    {
        v_i.push_back(i);
        i++;
    }
    auto v_end = std::chrono::system_clock::now();
    auto v_elapsed = v_end - v_start;
    std::cout << v_elapsed.count() << '\n';
}