#include <iostream>
#include <fstream>
#include "huffman.class.h"

int main(int argc,char **argv)
{
    std::ifstream plik(argv[1]);
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