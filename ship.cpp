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
    _centerShip= QPoint(300,300);
    //Initialize speed 0 by default
    speed = 0;
    //Create top of ship according to its center
    _sommet = QPoint(_centerShip.x(),_centerShip.y()-35);

    QPoint qPoint1 = QPoint(_centerShip.x()+10,_centerShip.y());
    QPoint qPoint2 = QPoint(_centerShip.x()+15,_centerShip.y());
    QPoint qPoint3 = QPoint(_centerShip.x()+15,_centerShip.y()-15);
    QPoint qPoint4 = QPoint(_centerShip.x()+15,_centerShip.y());
    QPoint qPoint5 = QPoint(_centerShip.x()+20,_centerShip.y());
    QPoint qPoint6 = QPoint(_centerShip.x()+20,_centerShip.y()-10);
    QPoint qPoint7 = QPoint(_centerShip.x()+25,_centerShip.y()-10);
    QPoint qPoint8 = QPoint(_centerShip.x()+25,_centerShip.y()-30);
    QPoint qPoint9 = QPoint(_centerShip.x()+25,_centerShip.y()-10);
    QPoint qPoint10 = QPoint(_centerShip.x()+30,_centerShip.y()-10);
    QPoint qPoint11 = QPoint(_centerShip.x()+30,_centerShip.y()+10);
    QPoint qPoint12 = QPoint(_centerShip.x()+20,_centerShip.y()+10);
    QPoint qPoint13 = QPoint(_centerShip.x()+20,_centerShip.y()+5);
    QPoint qPoint14 = QPoint(_centerShip.x()+10,_centerShip.y()+10);
    QPoint qPoint15 = QPoint(_centerShip.x()+10,_centerShip.y()+15);
    QPoint qPoint16 = QPoint(_centerShip.x()+5,_centerShip.y()+15);
    QPoint qPoint17 = QPoint(_centerShip.x()+5,_centerShip.y()+10);
    QPoint qPoint18 = QPoint(_centerShip.x()-5,_centerShip.y()+10);
    QPoint qPoint19 = QPoint(_centerShip.x()-5,_centerShip.y()+15);
    QPoint qPoint20 = QPoint(_centerShip.x()-10,_centerShip.y()+15);
    QPoint qPoint21 = QPoint(_centerShip.x()-10,_centerShip.y()+10);
    QPoint qPoint22 = QPoint(_centerShip.x()-20,_centerShip.y()+5);
    QPoint qPoint23 = QPoint(_centerShip.x()-20,_centerShip.y()+10);
    QPoint qPoint24 = QPoint(_centerShip.x()-30,_centerShip.y()+10);
    QPoint qPoint25 = QPoint(_centerShip.x()-30,_centerShip.y()-10);
    QPoint qPoint26 = QPoint(_centerShip.x()-25,_centerShip.y()-10);
    QPoint qPoint27 = QPoint(_centerShip.x()-25,_centerShip.y()-30);
    QPoint qPoint28 = QPoint(_centerShip.x()-25,_centerShip.y()-10);
    QPoint qPoint29 = QPoint(_centerShip.x()-20,_centerShip.y()-10);
    QPoint qPoint30 = QPoint(_centerShip.x()-20,_centerShip.y());
    QPoint qPoint31 = QPoint(_centerShip.x()-15,_centerShip.y());
    QPoint qPoint32 = QPoint(_centerShip.x()-15,_centerShip.y()-15);
    QPoint qPoint33 = QPoint(_centerShip.x()-15,_centerShip.y());
    QPoint qPoint34 = QPoint(_centerShip.x()-10,_centerShip.y());
    QPoint qPoint35 = QPoint(_centerShip.x(),_centerShip.y()-35);


    _points << _sommet << qPoint1 << qPoint2 << qPoint3 << qPoint4 << qPoint5 << qPoint6 << qPoint7 << qPoint8 << qPoint9 << qPoint10
                                  << qPoint11 << qPoint12 << qPoint13 << qPoint14 << qPoint15 << qPoint16 << qPoint17 << qPoint18 << qPoint19 << qPoint20
                                     << qPoint21 << qPoint22 << qPoint23 << qPoint24 << qPoint25 << qPoint26 << qPoint27 << qPoint28 << qPoint29 << qPoint30
                                        << qPoint31 << qPoint32 << qPoint33 << qPoint34 << qPoint35;
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

    //qDebug() << "Rotate ...";

    const int angle = (direction == "right") ? 15 : -15;


    int xCenter=_centerShip.x();
    int yCenter=_centerShip.y();

    QTransform trans;
    trans.translate(xCenter,yCenter);
    trans.rotate(angle);
    trans.translate(-xCenter,-yCenter);

    _points=trans.map(_points);
    _sommet=trans.map(_sommet);

    /*int i=0;
    foreach (QPoint point, _points) {

        int x = cos(angle)*(point.x()-xCenter) - sin(angle)*(point.y()-yCenter) + xCenter;
        int y = sin(angle)*(point.x()-xCenter) + cos(angle)*(point.y()-yCenter) + yCenter;
        _points.setPoint(i,x,y);
        ++i;
    }*/
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

