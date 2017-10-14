// custom Array<10,T, false>

// uses std::array or std::vector based on 2nd template parameter
// provides a typical interface (operator[], begin(), end())
// has a max()/min() method
// template_array.cpp

// dopisać testy


#include <iostream>
#include <array>
#include <vector>

template<unsigned int n, typename type, bool heap> // false - array; true - vector
class customArray
{
    private:
        std::vector<type> vec; // sterta
        std::array<type, n> tab; // stos

    public:
        // min()
        // {

        // }

        // max()
        // {

        // }
};

int main()
{
    return 0;
}