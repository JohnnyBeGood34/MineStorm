#include "ship.h"
#include "QTransform"
#include "math.h"
#include "iostream"
#include <QDebug>
#include <QPainter>
using namespace std;

Ship::Ship(/*Weapon *aWeapon*/) //: shipWeapon(aWeapon)
{
    //Centre du vaisseau
   _centerShip= QPoint(235,235);

    //Création des sommet du vaisseau en fonction du Qpoint central
    _sommet = QPoint(_centerShip.x(),_centerShip.y()-20);
    QPoint qPointSommetShip2 = QPoint(_centerShip.x()-10,_centerShip.y()+20);
    QPoint qPointSommetShip3 = QPoint(_centerShip.x(),_centerShip.y()+10);
    QPoint qPointSommetShip = QPoint(_centerShip.x()+10,_centerShip.y()+20);

    //Création du QPolygon du vaisseau
    _points << _sommet << qPointSommetShip2 << qPointSommetShip3 << qPointSommetShip ;

}

Ship::~Ship(){
   _points.clear();//On détruit le polygone à la destruction du vaisseau
}



void Ship::accelerate(){

         QTransform transform;
         int xSommet=_sommet.x();
         int ySommet=_sommet.y();
         int xCenter=_centerShip.x();
         int yCenter=_centerShip.y();
         qDebug() << "X center : " << xCenter << "  Ycenter : " <<yCenter;

        transform=transform.translate(xSommet/xCenter,(ySommet/yCenter));


        _points=transform.map(_points);
        _centerShip=transform.map(_centerShip);

}

void Ship::rotate(string direction){

    qDebug() << "Rotate ...";

  const int angle = (direction == "right") ? -5 : 5;

  int xCenter=_centerShip.x();
  int yCenter=_centerShip.y();

    for(int i =0;i<_points.size();++i){

        QPoint point=_points.at(i);

    int    x = cos(angle) *(point.x()-xCenter)-sin(angle)*(point.y()-yCenter)+xCenter;
        int y = sin(angle) *(point.x()-xCenter)+cos(angle)*(point.y()-yCenter)+yCenter;
      _points.setPoint(i,x,y);

    }

}

void Ship::destroy(){
_points.clear();
}

void Ship::slowDown(){

    QTransform transform;
    transform=transform.translate(0,10);
    _points=transform.map(_points);
_centerShip=transform.map(_centerShip);
}

Weapon* Ship::getWeapon(){
    return _shipWeapon;
}

QPolygon Ship::getPolygon(){
    return _points;
}

QPoint Ship::getSommet(){
    return _sommet;
}

QPoint Ship::getCenter(){
    return _centerShip;
}
