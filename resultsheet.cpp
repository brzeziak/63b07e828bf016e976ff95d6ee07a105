#include <iostream>
#include "resultsheet.h"

resultSheet::resultSheet()
{
    this->cycle=0;
    this->gAnts=0;
}

void resultSheet::recompute()
{
    data.push_back(this->cycle);
    data.push_back(this->gAnts);
}

void resultSheet::print()
{
    for(unsigned int i=0; i<data.capacity()-1; i++)
    {
        std::cout << "Cycle: " << data.at(i) << std::endl;
        std::cout << "Ants: " << data.at(i+1) << std::endl;
    }
}

void resultSheet::AddCycle()
{
    this->cycle++;
}

void resultSheet::PutAnt()
{
    this->gAnts++;
}
