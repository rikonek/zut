// 1. Zaimplementowac liste korzystajac z dynamicznej alokacji pamieci.
// 2. Wezel listy ma byc zdefiniowany jako:
// typedef struct List {
//   int value;
//   struct List* next;
// }
// 3. Zaimplementowac metody dostepu do listy:
// void push_back()
// int pop_front()
// - zwracana wartosc to wartosc pola value z wezla listy
// - jezeli lista jest pusta, zwracana wartosc ma wynosic -1
// 4. Stwórz pule N-watków (N>=3) z czego:
// 0-watek -> dodaje (push_back) losowe dane do listy
// <1-N) -> watki sciagaja (pop_front) dane z listy
// 5. Zidentyfikuj sekcje krytyczne w programie i odpowiednio je zabezpiecz.
// 6. Jezeli lista jest pusta, wowczas czytajace watki maja byc uspione.

#include <stdio.h>

typedef struct List
{
    int value;
    struct List *next;
} List;

void push_back(List *head,int value) //wrzucam element na koniec listy
{
    if(head==NULL)
    {
        puts("jestem tutaj");
        head=(List*)malloc(sizeof(List));
        head->value=123;
        head->next=NULL;
    }
    else
    {
        puts("Tu nie wchodze");
        List *current = head;
        while(current->next!=NULL)
        {
            current=current->next;
        }
        List *prepare=malloc(sizeof(List));
        prepare->value=value;
        prepare->next=NULL;
        current->next=prepare;
    }
}

int pop_front() //sciagam element z listy
{

}

void print_list(List *head)
{
    puts("Drukuje liste");
//    if(head==NULL) puts("Lista nie istenieje");
    List *current = head;
    while(current!=NULL)
    {
        printf("%d\n",current->value);
        current=current->next;
    }
}

int main()
{
    /*
    List *wezel=malloc(sizeof(List));
    if(wezel==NULL)
    {
        return 1;
    }
    wezel->value=NULL;
    wezel->next=NULL;
    */
    List *wezel=NULL;

/*
    wezel->value=5;
    wezel->next=NULL;
*/

    push_back(wezel,3);
    print_list(wezel);

    return 0;
}
