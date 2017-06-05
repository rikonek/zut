#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> //malloc

#define POKAZ_KOMENTARZ 1

/*
 * Losuje liczby 0-4
 * @param int n Ilosc liczb do wylosowania
 * @return int[]
 */
int *losuj(int n)
{
    int *tablica=malloc(sizeof(int) * n);
    int i=0;

    //inicjalizuje tablice wartoscia 0
    memset(tablica,0,sizeof(tablica));

    if(POKAZ_KOMENTARZ) printf("Generuje losowa tablice liczb - ilosc elementow %d\n",n);
    srand(time(NULL));
    for(;i<n;i++)
    {
        tablica[i]=rand()%10; //losuje liczby z zakresu 0-9
        if(POKAZ_KOMENTARZ) printf("%d ",tablica[i]);
    }
    if(POKAZ_KOMENTARZ) printf("\n\n");
    return tablica;
}

int main()
{
    int n=100;
    int *ptablica; //tablica wylosowanych liczb
    int znalezione[n]; //tablica unikalnych liczb
    int znalezione_ilosc=0; //ilosc zliczonych unikalnych liczb
    int ilosc[n]; //ilosc unikalnych liczb wzgledem tablicy znalezione[]
    int jest_w_znalezionych;
    int dominanta_ilosc=0;
    int dominanta_ilosc_wystapien=0;

    int z;
    int i;

    //inicjalizuje tablice - wczesniej nie moge bo rozmiar tablicy nie jest wpisany na sztywno
    memset(znalezione,0,sizeof(znalezione));
    memset(ilosc,0,sizeof(ilosc));

    //losuje tablice danych
    ptablica=losuj(n);

    //zliczam ilosc poszczegolnych liczb
    for(i=0;i<n;i++)
    {
        jest_w_znalezionych=0;
        for(z=0;z<=znalezione_ilosc;z++)
        {
            if(*(ptablica+i)==znalezione[z])
            {
                jest_w_znalezionych=1;
                ilosc[z]++;

                //jezeli liczba=0 i ilosc=1 to zwieksz znalezione_ilosc - potrzebne bo tablica jest domyslnie wypelniona 0
                if(*(ptablica+i)==0 && ilosc[z]==1)
                {
                    znalezione_ilosc++;
                }
                break;
            }
        }
        if(jest_w_znalezionych==0)
        {
            znalezione[znalezione_ilosc]=*(ptablica+i);
            ilosc[znalezione_ilosc]++;
            znalezione_ilosc++;
        }
    }
    if(POKAZ_KOMENTARZ)
    {
        printf("Znalezione liczby:\n");
        for(i=0;i<znalezione_ilosc;i++)
        {
            printf("Liczba: %d, ilosc wystapien: %d\n",znalezione[i],ilosc[i]);
        }
    }

    //zliczam ilosc dominant
    for(i=0;i<znalezione_ilosc;i++)
    {
        if(i==0)
        {
            dominanta_ilosc=ilosc[i];
            dominanta_ilosc_wystapien=1;
        }
        else
        {
            if(dominanta_ilosc==ilosc[i])
            {
                dominanta_ilosc_wystapien++;
            }
            else
            {
                if(dominanta_ilosc<ilosc[i])
                {
                    dominanta_ilosc=ilosc[i];
                    dominanta_ilosc_wystapien=1;
                }
            }
        }
    }

    //wyswietlam dominanty
    if(POKAZ_KOMENTARZ) printf("\n");
    if(dominanta_ilosc_wystapien==znalezione_ilosc)
    {
        printf("Brak dominanty\n");
    }
    else
    {
        printf("Znaleziono dominant: %d\n",dominanta_ilosc_wystapien);
        for(i=0;i<znalezione_ilosc;i++)
        {
            if(dominanta_ilosc==ilosc[i])
            {
                printf(" - Dominanta: %d, ilosc wystapien: %d\n",znalezione[i],ilosc[i]);
            }
        }
        printf("\n");
    }

    return 1;
}
