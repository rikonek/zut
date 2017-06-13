#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class huffman
{
    public:
        void debug(bool stan);
        std::string encode(std::ifstream &plik);
        ~huffman();

    private:
        struct lisc
        {
            char znak;
            int ilosc;
            lisc *lewy, *prawy;
            lisc(const char znak, const int ilosc): znak(znak), ilosc(ilosc)
            {
                lewy=NULL;
                prawy=NULL;
            }
        };
        bool debugowanie=0;
        std::map<char,std::string> tablica_kodowa;
        std::multimap<int,lisc*> drzewo;
        void liczZnaki(std::ifstream &plik);
        void zbudujDrzewo();
        void utworzKod(auto &drzewo,std::string kod);
        void wyswietlKod();
        void usunDrzewo(auto &drzewo);
        std::string zakoduj(std::ifstream &plik);
};

#endif