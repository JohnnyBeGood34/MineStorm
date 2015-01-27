#include "mine.h"
#include <QDebug>
Mine::Mine(QPoint qPointRand, int &compteur)
{
    //qPointRand central point of a mine
    _center =qPointRand;
    //Determine the mine type (little, middle, great)
    if(compteur < 5){
        mineType = 1;
    }else if(compteur >= 5 && compteur < 25){
        mineType = 2;
    }else if(compteur >= 25 && compteur < 30){
        mineType = 3;
    }

    //Polygon initialize to a point
    _points << _center;
}

void Mine::hatch(){

    switch ( mineType ) {
        case 1:
            _x = 7.5;
            _y = 2.5;
          break;
        case 2:
            _x = 15;
            _y = 5;
          break;
        case 3:
            _x = 30;
            _y = 10;
          break;
    }

    //Create tops of mines according to the central point
    QPoint qPointSommetMine = QPoint(_center.x(),_center.y()+_x);
    QPoint qPointSommetMine2 = QPoint(_center.x()+_y,_center.y()+_y);
    QPoint qPointSommetMine3 = QPoint(_center.x()+_x,_center.y());
    QPoint qPointSommetMine4 = QPoint(_center.x()+_y,_center.y()-_y);
    QPoint qPointSommetMine5 = QPoint(_center.x(),_center.y()-_x);
    QPoint qPointSommetMine6 = QPoint(_center.x()-_y,_center.y()-_y);
    QPoint qPointSommetMine7 = QPoint(_center.x()-_x,_center.y());
    QPoint qPointSommetMine8 = QPoint(_center.x()-_y,_center.y()+_y);
    _points.clear();
    //Create the mine polygon
    _points << qPointSommetMine << qPointSommetMine2 << qPointSommetMine3 << qPointSommetMine4 << qPointSommetMine5 << qPointSommetMine6 << qPointSommetMine7 << qPointSommetMine8;

    _direction=QPoint(1,1);
}

Mine::~Mine(){
   _points.clear();//Destroy the polygon
}

int Mine::getType(){
    return mineType;
}

void Mine::destroy(){
_points.clear();
}

QPolygon Mine::getPolygon(){
    return _points;
}


QPoint* Mine::getCenter(){
    return &_center;
}

void Mine::setCenter(QPoint center){
    _center=center;
}
