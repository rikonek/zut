// Implement a program that
// reads N values from command line
// reads N floating point values
// checks if values are given in ascending/descending order
// if ascending multiply, descending add

#include <iostream>
#include <vector>

int main()
{
    unsigned int number=0;
    std::vector<float> a;

    std::cout << "Enter number: ";
    std::cin >> number;
    std::cout << "Give a numbers: ";
    for(unsigned int i=0; i<number; i++)
    {
        std::cin >> a[i];
    }
    return 0;
}