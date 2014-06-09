#ifndef RESULTSHEET_H
#define RESULTSHEET_H
#include <vector>

class resultSheet
{
private:
    std::vector<int> data; // %2==0 for gAnts
     int cycle;
     int gAnts;

    public:
        void recompute();
        void print();
        resultSheet();
        void AddCycle();
        void PutAnt();

};

#endif // RESULTSHEET_H
