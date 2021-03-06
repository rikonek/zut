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

void sortuj(std::vector<int> &tablica,int indeksL,int indeksR)
{
    if(indeksL>=indeksR) return;

    int piwot=tablica[(indeksL+indeksR)/2]; //piwot ustawiam jako srodkowy element
    int i=indeksL; //i ustawiam na poczatku zbioru
    int j=indeksR; //j ustawiam na koncu zbioru
    do
    {
        while(tablica[i]<piwot) i++; //szukam od poczatku pierwszej liczby ktora bedzie mniejsza niz piwot
        while(tablica[j]>piwot) j--; //szukam od konca pierwszej wiekszej liczby ktora bedzie wieksza niz piwot
        if(i<=j)
        {
            std::swap(tablica[i],tablica[j]); //zamieniam liczby miejscami
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>indeksL) sortuj(tablica,indeksL,j); //sortuje lewa czesc tablicy
    if(i<indeksR) sortuj(tablica,i,indeksR); //sortuje prawa czesc tablicy
}

int main()
{
    const int n=100; //ilosc elementow w tablicy

    std::vector<int> tablica(n);
    srand(time(NULL));
    std::generate(tablica.begin(),tablica.end(),[]()->int { return rand()%100; });

    cout << "Tablica wejsciowa:" << endl;
    wyswietlTab(tablica);
    cout << endl << endl;

    sortuj(tablica,0,tablica.size()-1);

    cout << "Tablica posortowana:" << endl;
    wyswietlTab(tablica);
    cout << endl;

    return 0;
}