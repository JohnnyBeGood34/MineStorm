#include "ship.h"
using namespace std;
Ship::Ship(/*Weapon *aWeapon*/) //: shipWeapon(aWeapon)
{
    //Centre du vaisseau
    QPoint qPointCenterShip = QPoint(235,235);

    //Création des sommet ddu vaisseau en fonction du Qpoint central
    QPoint qPointSommetShip = QPoint(qPointCenterShip.x(),qPointCenterShip.y()-20);
    QPoint qPointSommetShip2 = QPoint(qPointCenterShip.x()-10,qPointCenterShip.y()+20);
    QPoint qPointSommetShip3 = QPoint(qPointCenterShip.x(),qPointCenterShip.y()+10);
    QPoint qPointSommetShip4 = QPoint(qPointCenterShip.x()+10,qPointCenterShip.y()+20);

    //Création du QPolygon du vaisseau
    _points << qPointSommetShip << qPointSommetShip2 << qPointSommetShip3 << qPointSommetShip4 ;
}

Ship::~Ship(){
   _points.clear();//On détruit le polygone à la destruction du vaisseau
}

QPolygon Ship::getPolygon(){
    return _points;
}

void Ship::accelerate(){

}

void Ship::rotate(){

}

void Ship::destroy(){

}

void Ship::slowDown(){

}
