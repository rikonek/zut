// Implement a function that
// works on std::vector<std::string> 
// replaces all lowercase string with "bummer"

#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>

int main()
{
    std::vector<std::string> v={"Alfabet", "Bagietka", "cegla", "DRZEWO", "fenikS"};
    std::vector<std::string> x;

    std::transform(v.begin(), v.end(), std::back_inserter(x), [](std::string a){
        if(std::all_of(a.begin(), a.end(), [](std::string b){
            for(const auto &c: b)
            {
                
            }
            return std::islower(b);
        }))
        {
            return a;
        }
        // for(const auto &b: a)
        // {
        //     std::is_lower(b)
        // }
    });

    for(std::string &y: v)
    {
        std::cout << "Old: " << y << std::endl;
    }
    for(std::string &y: x)
    {
        std::cout << "New: " << y << std::endl;
    }

    return 0;
}