// Write a program:
// with class hierarchy
// objects are created by a factory function depends on user input
// collect objects at a container
// call a function special for a class of a object
// print out properties of all elements

#include <iostream>
#include <memory>
#include <vector>

class fruit
{
    public:
        virtual void color() const noexcept;
};

class orange: public fruit
{
    public:
        virtual void color() const noexcept
        {
            std::cout << "orange" << std::endl;
        }
};

class lemon: public fruit
{
    public:
        virtual void color() const noexcept
        {
            std::cout << "yellow" << std::endl;
        }
};

int main()
{
    std::unique_ptr<fruit> f { std::make_unique<orange>() };
    f->color();

    return 0;
}