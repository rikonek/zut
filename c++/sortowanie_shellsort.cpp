#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void wyswietlTab(std::vector<int> &tablica)
{
    for(const auto &out: tablica)
    {
        cout << out << ",";
    }
}

void sortuj(std::vector<int> &tablica)
{
    unsigned int podzial,i,j;
    for(podzial=tablica.size()/2; podzial>0; podzial=podzial/2) //ustawiam punkt podzialu tablicy
    {
        for(i=podzial; i<tablica.size(); i++) //wykonuje iteracje tablicy od punktu podzialu do konca
        {
            /*
                wykorzystuje indeks pomocniczy "j" do iteracji w dol
                jezeli wartosc poprzednia (j-podzial) jest wieksza od wartosci biezacej (j) to dokonuje zamiany miejsc i zmieniam indeks (j) na (j-podzial)
            */
            for(j=i; j>=podzial && tablica[j-podzial]>tablica[j]; j=j-podzial)
            {
                std::swap(tablica[j],tablica[j-podzial]);
            }
        }
    }
}

int main()
{
    const int n=10000; //ilosc elementow w tablicy

    std::vector<int> tablica(n);
    srand(time(NULL));
    std::generate(tablica.begin(),tablica.end(),[]()->int { return rand()%100; });

    cout << "Tablica wejsciowa:" << endl;
    wyswietlTab(tablica);
    cout << endl << endl;

    sortuj(tablica);

    cout << "Tablica posortowana:" << endl;
    wyswietlTab(tablica);
    cout << endl;

    return 0;
}