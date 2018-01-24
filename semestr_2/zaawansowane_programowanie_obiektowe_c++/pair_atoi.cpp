#include <iostream>

namespace my_std
{
    std::pair<int,bool> atoi(std::string s)
    {
        if(s==0)
        {
            // return std::pair<int,bool> (0,false);
        }
        // r=std::atoi(s.c_str());
        // if(r)
        return std::pair(5,6);
    }
}

int main()
{
    std::cout << my_std::atoi("3");
    return 0;
}