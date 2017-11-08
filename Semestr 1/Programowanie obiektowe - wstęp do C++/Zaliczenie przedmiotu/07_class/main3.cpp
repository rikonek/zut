// When copy ctor, operator= is called?

struct MyType { 
    MyType(const MyType& rhs); 
    MyType& operator=(const MyType& rhs); 
};

int main() { 
    MyType a,b; 
    MyType c = a;   // <------ here
    b = a;
}