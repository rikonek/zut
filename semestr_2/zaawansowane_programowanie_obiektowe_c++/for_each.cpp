// Implement for_each that prints a container
// with free function
// with predicate
// with lambda

#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

template<typename T>
void p(T &c)
{
    std::cout << "[";
    auto endIt = std::end(c);
    std::advance(endIt, -1); // endIt--;
    std::for_each(std::begin(c), endIt, [](auto val) { // zamiast auto moze byc typename T::value_type val ale w tablicy w stylu "c" nie bedzie dzialalo
        std::cout << val << ", ";
    });
    std::cout << *(endIt);
    std::cout << "]" << std::endl;
}

int main()
{
    int ac[] = { 1, 2, 3, 4, 5 };
    std::array<int, 10> a { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<std::string> vs { "a", "b", "c" };

    p(ac);
    p(a);
    p(v);
    p(vs);

    return 0;
}