#ifndef SHIP_H
#define SHIP_H
#include "weapon.h"
#include <QPolygon>
#include <QPainter>

using namespace std;
/**
 * @brief The Ship class, represents the User Ship
 */
class Ship
{

public:
    /**
     * @brief Ship Constructor
     */
    Ship(/*Weapon *aWeapon*/);
    /**
     * @brief ~Ship Destructor
     */
    ~Ship();
    /**
     * @brief getPolygon, used to get the Ship polygon
     * @return QPolygon
     */
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
    /**
     * @brief getSommet, get QPoint sommet
     * @return QPoint
     */
    QPoint* getSommet();
    /**
     * @brief getCenter, get the QPoint center of the ship
     * @return QPoint
     */
    QPoint getCenter();

    Weapon* getWeapon();


    bool getIsShooting();

    void setIsShooting(bool result);
    /**
     * @brief incrementSpeed, used to increment ship speed
     */
    void incrementSpeed();
    /**
     * @brief shoot, used to make a shot
     */
    void shoot(/*QPainter &painter*/);
    /**
     * @brief reDrawShip used to re-draw the ship whan it's out of screen
     */
    void reDrawShip(const QSize &size);
    /**
     * @brief initShip init the ship position
     */
    void initShip();
private:
    /**
     * @brief _points, represents the QPolygon of the ship
     */
    QPolygon _points;
    /**
     * @brief _shipWeapon
     */
    Weapon *_shipWeapon;
    /**
     * @brief _sommet QPoint, sommet of ship
     */
    QPoint _sommet;
    /**
     * @brief _centerShip, QPoint, center ship
     */
    QPoint _centerShip;
    /**
     * @brief speed, ship speed
     */
    double speed;
    bool _isShooting;
};

#endif // SHIP_H
