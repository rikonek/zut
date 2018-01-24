// callback gdy w petli znajdziemy zadana wartosc

#include <iostream>
#include <functional>

void callback()
{
    std::cout << "I'm a callback function" << std::endl;
}

void find_int(5,)
{
    std::function<void()> new_f = callback;
    for(unsigned int i=0; i<40; i++)
    {
        if(i==23)
        {
            new_f();
        }
    }
}

int main()
{
    std::cout << "Callback test" << std::endl;

}