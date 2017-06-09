// Producent - 3x konsument (mutex+semafor) - Lista - Producent dodaj, konsument ściąga

// Treść zadania
// 1. Zaimplementuj listę korzystając z dynamicznej alokacji pamięci.

// 2. Węzeł listy ma być zdefiniowany jako:
// typedef struct List{
// int value;
// struct * List next;
// }

// 3. zaimplementuj metody dostępu do listy:
// void push_back();
// int pop_front();
// - zwracana wartość to wartość pola value z węzła listy
// - jeżeli lista jest pusta, zwracana wartosć wynosi -1

// 4. stwórz pulę N-wątków (N >= 3) z czego:
// 0-wątek -> dodaje losowe dane do listy
// <1-N) -> wątki ściągają (pop_front) dane z listy

// 5. Zidentyfikuj sekcje krytyczne w programie i odpowiednio je zabezpiecz

// 6.Jeżeli lista jest pusta, wówczas czytające wątki mają być uśpione.

// Zadanie domowe, zadanie z lista uogolnic na wielu producentow na wielu konsumentow - uzyc zwyklego unique locka i condition variable

#include <iostream>
#include <pthread.h>

using namespace std;

struct List
{
    int value;
    struct List *next;
};

// unsigned int size(const auto *head)
// {
//     unsigned int count=0;
//     while(head)
//     {
//         count++;
//         head=head->next;
//     }
//     return count;
// }

void push_back(auto *&head,int value)
{
    List *current=head;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    List *prepare=new List;
    prepare->value=value;
    prepare->next=NULL;
    current->next=prepare;
}

int pop_front(auto *&head)
{
    if(!head) return -1;
    List *current=head;
    int out=current->value;
    head=current->next;

    delete current;
    return out;
}

// void print(const auto *head)
// {
//     while(head)
//     {
//         cout << head->value << endl;
//         head=head->next;
//     }
// }

void *thread_hello(void *arg)
{
	// cout << "Watek zyje id = " << pthread_self() << endl;
    pthread_exit(NULL);
    return NULL;
}

int main()
{
    unsigned int num_threads=5;


    List *lista=new List;
    if(lista==NULL)
    {
        return 1;
    }
    lista->value=1;
    lista->next=NULL;

    pthread_t threads[num_threads];
    for(unsigned int i=0;i<num_threads;i++)
    {
        if(pthread_create(&threads[i],NULL,thread_hello,NULL)==0)
        {
		    cout << "Tworze watek: " << i << " Main thread id = " << pthread_self() << " | new thread = " << threads[i] << endl;
	    }
        else
        {
		    cout << "Thread creation error" << endl;
    	}
        // sleep(1);
    }


    push_back(lista,2);
    push_back(lista,3);
    push_back(lista,4);
    push_back(lista,5);

    cout << "Zdejmuje: " << pop_front(lista) << endl;
    cout << "Zdejmuje: " << pop_front(lista) << endl;
    cout << "Zdejmuje: " << pop_front(lista) << endl;
    cout << "Zdejmuje: " << pop_front(lista) << endl;
    cout << "Zdejmuje: " << pop_front(lista) << endl;
    cout << "Zdejmuje: " << pop_front(lista) << endl;
    cout << "Zdejmuje: " << pop_front(lista) << endl;

    return 0;
}