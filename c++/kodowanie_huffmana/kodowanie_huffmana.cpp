#include <iostream>
#include <vector>
#include <fstream>
// #include <ext/slist>
#include <list>
#include <algorithm> //find_if
// #include <bitset>
// #include <climits>

#define POKAZ_KOMENTARZ 1
#include "huffmann.class.cpp"


using namespace std;
// namespace listy=__gnu_cxx;

// static std::vector<int> unikalne_znaki(255);

static std::vector<int> ilosc_wystapien;

struct unikalny_znak
{
    char znak;
    int ilosc;
};
static std::list<unikalny_znak> lista;
static std::list<unikalny_znak> drzewo;

// std::string wczytajPlik(std::string sciezka)
// {
//     std::ifstream plik(sciezka);
//     if(!plik.is_open())
//     {
//         cout << "Nie mozna otworzyc pliku zrodlowego" << endl;
//         return "";
//     }

//     return sciezka;
// }

struct znajdzZnak // : std::unary_function<unikalny_znak,char>
{
    char znak;
    znajdzZnak(char znak):znak(znak) {}
    bool operator()(const unikalny_znak &e)
    {
        return e.znak==znak;
    }
};

struct znajdzMinimum
{
    bool operator()(const auto &a, const auto &b) const
    {
        return a.ilosc < b.ilosc;
    }
};

void wyswietlTab(std::vector<int> &tablica)
{
    for(const auto &out: tablica)
    {
        cout << out << ",";
    }
}

bool porownaj(const auto &a, const auto &b)
{
    return a.ilosc < b.ilosc;
}

struct sortujListe
{
    bool operator()(const auto &a, const auto &b) const
    {
        return a.ilosc < b.ilosc;
    }
};

bool fsortujListe(const auto &a, const auto &b)
{
    return a.ilosc < b.ilosc;
}

void sortujTablice()
{
    // std::sort(lista.begin(),lista.end(),sortujListe());
    // std::sort(lista.begin(),lista.end());
    // lista.sort(&porownaj);
    // lista.sort(fsortujListe);
    for(auto element=lista.begin();element!=lista.end();element++)
    {
        cout << "Element: " << element->znak << " " << element->ilosc << endl;
    }
}

void tablicaWystapien()
{
    cout << "Wyswietlam tablice" << endl;
    wyswietlTab(ilosc_wystapien);
    for(auto e=lista.begin();e!=lista.end();e++)
    {
        // cout << e->ilosc << endl;
        ilosc_wystapien.push_back(e->ilosc);
    }
    std::sort(ilosc_wystapien.begin(),ilosc_wystapien.end());
    cout << "Wyswietlam po sortowaniu" << endl;
    wyswietlTab(ilosc_wystapien);
}

void znajdzMin()
{
    for(auto element=lista.begin();element!=lista.end();element++)
    {
        cout << "Element: " << element->znak << " " << element->ilosc << endl;
    }
}

void zbudujDrzewo()
{
    // tablicaWystapien();
    // unikalny_znak *abc=std::min_element(lista.begin(),lista.end(),znajdzMin());
    auto it=std::min_element(lista.begin(),lista.end(),znajdzMinimum()); //[](const auto &a,const auto &b) {return a.ilosc < b.ilosc;}
    cout << "Min: " << it->znak << ":" << it->ilosc << endl;
    // lista.remove(it);
    for(auto e=lista.begin();e!=lista.end();e++)
    {
        // if(e->znak==znak)
        // {
        //     e->ilosc=e->ilosc+1;
        //     znaleziono=1;
        // }
    }
    // for(const auto &e: unikalne_znaki)
    // {
        // element.znak=znak;
        // element.ilosc=1;
        // lista.push_back(element);
    // }

    // cout << "Probuje usunac litere " << it->znak << endl;
    // for(auto element=lista.begin();element!=lista.end();element++)
    // {
    //     cout << "Element: " << element->znak << " " << element->ilosc << endl;
    // }
}

int main()
{
    // h=new huffmann;
    // std::fstream plik;
    // plik.open("kodowanie_huffmana_tekst.txt",std::ios::in);
    std::ifstream plik("kodowanie_huffmana_tekst.txt");
    if(!plik.is_open())
    {
        cout << "Nie mozna otworzyc pliku zrodlowego" << endl;
        return 1;
    }
    huffmann h;
    h.encode(plik);

    // wczytajPlik("kodowanie_huffmana_tekst.txt");

    // char znak;
    // while(plik.get(znak))
    // {
    //     cout << znak << endl;
    // }

    return 0;
}