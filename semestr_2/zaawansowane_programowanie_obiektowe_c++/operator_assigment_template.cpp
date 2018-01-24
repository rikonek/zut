// finish "C" class by adding assigment and move assigment operators

#include <iostream>
#include <cstring>
#include <utility>

template <typename T>
class C {
public:
    // assignment operator a=b=c=d
    C& operator=(const C& mystring)
    {
        std::cout << "C& operator assignment" << std::endl;
        if(this != &mystring)
        {
            if(size != mystring.size)
            {
                delete [] size;
                size=mystring.size;
                table=new T[size];
                strcpy(table, mystring.table);
            }
        }
        return *this;
    }

    // move assignment operator
    C& operator=(C&& mystring) noexcept
    {
        std::cout << "C&& operator move assignment" << std::endl;
        if(this != &mystring)
        {
            delete [] table;
            std::cout << "XXX: " << mystring.table << std::endl;
            table = std::exchange(mystring.table, nullptr);
            std::cout << "YYY: " << mystring.table << std::endl;
        }
        return *this;
    }

    C(T* data, size_t data_size) {
        table = new T[data_size];
        strcpy(table, data);
        size = data_size;
    }

    ~C() {
        delete [] table;
    }

    T* getTable() {
        return table;
    }

    size_t getSize() {
        return size;
    }

private:
public:
    T* table;
    size_t size;
};

int main()
{
    auto a=new C<char>("abecadlo", strlen("abecadlo"));
    std::cout << a->getTable() << std::endl;
    std::cout << a->getSize() << std::endl;
    std::cout << &a->table << std::endl;

    auto b=new C<char>("frytki", strlen("frytki"));
    b=a;
    std::cout << b->getTable() << std::endl;
    std::cout << b->getSize() << std::endl;
    std::cout << &b->table << std::endl;

    auto c=new C<char>("ketchup", strlen("ketchup"));
    c=std::move(b);
    std::cout << c->getTable() << std::endl;
    std::cout << c->getSize() << std::endl;
    std::cout << &c->table << std::endl;
    return 0;
}