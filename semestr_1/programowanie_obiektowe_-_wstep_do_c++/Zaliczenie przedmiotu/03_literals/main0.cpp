//Write a program to get a number and display it in dec oct hex val.

#include <iostream>

int podajLiczbe()
{
    int liczba;
    std::cout << "Podaj liczbe: ";
    std::cin >> liczba;
    return liczba;
}

int main()
{
    int liczba=podajLiczbe();

    std::cout << "Podana liczba to odpowiednio:" << std::endl;
    std::cout << "- Dec: " << std::dec << liczba << std::endl;
    std::cout << "- Oct: " << std::oct << liczba << std::endl;
    std::cout << "- Hex: " << std::hex << liczba << std::endl;

    return 0;
}