#include "mine.h"

Mine::Mine(QPoint qPointRand)
{
    //qPointRand point central donné par le rand() du mindstormgame

    //Création des sommet de la mine en fonction du Qpoint central
    QPoint qPointSommetMine = QPoint(qPointRand.x(),qPointRand.y()+30);
    QPoint qPointSommetMine2 = QPoint(qPointRand.x()+10,qPointRand.y()+10);
    QPoint qPointSommetMine3 = QPoint(qPointRand.x()+30,qPointRand.y());
    QPoint qPointSommetMine4 = QPoint(qPointRand.x()+10,qPointRand.y()-10);
    QPoint qPointSommetMine5 = QPoint(qPointRand.x(),qPointRand.y()-30);
    QPoint qPointSommetMine6 = QPoint(qPointRand.x()-10,qPointRand.y()-10);
    QPoint qPointSommetMine7 = QPoint(qPointRand.x()-30,qPointRand.y());
    QPoint qPointSommetMine8 = QPoint(qPointRand.x()-10,qPointRand.y()+10);

    //Création du QPolygon de la mine
    _points << qPointSommetMine << qPointSommetMine2 << qPointSommetMine3 << qPointSommetMine4 << qPointSommetMine5 << qPointSommetMine6 << qPointSommetMine7 << qPointSommetMine8;
}

Mine::~Mine(){
   _points.clear();//On détruit le polygone à la destruction de la mine
}

QPolygon Mine::getPolygon(){
    return _points;
}
