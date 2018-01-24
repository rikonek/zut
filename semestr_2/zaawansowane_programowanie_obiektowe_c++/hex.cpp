// Implement a function that
// works on std::vector<std::uint8_t> 
// displays all values as 0x7f____ 0xff____
// uses a lambda

#include <iostream>
#include <vector>

int main()
{
    std::vector<std::uint8_t> a {0,1,2,3,4,5,6,15,16,17,20,50,120,222,255};

    for(const auto &b: a)
    {
        auto old=std::cout.flags();
        std::cout << std::hex << "0x" << static_cast<int>(b) << std::endl;
        std::cout.setf(old);
    }

    return 0;
}