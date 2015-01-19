#include "mine.h"

Mine::Mine(QPoint qPointRand)
{
    //qPointRand point central donné par le rand() du mindstormgame
    _center =qPointRand;

    //choix rand() pour la taille des mines
    _mineType mineTypeRand = static_cast<_mineType>(rand() % Num_Count);

    //switch case permettant d'affecter la dimension pour les mines mais toujours ce probleme de tremblement.....
    switch ( mineTypeRand ) {
        case small:
            _x = 7.5;
            _y = 2.5;
          break;
        case meduim:
            _x = 15;
            _y = 5;
          break;
        case large:
            _x = 30;
            _y = 10;
          break;
    }

    //Création des sommet de la mine en fonction du Qpoint central
    QPoint qPointSommetMine = QPoint(qPointRand.x(),qPointRand.y()+_x);
    QPoint qPointSommetMine2 = QPoint(qPointRand.x()+_y,qPointRand.y()+_y);
    QPoint qPointSommetMine3 = QPoint(qPointRand.x()+_x,qPointRand.y());
    QPoint qPointSommetMine4 = QPoint(qPointRand.x()+_y,qPointRand.y()-_y);
    QPoint qPointSommetMine5 = QPoint(qPointRand.x(),qPointRand.y()-_x);
    QPoint qPointSommetMine6 = QPoint(qPointRand.x()-_y,qPointRand.y()-_y);
    QPoint qPointSommetMine7 = QPoint(qPointRand.x()-_x,qPointRand.y());
    QPoint qPointSommetMine8 = QPoint(qPointRand.x()-_y,qPointRand.y()+_y);

    //Création du QPolygon de la mine
    _points << qPointSommetMine << qPointSommetMine2 << qPointSommetMine3 << qPointSommetMine4 << qPointSommetMine5 << qPointSommetMine6 << qPointSommetMine7 << qPointSommetMine8;
}

Mine::~Mine(){
   _points.clear();//On détruit le polygone à la destruction de la mine
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
