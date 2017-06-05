#include <iostream>
// #include <list>
// #include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class huffmann
{
    public:
        std::string encode(std::ifstream &plik);

    private:
        struct lisc
        {
            char znak;
            int ilosc;
            lisc(){}
            lisc(const char z, int i) : znak(z), ilosc(i) {}
            void print() const
            {
                cout << "\t" << znak << " " << ilosc << endl;
            }
            bool operator < (const lisc &str) const // operator potrzebny do sortowania
            {
                return (ilosc<str.ilosc);
            }
        };

        struct galaz
        {
            char znak;
            int ilosc;
            struct galaz &lewy, &prawy, &rodzic;
            // galaz(){}
            // galaz(const int z, int i)
        };

        void wyswietlListe(const auto &l);
        void liczZnaki(std::ifstream &plik, auto &l);
        void dodajZnakDoListy(auto &l, char znak);
        bool fsortujListe(const auto &a, const auto &b);
        void sortujListe(auto &l);
        void zbudujDrzewo(const auto &l);
};

std::string huffmann::encode(std::ifstream &plik)
{
    std::list<lisc> lista;
    std::list<galaz> drzewo;

    if(POKAZ_KOMENTARZ) cout << "Przygotowuje plik do kodowania" << endl;
    liczZnaki(plik,lista);
    sortujListe(lista);
    zbudujDrzewo(drzewo);
    return "a";
}

void huffmann::wyswietlListe(const auto &l)
{
    for(auto e=l.begin();e!=l.end();e++)
    {
        e->print();
    }
}

void huffmann::liczZnaki(std::ifstream &plik, auto &l)
{
    char znak;
    if(POKAZ_KOMENTARZ) cout << " - Zliczam wystepujace znaki" << endl;
    while(plik.get(znak))
    {
        dodajZnakDoListy(l,znak);
    }
    if(POKAZ_KOMENTARZ) wyswietlListe(l);
}

void huffmann::dodajZnakDoListy(auto &l, char znak)
{
    bool znaleziono=0;

    for(auto e=l.begin();e!=l.end();e++)
    {
        if(e->znak==znak)
        {
            e->ilosc=e->ilosc+1;
            znaleziono=1;
        }
    }
    if(!znaleziono)
    {
        // lisc e;
        // e.znak=znak;
        // e.ilosc=1;
        // lista.push_back(e);
        l.push_back(lisc(znak,1));
    }
}

bool huffmann::fsortujListe(const auto &a, const auto &b)
{
    return a.ilosc < b.ilosc;
}

void huffmann::sortujListe(auto &l)
{
    if(POKAZ_KOMENTARZ) cout << " - Sortuje liste" << endl;
    l.sort();
    if(POKAZ_KOMENTARZ) wyswietlListe(l);
}

void huffmann::zbudujDrzewo(const auto &l)
{
    if(POKAZ_KOMENTARZ) cout << " - Buduje drzewo" << endl;

}