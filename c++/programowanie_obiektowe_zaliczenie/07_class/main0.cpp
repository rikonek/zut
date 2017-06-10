// Why it doesn't compile.
// Fix it....

#include <iostream>

struct MyType
{
    MyType() {};
    MyType(const MyType &t) {};
};

int main()
{
    MyType a;
}