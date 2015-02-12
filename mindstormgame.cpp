#include "mindstormgame.h"
#include <QPainter>
#include <QRect>
#include <QColor>
#include <QDebug>
#include <stdlib.h>
#include <memory>

using namespace std;
//Define the pen used to draw all elements in the game
QPen thePen;
MindStormGame::MindStormGame(const QSize &size,QObject *parent):Game(size,parent) {

    //Initialize the pen
    thePen.setColor(Qt::blue);
    thePen.setStyle(Qt::SolidLine);
    thePen.setWidth(2);
    //Loop counter is initialize to 0
    loopCounter = 0;
    //User space ship initialization
    _userShip=new Ship();
    //Build mines
    for(auto i=0;i<30;++i){
        auto x = rand() %size.width();
        auto y = rand() %size.height();
        //Add a mine in mines vector
        _mines.push_back(new Mine(QPoint(x,y),i));
        //_mines.push_back(make_unique<Mine>(QPoint(x,y),i));
    }
    //QObject::connect(&_timerMines,SIGNAL(timeout()),this,SLOT(test()));
}

void MindStormGame::draw(QPainter &painter, QRect &rect){
    //Increment the loop counter to have a 5 seconds
    if(loopCounter <100){
        ++loopCounter;
    }
    //Set the painter pen
    painter.setPen(thePen);
    //Fill the background of the game board
    painter.fillRect(rect, QColor(0,0,0));
    //Fill mines
    disposeMines(painter);
    //Fille user space ship
    disposeUserShip(painter);
    //Shoot tests
    if(_userShip->_isShooting){
        auto xSommet=_userShip->getSommet()->x();
        auto ySommet=_userShip->getSommet()->y();
        auto center=_userShip->getCenter();
        painter.drawLine(xSommet,ySommet,xSommet+(xSommet-center.x()),ySommet+(ySommet-center.y()));
        qDebug() << "Shooting...";
        //qDebug() << "x Center :"<< center.x() << "  y Center : " <<center.y();
    }

    //Hatch each mines at 5 seconds (100 loops)
    if(loopCounter == 100){
        hatchMines(painter);
        }

}

void MindStormGame::hatchMines(QPainter &painter){
    //Hatch each mine
    for(auto i=0;i<_mines.size();++i){

            //"Remove" the center point by drawing the point in black
            thePen.setColor(Qt::black);
            painter.setPen(thePen);
            QPointF point(_mines.at(i)->getCenter()->x(),_mines.at(i)->getCenter()->y());
            painter.drawPoint(point);
            //Then hatch mines in blue
            thePen.setColor(Qt::blue);
            painter.setPen(thePen);
            _mines.at(i)->hatch();
            painter.drawPolygon(_mines.at(i)->getPolygon());


    }
}

void MindStormGame::disposeUserShip(QPainter &painter){
    QPolygon polygon=_userShip->getPolygon();
    painter.drawPolygon(polygon);

}


void MindStormGame::mousePressed( int x, int y){

}

void MindStormGame::keyPressed( int key ){
    qDebug() << "KEY PRESSED " << key;
    switch(key) {
        case Qt::Key_Up: _userShip->incrementSpeed();
            break;
        case Qt::Key_Down: _userShip->slowDown();
            break;
        case Qt::Key_Left: _userShip->rotate("left");
            break;
        case Qt::Key_Right: _userShip->rotate("right");
            break;
        case Qt::Key_Space:_userShip->_isShooting=true;
            break;
        default:
            break;
    }

}

void MindStormGame::disposeMines(QPainter &painter){
    //For each mines, drawing a point according
    //to its center, maybe need to make a sleep..
    for(auto i=0;i<_mines.size();++i){
        QPointF point(_mines.at(i)->getCenter()->x(),_mines.at(i)->getCenter()->y());
        painter.drawPoint(point);
    }

}


void MindStormGame::keyReleased( QKeyEvent * event){

    switch(event->key()) {
    case Qt::Key_Up:
        qDebug() << "KEY UP...";
        //If the event handled isn't an autorepeat event
        //Decelerate the ship
        if(!event->isAutoRepeat()){
            _userShip->slowDown();
        }
        break;
    case Qt::Key_Space:_userShip->_isShooting=false;//End of shots
        break;
    }
}

void MindStormGame::step(){
  /*   const int min = -10;
    const int max = 10;

      for(auto i=0;i<_mines.size();++i){

        //int direction = min + (rand()%(max-min));

        //Il faut utiliser un vecteur de mines
        // initialiser chaque mine avec une direction constante (QPoint) au hasard
        //et l'appliquer ici
        int x=(_mines.at(i).x())+1;
              _mines.at(i).setX(x);
        int y=(_mines.at(i).y())+1;
              _mines.at(i).setY(y);
        if(collision(x,y)== true){
            //LifeCounter.decrement();
        }

    }
*/
    //version vector de Mines

    for(auto i=0;i<_mines.size();++i){
        int xD=_mines.at(i)->_direction.x();
        int yD=_mines.at(i)->_direction.y();


        QPolygon poly=_mines.at(i)->getPolygon();
        for(auto j=0;j<poly.size();++j){
            int x=poly.at(j).x();
            int y=poly.at(j).y();
            poly.setPoint(j,x+xD,y+yD);
        }
    }

    _userShip->accelerate();
}

bool MindStormGame::collision(int x, int y)
{
    bool retour = false;
    //Collision test between ship and mines
    if(_userShip->getPolygon().containsPoint(QPoint(x,y),Qt::OddEvenFill)){
        _userShip->destroy();//At this time the space ship disapear
        //Plz add the mine destruction

        retour = true;
    }
    return retour;
}




void MindStormGame::initialize(){
    _mines.clear();
    _userShip->destroy();

}
