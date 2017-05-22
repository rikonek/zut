#include <iostream>

using namespace std;

void rozmiar(int *t)
{
    cout << "Ilosc w funkcji: " << sizeof(t)/sizeof(int) << endl;
}

int main() {
    int tabl[]={1,2,3,4};
    int size=sizeof(tabl)/sizeof(int);
    cout << "Ilosc: " << sizeof(tabl)/sizeof(int) << endl;
    rozmiar(tabl);
}