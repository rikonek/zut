// Write a program to copy a string as a const char* and std::string into another one.

#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::string a="Alfabet";
    std::string b;

    b=a;

    cout << a << endl;
    cout << b << endl;

    return 0;
}