// implement a clamp function that:
// has two std::vector<>(input, output), hi, lo and enum arguments
// checks if elements are less than T and if true inserts them to second container
// enum arg is: 
//     Replace // do a in place insertion
//     Clear // clear before adding
//     Append // just add
// 
// Funkcja ma kopiować z jednego wektora do drugiego wartości mniejsze niż wartość zadana "hi"

#include <iostream>
#include <vector>

enum class Flags
{
    REPLACE=0,
    CLEAR=1,
    APPEND=2
};

template<typename T>
void clamp(std::vector<T> input, std::vector<T> &output, T hi, Flags f)
{
    // if(f==1) // clear 
    if(Flags::CLEAR) std::cout << "Clear" << std::endl;
    for(const auto &tmp: input)
    {
        if(tmp<hi)
        {

        }
    }
}

int main()
{
    std::vector<int> x={2,4,6,8,10,12,14,16,18};
    std::vector<int> y;
    clamp(x,y,9,Flags::APPEND);
    for(const auto &tmp: y)
    {
        std::cout << tmp << std::endl;
    }
    return 0;
}