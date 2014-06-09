#ifndef MROWISKO_H
#define MROWISKO_H
#include <string>
#include "world.h"

using namespace std;



class Mrowka{
      private:
        void policz_odleglosci();
        // liczy odlegloœci od aktualnego po³o¿enia do pozosta³ych
        // punktów (oprócz w³asnego i mrowiska)
        void sortuj_tablice_pomocnicza();
        // zapisuje w tablicy "aux" wartoœci
        // ilorazów "feromon/odleg³oœæ" dla punktów
        // a nastêpnie sortuje je rosn¹co
        bool sprawdz_sciezke(char znak);
        // sprawdza, czy w sciezce wystêpuje podany znak
        int losuj(); // losuje kolejne po³o¿enie mrówki
        int ruletka();
        // wybiera metod¹ ruletki kolejne po³o¿enie mrówki
      public:
        World *swiat; 
        // wskazanie œwiata, do którego nale¿y mrówka
        char polozenie;
        float feromon; // iloœæ pozostawianego feromonu w punkcie
        bool syta;
        string sciezka;
        int wybierz_punkt(); // zwraca index kolejnego punktu
        void akcja();
        // sprawdza, czy mrówka osi¹gnê³a pokarm,
        // jeœli NIE - dopisuje osi¹gniêty punkt do jej œcie¿ki
        // jeœli TAK - dodaje do ka¿dego punktu  na œcie¿ce feromon,
        //             i "usypia" mrówkê za pomoc¹ "syta=true" 
        void polej_sciezke();
        // akcja wykonywana na punktach œwiata nale¿¹cych
        // do œcie¿ki tej mrówki, która dosz³a do pokarmu
        void pokaz();
};

class Mrowisko{
      private:
        int lmr;            // liczba mrówek w mrowisku
        Mrowka *ants;       // tablica mrówek
        string min_sciezka; // œcie¿ka minimalna
      public:
        Mrowisko(World *_swiat, int _lmr, float _fer);
        // mrowisko tworzy spo³ecznoœæ mrówek w okreœlonym œwiecie
        void reset();
        // ustawia wszystkie mrówki w po³o¿eniu home,
        // zeruje ich œcie¿ki i iloœæ foremonu w punktach
        void move();    
        // w ka¿dym cyklu przesuwa wszystkie mrówki do kolejnych punktów, 
        // najlepeszych z trzech losowo (lub za pomoc¹ ruletki) wybranych,
        // po przesuniêciu wykonuje na ka¿dej mrówce metodê "akcja" 
        // z klasy Mrówka
        void pokaz(int cykl);
        void WTF(bool ferom);
        void WNL();
        void resetFerom();
};        
        

#endif // MROWISKO_H        
