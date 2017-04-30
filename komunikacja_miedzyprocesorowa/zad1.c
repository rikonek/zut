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
