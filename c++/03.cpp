#include <iostream>
#include <array>

using namespace std;

void rozmiar(std::array<int, 4> t)
{
    cout << "Ilosc w funkcji: " << t.size() << endl;
}

int main() {
    std:array<int,4> tabl {1,2,3,4};
    cout << "Ilosc: " << tabl.size() << endl;
    rozmiar(tabl);
}