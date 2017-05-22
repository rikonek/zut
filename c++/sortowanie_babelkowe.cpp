#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

template <std::size_t SIZE>
void wyswietlTab(std::array<int,SIZE> &tablica)
{
    for(const auto &out: tablica)
    {
        cout << out << ",";
    }
}

int main()
{
    const int n=100; //ilosc elementow w tablicy
    int zmiana=0; //zmienna pomocnicza do przechowywania informacji o zmianie podczas sortowania

    std::array<int,n> tablica {0};
    srand(time(NULL));
    std::generate(tablica.begin(),tablica.end(),[]()->int { return rand()%100; });

    cout << "Tablica wejsciowa:" << endl;
    wyswietlTab(tablica);
    cout << endl << endl;

    do
    {
        zmiana=0;
        for(int i=0;i<(n-1);i++)
        {
            if(tablica[i]>tablica[i+1])
            {
                zmiana=1;
                std::swap(tablica[i],tablica[i+1]);
            }
        }
    }
    while(zmiana!=0);

    cout << "Tablica posortowana:" << endl;
    wyswietlTab(tablica);
    cout << endl;

    return 0;
}