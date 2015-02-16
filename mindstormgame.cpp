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
    buildMines();
    _lifecounter = new LifeCounter();
    _pointcounter = new PointsCounter();
    //connect(minesTimer,SIGNAL(timeout()),this,SLOT(test()));
    //minesTimer->start(1000);
}

void MindStormGame::test(){
    qDebug() << "signal test ...";
}

void MindStormGame::moveMines(){
    for(auto i=0;i<_mines.size();++i){
        _mines.at(i)->move();
    }
}

void MindStormGame::buildMines(){

    for(auto i=0;i<30;++i){
        auto x = rand() %size().width();
        auto y = rand() %size().height();
        //Add a mine in mines vector
        _mines.push_back(new Mine(QPoint(x,y),i));
        //_mines.push_back(make_unique<Mine>(QPoint(x,y),i));
    }
}

void MindStormGame::draw(QPainter &painter, QRect &rect){

    //Increment the loop counter to have a 5 seconds to hatch mines
    if(loopCounter <100){
        ++loopCounter;
    }

    //Antialiasing on painter
    painter.setRenderHint(QPainter::Antialiasing);
    //Set the painter pen
    painter.setPen(thePen);
    //Fill the background of the game board
    painter.fillRect(rect, QColor(0,0,0));
    //Hatch each mines at 5 seconds (100 loops)
    if(loopCounter == 100){
        hatchMines(painter);
        moveMines();
    }
    //Fill mines
    disposeMines(painter);
    //Fille user space ship
    disposeUserShip(painter);
    //Used to display lifes of user
    _lifecounter->drawLifeOnGameBoard(painter,size());
    //Used to display the score of the user
    _pointcounter->drawPointsIntoGameBoard(painter,size());

    //Shoot tests
    if(_userShip->_isShooting){

        _userShip->shoot(painter);
        qDebug() << "Shooting...";
    }

    //End of game
     if(_lifecounter->getLifes() == 0 ){
         showEndofGame(painter);
         pause();
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
        _mines.at(i)->reDrawMine(size());


    }
}

void MindStormGame::disposeUserShip(QPainter &painter){
    QPolygon polygon=_userShip->getPolygon();
    painter.setBrush(Qt::blue);
    painter.drawPolygon(polygon,Qt::WindingFill);
    _userShip->reDrawShip(size());
}


void MindStormGame::blastPolygon(QPolygon polygon){

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

void MindStormGame::showEndofGame(QPainter &painter)
{
    //Set font
    QFont font=painter.font() ;
    font.setPointSize (32);
    painter.setFont(font);

    //Then draw it into the gameboard
    painter.drawText(QPoint((size().width()/2),(size().height()/2)),"GAME OVER");
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
        if(hasCollision(poly)){
            qDebug() << "Collision";
            //blastPolygon(_userShip->getPolygon());
            _userShip->destroy();
            _mines.at(i)->destroy();
            //Decrement the life number
            _lifecounter->decrement();
            //Init the ship
            //_userShip->initShip();
             resetPlace();
        }
    }

    _userShip->accelerate();
}

bool MindStormGame::hasCollision(QPolygon mine)
{
    bool retour = false;
    //Collision test between ship and mines
    QPolygon intersection=_userShip->getPolygon().intersected(QPolygon(mine));
    if(!intersection.isEmpty()){
        retour = true;
    }
    return retour;
}


void MindStormGame::resetPlace(){
    _mines.clear();
    _userShip=nullptr;
    loopCounter=0;
   _userShip=new Ship();
    //_userShip->initShip();
    buildMines();
}

void MindStormGame::initialize(){

resetPlace();
_lifecounter->setLifes(4);
_pointcounter->setPoint(0);

}
