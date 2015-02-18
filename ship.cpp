#include "ship.h"
#include "QTransform"
#include "math.h"
#include "iostream"
#include <QDebug>
#include <QPainter>
using namespace std;

Ship::Ship(/*Weapon *aWeapon*/) //: shipWeapon(aWeapon)
{
    initShip();
    _isShooting=false;
}

void Ship::initShip(){

    //Ship center;
    _centerShip= QPoint(450,450);
    //Initialize speed 0 by default
    speed = 0;
    //Create top of ship according to its center
    _sommet = QPoint(_centerShip.x(),_centerShip.y()-20);

    //Ship body
    QPoint qPoint1 = QPoint(_centerShip.x()-10,_centerShip.y()+20);
    QPoint qPoint2 = QPoint(_centerShip.x(),_centerShip.y()+25);
    QPoint qPoint3 = QPoint(_centerShip.x()+10,_centerShip.y()+20);

    //Right reactor
    QPoint qPoint4 = QPoint(_centerShip.x()+10,_centerShip.y()+35);
    QPoint qPoint5 = QPoint(_centerShip.x()+20,_centerShip.y()+20);
    QPoint qPoint6 = QPoint(_centerShip.x()+10,_centerShip.y()-5);

    //Left reactor
    QPoint qPoint8 = QPoint(_centerShip.x()-10,_centerShip.y()-5);
    QPoint qPoint9 = QPoint(_centerShip.x()-20,_centerShip.y()+20);
    QPoint qPoint10 = QPoint(_centerShip.x()-10,_centerShip.y()+35);

    //_points << _sommet << qPoint1;
    //Create ship Qpolygon
    _points << _sommet << qPoint1 << qPoint8 << qPoint9 << qPoint10 << qPoint2 << qPoint4 << qPoint5
            << qPoint6 << qPoint3;
    //_points << _sommet << qPoint1 << qPoint8 << qPoint9 << qPoint10 << qPoint11 << qPoint1 << qPoint2 <<
      //         qPoint3 << qPoint4 << qPoint5 << qPoint6 << qPoint7 << qPoint3;
}

Ship::~Ship(){
    qDebug()<< "destructeur vaisseau";
    _points.clear();//Destroy the polygon of space ship
}

void Ship::accelerate(){

    QTransform transform;
    int xSommet=_sommet.x();
    int ySommet=_sommet.y();
    int xCenter=_centerShip.x();
    int yCenter=_centerShip.y();


    transform=transform.translate((xSommet-xCenter)*this->speed,(ySommet-yCenter)*this->speed);

    _points=transform.map(_points);
    _centerShip=transform.map(_centerShip);
    _sommet=transform.map(_sommet);

}

void Ship::incrementSpeed(){
    if(this->speed < 3){
        this->speed = this->speed + 0.5;
    }
}

void Ship::reDrawShip(const QSize &size){

    QTransform transform;
    int xSommet=_sommet.x();
    int ySommet=_sommet.y();
    int xCenter=_centerShip.x();
    int yCenter=_centerShip.y();


    //Detect if center of user ship is out of screen
    //Right side
    if(_centerShip.x() > size.width()){
        //qDebug() << "RIGHT OUT";
        transform=transform.translate(xSommet-xCenter-size.width(),ySommet-yCenter);
    }
    //Left side
    else if(_centerShip.x() < 0){
        //qDebug() << "LEFT OUT";
        transform=transform.translate(xSommet-xCenter+size.width(),ySommet-yCenter);
    }
    //Top side
    else if(_centerShip.y() > size.height()){
        transform=transform.translate(xSommet-xCenter,ySommet-yCenter-size.height());
    }
    //Bottom side
    else if(_centerShip.y() < 0){
        transform=transform.translate(xSommet-xCenter,ySommet-yCenter+size.height());
    }
    //Map the polygon
    _points=transform.map(_points);
    _centerShip=transform.map(_centerShip);
    _sommet=transform.map(_sommet);
}

void Ship::rotate(string direction){

    qDebug() << "Rotate ...";

    const int angle = (direction == "right") ? 10 : -10;


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

void Ship::shoot(QPainter &painter){


            auto center=_centerShip;
            QPoint shotStart=QPoint(_sommet.x(),_sommet.y());
            QPoint shotEnd(_sommet.x()+_sommet.x()-center.x(),_sommet.y()+(_sommet.y()-center.y()));

          painter.drawLine(shotStart.x(),shotStart.y(),shotEnd.x(),shotEnd.y());
           /* QTransform trans;
            trans.translate(0,-3);

                    shotStart=trans.map(shotStart);
                     shotEnd=trans.map(shotEnd);
                     painter.drawLine(shotStart.x(),shotStart.y(),shotEnd.x(),shotEnd.y());
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
