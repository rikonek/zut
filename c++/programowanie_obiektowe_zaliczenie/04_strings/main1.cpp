//Write a program to revert a string (const char*, std::string)

#include <iostream>
#include <string>
#include <algorithm>
#include <codecvt>
#include <locale>

using namespace std;

int main()
{
    // ASCII
    std::string a="Alfabet";
    std::string b=a;

    std::reverse(b.begin(),b.end());

    cout << a << endl;
    cout << b << endl;    

    // UTF8
    std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8_conv;
    std::wstring c=L"Łódź";
    std::wstring d=c;

    std::reverse(d.begin(),d.end());

    cout << utf8_conv.to_bytes(c) << endl;
    cout << utf8_conv.to_bytes(d) << endl;

    return 0;
}