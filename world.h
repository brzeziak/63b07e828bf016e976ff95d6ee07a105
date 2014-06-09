#ifndef WORLD_H
#define WORLD_H

struct Punkt{ char name; int x; int y; float ferom;};
struct Aux{char name; float ratio;}; // struktura pomocnicza
        
class World{
      private:
      public:
        int lp;        // liczba punktów œwiata
        Punkt *punkty; // tablica punktów œwiata
        Aux *aux;      // tablica pomocnicza do obliczeñ
        char home;     // nazwa punktu mrowiska
        char food;     // nazwa punktu zawieraj¹cego pokarm
        int lpw;       // liczba punktów wyboru dla mrówek        
        World(int _lp, char _home, char _food, int _lpw);
        void reset( );
        // zeruje iloœæ foremonu we wszystkich punktach œwiata
        void pokaz( ); //
        void decreaseFeroms();
};

#endif // WORLD_H
