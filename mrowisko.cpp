#include <stdlib.h>
#include <iostream>
#include <string>
#include <math.h>
#include "mrowisko.h"
#include "world.h"
#include "losowy.h"

#include <fstream>
#include "globalSettings.h"

using namespace std;
const float MAX=1e6; // nie spotykana odleg³oœæ miêdzy punktami

int _cykl=0;
int ant_sum=0;
float _feroms=0;

void Mrowisko::WTF(bool ferom)
{
    ofstream myfile;
    myfile.open ("data.txt", ios_base::app);

    if(myfile.is_open())
    {
        if(ferom)
            myfile << _cykl << '\t' << _feroms << '\n';
        else
            myfile << _cykl << '\t' << ant_sum << '\n';

        myfile.close();
    }
}

void Mrowisko::WNL()
{
    ofstream myfile;
    myfile.open ("data.txt", ios_base::app);
    if(myfile.is_open())
    {
        myfile << '\n';
        myfile.close();
    }
}

void Mrowka::policz_odleglosci(){
      int index=polozenie-'a';
      int dx,dy;
      for(int i=0;i<swiat->lp;i++)
       if((i==index)or(i==swiat->home-'a'))
        swiat->aux[i].ratio=MAX;
        else{
         dx=swiat->punkty[index].x-swiat->punkty[i].x;
         dy=swiat->punkty[index].y-swiat->punkty[i].y;
         swiat->aux[i].ratio=sqrt(dx*dx+dy*dy);
       } 
}
void Mrowka::sortuj_tablice_pomocnicza(){
      // wype³nia tablicê pomocmicz¹ "aux" wartoœciami "feromon/odleg³oœæ"
      for(int i=0;i<swiat->lp;i++)
       swiat->aux[i].ratio=(swiat->punkty[i].ferom+1)/swiat->aux[i].ratio;
      // sortuje tablice pomocnicz¹
      Aux bufor;
      for(int i=swiat->lp-1;i>0;i--)
       for(int j=1;j<=i;j++)
        if(swiat->aux[j].ratio>=swiat->aux[j-1].ratio){
         bufor.name=swiat->aux[j].name;
         bufor.ratio=swiat->aux[j].ratio;
         swiat->aux[j].name=swiat->aux[j-1].name;
         swiat->aux[j].ratio=swiat->aux[j-1].ratio;
         swiat->aux[j-1].name=bufor.name;
         swiat->aux[j-1].ratio=bufor.ratio;
        }
}
int Mrowka::losuj( ){
     srand(pobierz_baze());
     return rand()%swiat->lpw;
}
int Mrowka::ruletka(){
     float help[swiat->lpw];
     float suma=0;
     for(int i=0;i<swiat->lpw;i++)
      suma+=swiat->aux[i].ratio;
     for(int i=0;i<swiat->lpw;i++)
      help[i]=swiat->aux[i].ratio/suma*100;
     srand(pobierz_baze());      
     int losowa=rand()%100; 
     int i=0; suma=help[i];
     while(losowa>suma)suma+=help[++i];
     return i;
}
bool Mrowka::sprawdz_sciezke(char znak){    
     int jest=0; unsigned int i=0;
     while(not jest and(i<sciezka.size()))
         if(sciezka[i]==znak)jest=1; else i++;
     return jest;
}            
int Mrowka::wybierz_punkt() {
     for(int i=0;i<swiat->lp;i++)// resetuje tablicê pomocnicz¹
      swiat->aux[i].name=swiat->punkty[i].name;
     policz_odleglosci();
     sortuj_tablice_pomocnicza();
     int wybor; bool zly_wybor;
     do{ 
         if(gs_use_roulette)
            wybor=ruletka();// wybór przy pomocy ruletki
         else
             wybor=losuj(); // wybór przy pomocy losowania klasycznego

         zly_wybor=sprawdz_sciezke(swiat->aux[wybor].name);
       }while(zly_wybor);
     return wybor; 
}
void Mrowka::polej_sciezke(){
     for(unsigned int i=0;i<sciezka.size();i++)
         if(sciezka[i]!=swiat->home)
         {
             swiat->punkty[sciezka[i]-'a'].ferom+=(feromon*gs_fer_reduction);
            _feroms = swiat->punkty[sciezka[i]-'a'].ferom;
         }
            //swiat->punkty[sciezka[i]-'a'].ferom+=feromon;
}
void Mrowka::akcja( ){
     int index=wybierz_punkt();
     int valor=(swiat->aux[index].name!=(swiat->food))?1:0;
     switch (valor)
     { case 1: polozenie=swiat->aux[index].name;
               sciezka+=polozenie;
               break;
        case 0:
            if(gs_return_home)
            {
                polozenie=swiat->food;
                sciezka+=polozenie;
                polej_sciezke();
                sciezka="";
                polozenie=swiat->home;
                ant_sum++;
            }
            else
            {
                syta=true;
                polozenie=swiat->food;
                sciezka+=polozenie;
                polej_sciezke();
                ant_sum++;
            }
            break;
       }
}
void Mrowka::pokaz(){
     cout<<syta<<"  "+sciezka+"  "<<sciezka.size()<<"  \n";

}
Mrowisko::Mrowisko(World *_swiat, int _lmr, float _fer)
      {lmr=_lmr; ants=new Mrowka[lmr];
       losuj_baze();
       // losowanie bazy liczb losowych do losowañ po³o¿eñ mrówek
       for(int i=0;i<lmr;i++){
           Mrowka &m=ants[i];
           m.swiat=_swiat; m.syta=false;
           m.polozenie=m.swiat->home;
           m.sciezka=m.swiat->home;
           m.feromon=_fer;    }
      }
void Mrowisko::reset( ){
     for(int i=0;i<lmr;i++){
         ants[i].polozenie=ants[i].swiat->home;
         ants[i].sciezka=ants[i].swiat->home;}    
}
void Mrowisko::move( ){
     for(int i=0;i<lmr;i++)
         if(not ants[i].syta)ants[i].akcja();
}
void Mrowisko::pokaz(int cykl){
    for(int i=0;i<lmr;i++)
        ants[i].pokaz();

    _cykl=cykl;
    std::cout << "Cykl: " << _cykl << std::endl;
    std::cout << "Mrowki: " << ant_sum << std::endl;
    WTF(gs_WriteFeroms);
    _feroms=0;
    ant_sum=0;
}
