#include "ship.h"

Ship::Ship()
{

    _points << QPoint(235,220) << QPoint(220,250) << QPoint(250,250) ;

}

Ship::~Ship(){
   _points.clear();//On détruit le polygone à la destruction du vaisseau
}

QPolygon Ship::getPolygon(){
    return _points;
}
