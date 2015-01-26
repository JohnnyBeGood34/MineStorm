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
     * @brief accelerate permet au vaisseau user d'accélerer
     */
    void accelerate();
    /**
     * @brief rotate effectue une rotation du vaisseau
     */
    void rotate(string direction);
    /**
     * @brief destroy détruit le vaisseau en tracant des lignes partant de son centre
     */
    void destroy();
    /**
     * @brief slowDown ralentit le vaisseau
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
