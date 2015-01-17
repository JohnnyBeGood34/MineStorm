#include "ship.h"
using namespace std;
Ship::Ship(/*Weapon *aWeapon*/) //: shipWeapon(aWeapon)
{
    //A mon avis il faudrait mettre un attribut du vaisseau qui serait le centre de ce dernier
    //Le centre du vaisseau à cet instant est 235,235, mais comment avoir ce point sans que la ligne soit tracée?
    //Rajout ici du point 231,235 et 239,235 pour voir comment ça fait
    _points << QPoint(235,220) << QPoint(231,237) << QPoint(220,250) << QPoint(250,250) << QPoint(239,237) ;

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
