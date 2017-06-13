#include <iostream>
#include <fstream>
#include "huffman.class.h"

int main()
{
    std::ifstream plik("kodowanie_huffmana_tekst.txt");
    if(!plik.is_open())
    {
        std::cout << "Nie mozna otworzyc pliku zrodlowego" << std::endl;
        return 1;
    }
    huffman h;
    h.debug(true);
    std::cout << h.encode(plik) << std::endl;
    plik.close();

    return 0;
}