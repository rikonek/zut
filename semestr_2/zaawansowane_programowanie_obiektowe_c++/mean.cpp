// Implement a mean function that
// works on std::vector<int> 
// calculates mean value
// uses a lambda

#include <iostream>
#include <algorithm>
#include <vector>

float mean(const std::vector<int> &v)
{
    int sum=0;
    int iteration=0;
    std::for_each(v.begin(), v.end(), [&sum, &iteration](const int &element) {
        sum=sum+element;
        iteration++;
    });

    return static_cast<float> (sum)/iteration;
}

int main()
{
    std::vector<int> v { 4, 6, 5, 7, 15 };
    std::cout << mean(v) << std::endl;
    return 0;
}