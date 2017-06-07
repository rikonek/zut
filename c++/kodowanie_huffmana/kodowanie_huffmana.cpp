#include <iostream>
#include <fstream>
#include "huffman.class.cpp"

int main()
{
    std::ifstream plik("kodowanie_huffmana_tekst.txt");
    if(!plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku zrodlowego" << endl;
        return 1;
    }
    huffman h;
    h.debug(true);
    cout << h.encode(plik) << endl;
    plik.close();

    return 0;
}