#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Animal
{
    public:
        virtual void eat() const noexcept
        {
            cout << "Cat eats a food" << endl;
        }
};

class Cat: public Animal
{
    public:
        void eat() const noexcept
        {
            cout << "I'm a cat and eating a rat." << endl;
        }
};

class HouseCat: public Cat
{
    public:
        void eat() const noexcept
        {
            Cat::eat();
            cout << "House cat eats home food." << endl;
        }
};

void f()
{
    unique_ptr<Animal> a { make_unique<HouseCat>() };
    // Animal* a = new HouseCat();
    a->eat();
}

int main()
{
    f();
}