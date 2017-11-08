// Write a class containing variables type of an integer,
// string and double with all constructors, destructor, operators...
// (C++11 recommended - move semantic)

#include <iostream>

using namespace std;

class MyClass
{
    public:
        MyClass() {};
        MyClass(const int &a): i(a) {};
        MyClass(const std::string &a): s(a) {};
        MyClass(const double &a): d(a) {};
        MyClass(const int &a, const std::string &b, const double &c): i(a), s(b), d(c) {};
        void setInt(const int &a);
        void setString(const std::string &a);
        void setDouble(const double &a);
        int getInt();
        std::string getString();
        double getDouble();
        ~MyClass() {};

    private:
        int i=0;
        std::string s;
        double d=0;
};

void MyClass::setInt(const int &a)
{
    i=a;
}

void MyClass::setString(const std::string &a)
{
    s=a;
}

void MyClass::setDouble(const double &a)
{
    d=a;
}

int MyClass::getInt()
{
    return i;
}

std::string MyClass::getString()
{
    return s;
}

double MyClass::getDouble()
{
    return d;
}

int main()
{
    cout << "--- A ---" << endl;
    MyClass a;
    a.setInt(1);
    a.setString("Pierwszy");
    a.setDouble(11.11);
    cout << a.getInt() << endl;
    cout << a.getString() << endl;
    cout << a.getDouble() << endl;

    cout << "--- B ---" << endl;
    MyClass b(2);
    cout << b.getInt() << endl;

    cout << "--- C ---" << endl;
    MyClass c("Trzeci");
    cout << c.getString() << endl;

    cout << "--- D ---" << endl;
    MyClass d(4.4);
    cout << d.getDouble() << endl;

    cout << "--- E ---" << endl;
    MyClass e(5,"Piaty",5.5);
    cout << e.getInt() << endl;
    cout << e.getString() << endl;
    cout << e.getDouble() << endl;

    cout << "--- F ---" << endl;
    MyClass f=e;
    cout << f.getInt() << endl;
    cout << f.getString() << endl;
    cout << f.getDouble() << endl;

    cout << "--- G ---" << endl;
    MyClass g;
    g=a;
    cout << g.getInt() << endl;
    cout << g.getString() << endl;
    cout << g.getDouble() << endl;


    return 0;
}