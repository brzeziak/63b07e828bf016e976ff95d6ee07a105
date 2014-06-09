#ifndef LOSOWY_H
#define LOSOWY_H
#include <time.h>
using namespace std;

// struktury i funkcje potrzebne do losowañ
const int mlc=100; // maksymalna liczba cykli w eksperymencie
const int liczba_losowan=10*mlc;
int tablica_bazowa[liczba_losowan]; int index_bazowy=0;

// Patrz dopisalem te linijke jakies 18 godzin od publikacji
// Oznaczylem ten commit jakims komentarzem i nazwa

void losuj_baze(void)
{   time_t t;
    srand((unsigned)time(&t));
    for(int i=0;i<liczba_losowan;i++)
    tablica_bazowa[i]=rand()%256 ;
}

int pobierz_baze(void)
{   return tablica_bazowa[index_bazowy++];}

#endif // LOSOWY_H
