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

void huffman::debug(bool stan)
{
    debugowanie=stan;
}

std::string huffman::encode(std::ifstream &plik)
{
    if(debugowanie) cout << "Tekst do kompresji:" << endl;

    if(debugowanie) cout << plik.rdbuf() << endl << endl;
    liczZnaki(plik);
    zbudujDrzewo();

    if(debugowanie) cout << "Tworze tablice kodowa" << endl;
    utworzKod(drzewo.begin()->second,"");
    if(debugowanie) wyswietlKod();

    return zakoduj(plik);
}

void huffman::liczZnaki(std::ifstream &plik)
{
    if(debugowanie) cout << "Zliczam znaki" << endl;

    plik.clear();
    plik.seekg(0, ios::beg);
    std::map<char,int> ilosc_znakow;
    char znak;
    while(plik.get(znak))
    {
        if(ilosc_znakow[znak])
        {
            ilosc_znakow[znak]=ilosc_znakow[znak]+1;
        }
        else
        {
            ilosc_znakow[znak]=1;
        }
    }
    for(std::map<char,int>::iterator i=ilosc_znakow.begin();i!=ilosc_znakow.end();i++)
    {
        if(debugowanie) cout << (*i).first << " : " << (*i).second << endl;
        drzewo.insert(std::pair<int,lisc*>((*i).second,new lisc((*i).first,(*i).second)));
    }
    if(debugowanie) cout << endl;
}

void huffman::zbudujDrzewo()
{
    if(debugowanie) cout << "Buduje drzewo" << endl;

    lisc *lewy, *prawy, *glowa;
    while(drzewo.size()>1)
    {
        lewy=drzewo.begin()->second;
        drzewo.erase(drzewo.begin());

        prawy=drzewo.begin()->second;
        drzewo.erase(drzewo.begin());

        glowa=new lisc('|',lewy->ilosc+prawy->ilosc);
        glowa->lewy=lewy;
        glowa->prawy=prawy;
        drzewo.insert(std::pair<int,lisc*>(lewy->ilosc+prawy->ilosc,glowa));
    }
}

void huffman::utworzKod(auto &drzewo,std::string kod)
{
    if(drzewo->znak!='|')
    {
        tablica_kodowa[drzewo->znak]=kod;
    }
    if(drzewo->lewy!=NULL) utworzKod(drzewo->lewy,kod+"0");
    if(drzewo->prawy!=NULL) utworzKod(drzewo->prawy,kod+"1");
}

void huffman::wyswietlKod()
{
    for(std::map<char,string>::iterator i=tablica_kodowa.begin();i!=tablica_kodowa.end();i++)
    {
        cout << (*i).first << ": " << (*i).second << endl;
    }
}

void huffman::usunDrzewo(auto &drzewo)
{
    if(drzewo->lewy!=NULL)
    {
        usunDrzewo(drzewo->lewy);
        drzewo->lewy=NULL;
    }
    if(drzewo->prawy!=NULL)
    {
        usunDrzewo(drzewo->prawy);
        drzewo->prawy=NULL;
    }
    if(drzewo->lewy==NULL && drzewo->prawy==NULL)
    {
        delete drzewo;
    }
}

std::string huffman::zakoduj(std::ifstream &plik)
{
    if(debugowanie) cout << endl << "Tekst po kompresji:" << endl;
    plik.clear();
    plik.seekg(0, ios::beg);
    char znak;
    std::string zakodowane;
    while(plik.get(znak))
    {
        zakodowane+=tablica_kodowa[znak];
    }
    if(debugowanie) cout << zakodowane << endl;

    return zakodowane;
}

huffman::~huffman()
{
    usunDrzewo(drzewo.begin()->second);
}