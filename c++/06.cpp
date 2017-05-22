#include <iostream>
#include <vector>
#include <string>

using namespace std;

//cxxopts - uzyc

int main(int argc, char* argv[])
{
    const std::vector<std::string> args(argv+1,argv+argc);

    for(const auto &a: args)
    {
        //szukam parametru pomocy, jak znajde to nie wyswietlam nic wiecej
        if(a=="-h" || a=="--help")
        {
            cout << "Usage:" << endl;
            cout << " -h | --help\tShow this help" << endl;
            cout << " -v | --verbose\tShow all arguments passed" << endl;
            cout << " -f=N\t\tCalculates N*N" << endl;
            return 0;
        }
    }
    for(const auto &a: args)
    {
        if(a=="-v" || a=="--verbose")
        {
            cout << "Arguments passed" << endl;
            for(auto tmp: args)
            {
                cout << " " << tmp << endl;
            }
        }
        if(a.substr(0,2)=="-f")
        {
            std::string cut=a.substr(3,-1);
            int output=std::atoi(cut.c_str());
            cout << "Calculates N*N: " << output*output << endl;
        }
    }

    return 0;
}