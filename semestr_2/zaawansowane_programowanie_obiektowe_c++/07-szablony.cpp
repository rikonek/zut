#include <iostream>

// template<typename type>
// void func(type name)
// {
//     std::cout << name << std::endl;
// }

template<class type>
class myclass
{
    private:
        type s;

    public:
        alloc(type x);
}
template<class type> type myclass<type>::alloc(type x)
{
    
}

int main()
{
    func<>("hello");
    func<>(std::string("hey"));
    return 0;
}