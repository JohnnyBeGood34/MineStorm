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

    //Initialize speed
    speed = 0;
    //Create tops of ship according to its center
    _sommet = QPoint(_centerShip.x(),_centerShip.y()-20);
    QPoint qPointSommetShip2 = QPoint(_centerShip.x()-10,_centerShip.y()+20);
    QPoint qPointSommetShip3 = QPoint(_centerShip.x(),_centerShip.y()+10);
    QPoint qPointSommetShip = QPoint(_centerShip.x()+10,_centerShip.y()+20);

    //Create ship Qpolygon
    _points << _sommet << qPointSommetShip2 << qPointSommetShip3 << qPointSommetShip ;
    _isShooting=false;
}

Ship::~Ship(){
    _points.clear();//Destroy the polygon of space ship
}



void Ship::accelerate(){

    QTransform transform;
    int xSommet=_sommet.x();
    int ySommet=_sommet.y();
    int xCenter=_centerShip.x();
    int yCenter=_centerShip.y();
    //qDebug() << "X center : " << xCenter << "  Ycenter : " <<yCenter;
    //qDebug() << "X Sommet : " << xSommet << "  Y Sommet : " <<ySommet;

    transform=transform.translate((xSommet-xCenter)*this->speed,(ySommet-yCenter)*this->speed);

    _points=transform.map(_points);
    _centerShip=transform.map(_centerShip);
    _sommet=transform.map(_sommet);

}

void Ship::incrementSpeed(){
    if(this->speed < 2){
        this->speed = this->speed + 0.2;
    }
}



void Ship::rotate(string direction){

    qDebug() << "Rotate ...";

    const int angle = (direction == "right") ? 5 : -5;


    int xCenter=_centerShip.x();
    int yCenter=_centerShip.y();

    QTransform trans;
    trans.translate(xCenter,yCenter);
    trans.rotate(angle);
    trans.translate(-xCenter,-yCenter);

    _points=trans.map(_points);
    _sommet=trans.map(_sommet);
    /*  for(int i =0;i<_points.size();++i){

        QPoint point=_points.at(i);

    int    x = cos(angle) *(point.x()-xCenter)-sin(angle)*(point.y()-yCenter)+xCenter;
        int y = sin(angle) *(point.x()-xCenter)+cos(angle)*(point.y()-yCenter)+yCenter;
      _points.setPoint(i,x,y);

    }
*/

}

void Ship::destroy(){
    _points.clear();
}

void Ship::slowDown(){

    this->speed = 0;
   /*if(this->speed >= 0.2){
    this->speed = this->speed - 0.2;
    }*/
}

Weapon* Ship::getWeapon(){
    return _shipWeapon;
}

QPolygon Ship::getPolygon(){
    return _points;
}

QPoint* Ship::getSommet(){
    return &_sommet;
}

QPoint Ship::getCenter(){
    return _centerShip;
}
