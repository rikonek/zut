// Add operator= to the class

#include <iostream>

struct MyType
{
    MyType() {};
    MyType(const MyType& rhs) {};
};

MyType getType()
{
    return MyType{};
}

int main()
{
    MyType b; 
    MyType a={b};
    MyType c { getType() };
};