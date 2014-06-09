#include <iostream>
#include "mrowisko.h"
#include "world.h"
#include "globalSettings.h"

using namespace std;

World::World(int _lp, char _home, char _food, int _lpw){ 
             home=_home; food=_food; lpw=_lpw;
             punkty=new Punkt[lp=_lp];
             for(int i=0;i<lp;i++)
                 punkty[i].ferom=0.0;
             aux=new Aux[lp];
}

void World::reset(){
     for(int i=0;i<lp;i++){
         punkty[i].ferom=0.0;  

     }
}

void World::decreaseFeroms()
{
    for(int i=0;i<lp;i++) {
        punkty[i].ferom -= gs_fer_reduction_per_cycle; //(punkty[i].ferom * gs_fer_reduction_per_cycle);
        if(punkty[i].ferom < 0.f) punkty[i].ferom=0.f;
    }

}

void World::pokaz(){
     for(int i=0;i<lp;i++)
         cout<<(char)punkty[i].name<<"   "; cout<<endl;
     for(int i=0;i<lp;i++)
         cout<<punkty[i].ferom<<"   "; cout<<endl;
}
