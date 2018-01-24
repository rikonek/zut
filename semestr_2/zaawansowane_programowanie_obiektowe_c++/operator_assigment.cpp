// finish "C" class by adding assigment and move assigment operators

#include <iostream>
#include <cstring>

class C {
public:
    // assignment operator a=b=c=d
    // C& operator=(const C& mystring)
    // {
    //   if(this != &mystring)
    //   {
      
    //   }
    //   return *this;
    // }

    // move assignment operator
    // C& operator=(C&& mystring) noexcept
    // {
    //   if(this != &mystring)
    //   {
    //   
    //   }
    //   return;
    // }

    C(char* text) {
        table = new char[strlen(text) + 1];
        strcpy(table, text);
    }

    ~C() {
        delete table;
    }

    char* getStr() {
        return table;
    }

private:
    char* table;
};

int main()
{
    auto a=new C("abecadlo");
    std::cout << a->getStr() << std::endl;

    auto b=new C("frytki");
    b=a;
    std::cout << b->getStr() << std::endl;
    return 0;
}