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

// Zadanie dodatkowe. Zadanie z lista uogolnic na wielu producentow na wielu konsumentow
//  - uzyc zwyklego unique locka i condition variable

#include <iostream>
#include <random>
#include <unistd.h>
#include <pthread.h>
// #include <semaphore.h>

using namespace std;

struct List
{
    int value;
    struct List *next;
};

List *lista=NULL;

pthread_mutex_t mutex;
pthread_cond_t cond;
// sem_t semafor;

void push_back(auto *&head,int value); //dodawanie elementu na koniec listy
int pop_front(auto *&head); //zdejmowanie elementu z poczatku listy
void *thread_server(void *arg); //funkcja dla watku producenta
void *thread_client(void *arg); //funkcja dla watku konsumenta

int main()
{
    unsigned int server_num_threads=5; //ilosc producentow
    unsigned int client_num_threads=3; //ilosc konsumentow

    if(pthread_mutex_init(&mutex,0)!=0)
    {
        perror("Nie moge utworzyc mutexa");
        exit(0);
    }
    if(pthread_cond_init(&cond,0)!=0)
    {
        perror("Nie moge utworzyc cond var");
        exit(0);
    }
    // if(sem_init(&semafor,0,0)!=0)
    // {
    //     perror("Nie moge utworzyc semafora");
    //     exit(0);
    // }

    cout << endl << "--- Tworze serwery ---" << endl;
    pthread_t server_threads[server_num_threads];
    for(unsigned int i=0;i<server_num_threads;i++)
    {
        if(pthread_create(&server_threads[i],NULL,thread_server,NULL)==0)
        {
            cout << "Serwer: " << i << " ID = " << pthread_self() << " | new thread = " << server_threads[i] << endl;
        }
        else
        {
            perror("Nie moge utworzyc serwera");
            exit(0);
        }
    }

    cout << endl << "--- Tworze klientow ---" << endl;
    pthread_t client_threads[client_num_threads];
    for(unsigned int i=0;i<client_num_threads;i++)
    {
        if(pthread_create(&client_threads[i],NULL,thread_client,NULL)==0)
        {
		    cout << "Klient: " << i << " ID = " << pthread_self() << " | new thread = " << client_threads[i] << endl;
	    }
        else
        {
		    perror("Nie moge utworzyc klienta");
            exit(0);
    	}
    }

    for(unsigned int i=0;i<server_num_threads;i++)
    {
        pthread_join(server_threads[i],NULL);
    }
    // sem_destroy(&semafor);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}

void push_back(auto *&head,int value)
{
    List *current=head;
    if(head!=NULL)
    {
        while(current->next!=NULL)
        {
            current=current->next;
        }
    }
    List *prepare=new List;
    prepare->value=value;
    prepare->next=NULL;
    if(head==NULL)
    {
        head=prepare;
    }
    else
    {
        current->next=prepare;
    }
}

int pop_front(auto *&head)
{
    if(head==NULL)
    {
        return -1;
    }
    List *current=head;
    int out=current->value;
    head=current->next;

    delete current;
    return out;
}

void *thread_server(void *arg)
{
    std::random_device rd;

	cout << "Serwer - Watek zyje id = " << pthread_self() << endl;
    int i=0;
    while(1)
    {
        int los=rd()%100;
        pthread_mutex_lock(&mutex); //poczatek sekcji krytycznej
            push_back(lista,los);
            cout << pthread_self() << " " << i << " : " << los << endl << flush;
            pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex); //koniec sekcji krytycznej
        // sem_post(&semafor);
        usleep(rd()%3000000); //usypiam watek na losowy czas
        i++;
    }
    pthread_exit(NULL);
}

void *thread_client(void *arg)
{
    std::random_device rd;
	cout << "Klient - Watek zyje id = " << pthread_self() << endl;
    while(1)
    {
        // sem_wait(&semafor);
        pthread_mutex_lock(&mutex); //poczatek sekcji krytycznej
            int value=pop_front(lista);
            if(value==-1)
            {
                cout << pthread_self() << " Lista pusta. Czekam..." << endl;
                pthread_cond_wait(&cond,&mutex);
            }
            else
            {
                cout << pthread_self() << " Zdejmuje: " << value << endl;
            }
        pthread_mutex_unlock(&mutex); //koniec sekcji krytycznej
        usleep(rd()%1000000); //usypiam watek na losowy czas
    }
    pthread_exit(NULL);
}