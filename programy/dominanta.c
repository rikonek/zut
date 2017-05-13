#include <stdio.h>
#include <time.h>

#define KOMENTARZ 1

/*
 * Losuje liczby 0-4
 * @param int n Ilosc liczb do wylosowania
 * @return int[]
 */
int losuj(int n)
{
    int tablica[n];
    int i=0;
    if(KOMENTARZ) printf("Generuje losowa tablice liczb - ilosc elementow %d\n",n);
    srand(time(NULL));
    for(;i<n;i++)
    {
        tablica[i]=rand()%5;
        if(KOMENTARZ) printf("%d,",tablica[i]);
    }
    if(KOMENTARZ) printf("\n");
    return tablica;
}

int main()
{
    int n=5;
    int *tablica; //tablica wylosowanych liczb
    int znalezione[n]; //tablica unikalnych liczb
    int znalezione_ilosc=0; //ilosc zliczonych unikalnych liczb
    int ilosc[n]; //ilosc unikalnych liczb wzgledem tablicy znalezione[]
    int jest_w_znalezionych;
    int dominanta_ilosc=0;
    int dominanta_ilosc_wystapien=0;

    int z;
    int i;

    //inicjalizuje tablice - wczesniej nie moge bo rozmiar tablicy nie jest wpisany na sztywno
    memcpy(znalezione,(int[]) {0}, sizeof(znalezione));
    memcpy(ilosc,(int[]) {0},sizeof(ilosc));

    //losuje tablice danych
    tablica=losuj(n);

    //zliczam ilosc poszczegolnych liczb
    for(i=0;i<n;i++)
    {
printf("iteracja: %d, znalezione_ilosc: %d\n",i,znalezione_ilosc);
        jest_w_znalezionych=0;
        if(znalezione_ilosc>0)
        {
            for(z=0;z<=znalezione_ilosc;z++)
            {
                if(tablica[i]==znalezione[z])
                {
                  jest_w_znalezionych=1;
                  ilosc[z]++;
    //              printf(" - Z1: %d, ilosc: %d\n",z,ilosc[z]);
                  break;
                }
            }
        }
        if(jest_w_znalezionych==0)
        {
            znalezione[znalezione_ilosc]=tablica[i];
            ilosc[znalezione_ilosc]++;
            znalezione_ilosc++;
//            printf(" - Z0: %d, ilosc: %d\n",i,tablica[i]);
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
    if(KOMENTARZ) printf("\n");
    if(dominanta_ilosc_wystapien==znalezione_ilosc)
    {
        printf("Brak dominanty");
    }
    else
    {
        printf("Znaleziono dominant: %d\n",dominanta_ilosc_wystapien);
//        printf("Ilosc powtorzen: %d\n",znalezione_ilosc);
        printf("tj.: ");
        for(i=0;i<znalezione_ilosc;i++)
        {
            if(dominanta_ilosc==ilosc[i])
            {
                printf("%d,",znalezione[i]);
            }
        }
    }

    return 1;
}
