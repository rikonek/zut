#include <iostream>

using namespace std;

int main()
{
    cout << "C string" << endl;

    const char* c1="tekst";
    const char* c2=c1;

    delete c1;

    cout << "C1: " << c1 << endl;
    cout << "C2: " << c2 << endl;

    cout << endl;

    cout << "C++ string" << endl;
    std::string s="abecadlo";
    std::string cs=s;
    cout << "S: " << s << endl;
    cout << "CS: " << cs << endl;
}