// Klasyczny algorytm mrówkowy v.1.1.0
// ostatnia aktualizacja 2011-04-25
// CopyLeft Feliks Kurp 2011
#include <cstdlib>
#include <iostream>
#include "world.h"
#include "mrowisko.h"

#include "globalSettings.h"

using namespace std;
// huwhuwhuwhuwhuwhuwhuhwuwhuwhwuheuheue
// inicjacja œwiata
const int lp=7;    // liczba punktów œwiata
int tabela[3][lp]={'a','b','c','d','e','f','g',
                    6, 13,  4,  4,  8,  6,  10,
                    1,  1,  3,  5,  5,  8,  8}; 
void inicjuj(World swiat); // inicjuje konkretny œwiat

int main(int argc, char *argv[])
{
        World swiat(gs_map_points,'a','g',gs_pathselect_points);
        // parametry œwiata: liczba punktów, home, food,
        //                   liczba punktów wyboru dla mrówek

        for(int at=0; at<gs_attempts; at++)
        {
            inicjuj(swiat); // inicjacja œwiata wartoœciami
            Mrowisko m(&swiat,gs_ants,gs_fers); // parametry mrowiska: nazwa œwiata,
            // liczba mrówek, iloœæ pozostawianego feromonu przez mrówkê
            cout<<"---------- stan poczatkowy\n";
            m.pokaz(0);                // mrowisko - stan pocz¹tkowy
            swiat.pokaz(); cout<<endl;// œwiat    - stan pocz¹tkowy

            for(unsigned int i=1;i<=gs_cycles;i++){
                cout<<"---------- "<<i<<" cykl ----------\n";
                m.move(); m.pokaz(i);
                swiat.pokaz(); cout<<endl;

                swiat.decreaseFeroms();
            }

            m.WNL();

            m.reset();
            swiat.reset();
        }

      system("PAUSE");
      return EXIT_SUCCESS;
}

void inicjuj(World swiat){
     for(int i=0;i<lp;i++)
         {swiat.punkty[i].name =tabela[0][i];
          swiat.punkty[i].x    =tabela[1][i];
          swiat.punkty[i].y    =tabela[2][i];
         } 
}

