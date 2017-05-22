#include <iostream>
#include <array>
#include <algorithm> //std::generator

using namespace std;

//nadpisuje operator - zeby mi wyswietlal tablice jako string
std::ostream &operator << (std::ostream &output, const std::array<int,10> &tab)
{
    for(auto element: tab)
    {
        output << element << ",";
    }
    return output;
}

int main()
{
    std::array<int,10> tab {0};
    // int max=0;

    // srand(time(NULL));
    // for(auto &tmp: tab)
    // {
    //     tmp=rand()%100;
    // }

    std::generate(tab.begin(),tab.end(),[]()->int { return rand()%100; });
    //funkcja lambda []()->int { return 0; }

    cout << tab << endl;

    // for(auto tmp: tab)
    // {
    //     if(tmp>max) max=tmp;
    // }

    const auto max=max_element(tab.begin(),tab.end());

    cout << "Najwieksza: " << *max << endl;

    return 0;
}