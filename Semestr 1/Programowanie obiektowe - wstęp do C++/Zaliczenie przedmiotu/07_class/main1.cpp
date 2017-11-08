// Why it doesn't compile.
// Fix it....

#include <iostream>

struct MyType
{
    MyType() {};
    MyType(const MyType &rhs) {};
    MyType(MyType &rsh) {};
};

MyType getType()
{
    return MyType{};
}

int main()
{
    MyType b;
    MyType a {b}; //silne typowanie
    /*
    bool b=t;
    bool b {t}; //zabronione, silne typowanie wymaga w tym przypadku true/false
    */
    MyType c { getType() };
}