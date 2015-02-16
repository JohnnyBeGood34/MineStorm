#include "mine.h"
#include <QDebug>
#include <QPainter>
#include <QDebug>
Mine::Mine(QPoint qPointRand, int &compteur)
{
    //Get a random direction
    int min = -30;
    int max = 30;
    int newDirection = min + (rand() % (int)(max - min + 1)) +1;
    //Set default direction on x and y for mine
    this->direction_x = newDirection;
    newDirection = min + (rand() % (int)(max - min + 1));
    this->direction_y = newDirection;

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
    qDebug() << "destruction mine ! ";
}

QPolygon Mine::getPolygon(){
    return _points;
}
/**
 * @brief Mine::move A refaire avec une direction différent pour chaque mine
 */
void Mine::move(){
    qDebug() << "move mine";
    QTransform transform;
    transform = transform.translate(this->direction_x*0.2,this->direction_y*0.2);
    _points=transform.map(_points);
    _center=transform.map(_center);
}

QPoint* Mine::getCenter(){
    return &_center;
}

void Mine::setCenter(QPoint center){
    _center=center;
}
