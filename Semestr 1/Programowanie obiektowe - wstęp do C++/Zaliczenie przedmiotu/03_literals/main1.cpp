//Write a function to compare two numbers of float. Add unit tests to check if its right.

#include <iostream>
#include <cmath>
#include <limits>

/*
 * Pyta uzytkownika o liczbe
 * @param std::string opis Wyswietla podany opis przy wprowadzaniu danych
 * @return float
 */
float podajLiczbe(std::string opis)
{
    float liczba;
    std::cout << "Podaj liczbe " << opis << ": ";
    std::cin >> liczba;
    return liczba;
}

/*
 * Sprawdza czy liczby sa identyczne
 * @param float x
 * @param float y
 * @return bool True jezeli sa identyczne
 */
bool takieSame(float &x, float &y)
{
    return std::fabs(x-y) < std::numeric_limits<float>::epsilon();
}

/*
 * Sprawdza czy parametry sa true
 * @param bool takieSame
 * @param bool warunek
 * @return bool
 */
bool test(bool takieSame, bool warunek)
{
    if(takieSame==warunek)
    {
        std::cout << "x == y == " << warunek << std::endl;
        return true;
    }
    std::cout << "X != Y != " << warunek << std::endl;
    return false;
}

int main()
{
    float x, y;
    x=podajLiczbe("x");
    y=podajLiczbe("y");

    test(takieSame(x,y),true);

    return 0;
}