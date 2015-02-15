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
     * @brief connectSommet
     */
    void connectSommet(QPoint centerShip);
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
    void incrementSpeed();
    bool _isShooting;
    /**
     * @brief reDrawShip used to re-draw the ship whan it's out of screen
     */
    void reDrawShip(const QSize &size);
    /**
     * @brief initShip init the ship position
     */
    void initShip();
private:
    QPolygon _points;
    Weapon *_shipWeapon;
    QPoint _sommet;
    QPoint _centerShip;
    double speed;
};

#endif // SHIP_H
