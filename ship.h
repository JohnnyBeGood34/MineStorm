#ifndef SHIP_H
#define SHIP_H
#include "weapon.h"
#include <QPolygon>


using namespace std;

class Ship
{

public:

    Ship(/*Weapon *aWeapon*/);
    ~Ship();
    QPolygon getPolygon();
    /**
     * @brief accelerate
     */
    void accelerate();
    /**
     * @brief rotate make a rotation
     */
    void rotate(string direction);
    /**
     * @brief destroy destroy the user space ship
     */
    void destroy();
    /**
     * @brief slowDown slow down the space ship
     */
    void slowDown();

    QPoint* getSommet();

    QPoint getCenter();

    Weapon* getWeapon();

    bool _isShooting;
private:
    QPolygon _points;
    int _speed;
    Weapon *_shipWeapon;
    QPoint _sommet;
    QPoint _centerShip;
};

#endif // SHIP_H
