// Implement a function that
// works on a container
// returns smallest odd and smallest even number

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

void minimum(std::vector<int> &a)
{
    auto it=std::partition(a.begin(), a.end(), [](int i){ return i%2==0; });

// make_pair
// std::min_element
    // std::cout << it << std::endl;
    std::copy(std::begin(a), it, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::copy(it, std::end(a), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}

int main()
{
    std::vector<int> a { 9, 4, 7, 8, 2, 4, 6, 2, 1, 8 };
    minimum(a);

    return 0;
}