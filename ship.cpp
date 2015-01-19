#include "ship.h"
#include "QTransform"
#include "math.h"

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



void Ship::accelerate(int acceleration){

    QTransform transform;
        transform=transform.translate(0,-5*acceleration);
        _points=transform.map(_points);
acceleration++;
}

void Ship::rotate(){

  /* QTransform transform;
   transform=transform.rotate(5);
 _points=transform.map(_points);//Rotation appliquée ici mais pas ce que l'on veut
 */


//Ici la bonne rotation ..mais ne s'applique pas
  const int angle =10;
  int xCenter=_centerShip.x();
  int yCenter=_centerShip.y();

    for(int i =0;i<_points.size();++i){
        QPoint point=_points.at(i);

    int    x = cos(angle) *(point.x()-xCenter)-sin(angle)*(point.y()-yCenter)+xCenter;
        int y = sin(angle) *(point.x()-xCenter)+cos(angle)*(point.y()-yCenter)+yCenter;
       point.setX(x);
       point.setY(y);

    }
//_points=transform.map(_points);

}

void Ship::destroy(){
_points.clear();
}

void Ship::slowDown(){
    QTransform transform;
    transform=transform.translate(0,10);
    _points=transform.map(_points);


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
