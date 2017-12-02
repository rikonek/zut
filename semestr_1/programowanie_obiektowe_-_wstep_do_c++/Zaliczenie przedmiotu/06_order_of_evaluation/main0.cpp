// Order of evaluation

#include <iostream>

using namespace std;

void funA(int& i)
{
    // kolejnosc ewaluacji:
    // 1. preinkrementacja
    // 2. +i
    // 3. postinkrementacja nie jest widoczna przez nadpisanie i=

    i = ++i + i++;

    // powyzszy zapis wykonuje dzialanie i=(i+1)*2,
    // chociaz mozna sie domyslac ze chodzilo o dzialanie
    // i=i+2;
 
    // i=1
    // cout << i << endl; //1
    // cout << ++i << endl; //2
    // cout << i++ << endl; //2
} 

void funB(int& i)
{
    // postinkrementacja nie jest widoczna przez nadpisanie i=
    i = i++ + 1;

    // czytelniej byloby napisac i++ lub i=i+1
}

void funC(int& i)
{
    // zachowanie nie jest okreslone
    cout << i << i++;

    // operator<<(operator<<(cout, i),   i++);
    //            <------arg1------->, <-arg2->
}

void funD(int& i)
{
    int a[i+1]={0};

    a[i] = i++; // do tablicy trafi wartosc przed inkrementacja
}

void funE(int& i)
{
    // kolejnosc ewaluacji uzalezniona od wersji kompilatora
    f(++i, ++i);
    foo(bar(), baz());
}

void funF(int& i)
{
    // kolejnosc ewaluacji uzalezniona od wersji kompilatora
    if (bar() && baz()) {}
    if (bar() || baz()) {}
}

int main()
{
    int i=1;
    // funA(i); // 4
    // funB(i); // 2
    // funC(i); // 21
    // funD(i); // w tablicy a[1]=1; po funkcji 2
    cout << i << endl;
    return 0;
}