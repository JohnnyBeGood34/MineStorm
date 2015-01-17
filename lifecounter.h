#ifndef LIFECOUNTER_H
#define LIFECOUNTER_H
#include "vector"
#include "memory"

class LifeCounter
{
public:
    LifeCounter();
    void decrement();
    int getLives();
private:
    int _lives=3;
    //Mettre en attribut ce qui va representer la zone...
    //Vecteur de 3 Polygones pour représenter les 3 vies de départ ?
  //  vector<unique_ptr<QPolygon>> _livesShips;

};

#endif // LIFECOUNTER_H
