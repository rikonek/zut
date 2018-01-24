// Implement cat program with smallest amount of code

#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    std::cout << argv[1];
    // std::cout << argv[1] << std::endl;
    std::ifstream file("cat.cpp");
    if(!file.is_open())
    {
        for(const auto &out: argv)
        {
            std::cout << out << " ";
        }
        std::cout << "ED";
        std::cout << argv[0] << std::endl;
        return 1;
    }
    std::cout << "EX";
    file.rdbuf();
    return 0;
}