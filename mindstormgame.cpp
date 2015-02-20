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
    //Loop counter for hacth mine is initialize to 0
    loopCounterHatchMines = 0;

    //User space ship initialization
    _userShip=new Ship();
    //User space Ennemy ship initialization
    _EnnemyShip=new EnnemySpaceShip();
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

void MindStormGame::moveMines(int counter){
     for(auto i=0;i<=counter;++i){
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



    //Antialiasing on painter
    painter.setRenderHint(QPainter::Antialiasing);
    //Set the painter pen
    painter.setPen(thePen);
    //Fill the background of the game board
    painter.fillRect(rect, QColor(0,0,0));

    //Ennemyship appear and dispose mines only if in screen
    if(_EnnemyShip->getCenter().y() < 600){
        disposeEnnemyShip(painter);
        _EnnemyShip->move();
        //Fill mines
        disposeMines(painter);
    }
    //When Ennemy ship clear, the game start
    else{
        // Destroy ennemy ship
        _EnnemyShip->destroy();

        //Increment the loop counter to have a 5 seconds to hatch mines
        if(loopCounter <1500){
            ++loopCounter;
        }

        //Hatch each mines at 5 seconds (100 loops)
        if(loopCounter % 50 == 0){
            ++loopCounterHatchMines;
        }
        hatchMines(painter,loopCounterHatchMines);
        moveMines(loopCounterHatchMines);


        //Fill mines
        disposeMines(painter);
        //Fille user space ship
        disposeUserShip(painter);
        //Used to display lifes of user
        _lifecounter->drawLifeOnGameBoard(painter,size());
        //Used to display the score of the user
        _pointcounter->drawPointsIntoGameBoard(painter,size());

        //On event we add shot to vector of shots
        if(_userShip->_isShooting){
            _userShip->shoot(painter);
            qDebug() << "Add shot...";
        }

        //We get all shots and then we draw them
        vector<Shot>* shots=_userShip->getShots();
        qDebug() << "Nb shots : "<< shots->size();


        for(auto i=0;i<shots->size();++i){
            QTransform transform;
            auto startShot=shots->at(i).getStart();
            auto endShot=shots->at(i).getEnd();
             //Il faudrait arriver ici à récupérer les bonnes coordonnées des points ...pour l'instant X = O
            qDebug()<< "Start shot X: " << startShot.x();
            //qDebug()<< "End shot X: " << endShot->x();
            //transform = transform.translate(startShot.x()-endShot->x()*0.2,startShot->y()-endShot->y()*0.2);
            QPolygon* shot=&shots->at(i);
            //startShot->setX(startShot->x()-endShot->x()*0.2);
            //startShot->setY(startShot->y()-endShot->y()*0.2);
            //endShot->setX(startShot->x()-endShot->x()*0.2);
            //endShot->setY(startShot->y()-endShot->y()*0.2);
            //painter.drawPolygon(*shot);
            //*shot = transform.map(*shot);
             //painter.drawPolygon(*shot);
        }

        //End of game
         if(_lifecounter->getLifes() == 0 ){

             showEndofGame(painter,rect);
             pause();
         }

         //Draw explosions of mine and ship
         if(!_explosion.empty()){
             painter.drawPolygon(_explosion);
             _explosion.clear();
         }
    }
}

void MindStormGame::hatchMines(QPainter &painter, int counter){
    //Hatch each mine

    for(auto i=0;i<counter;++i){
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

void MindStormGame::disposeEnnemyShip(QPainter &painter){
    QPolygon polygon=_EnnemyShip->getPolygon();
    painter.setBrush(Qt::blue);
    painter.drawPolygon(polygon,Qt::WindingFill);
}


void MindStormGame::blastPolygon(QPoint center){
    QPoint qPoint = QPoint(center.x()+40,center.y());
    QPoint qPoint1 = QPoint(center.x(),center.y());
    QPoint qPoint2 = QPoint(center.x()+30,center.y()-30);
    QPoint qPoint3 = QPoint(center.x(),center.y());
    QPoint qPoint4 = QPoint(center.x(),center.y()-40);
    QPoint qPoint5 = QPoint(center.x(),center.y());
    QPoint qPoint6 = QPoint(center.x()-30,center.y()-30);
    QPoint qPoint7 = QPoint(center.x(),center.y());
    QPoint qPoint8 = QPoint(center.x()-40,center.y());
    QPoint qPoint9 = QPoint(center.x(),center.y());
    QPoint qPoint10 = QPoint(center.x()-30,center.y()+30);
    QPoint qPoint11 = QPoint(center.x(),center.y());
    QPoint qPoint12 = QPoint(center.x(),center.y()+40);
    QPoint qPoint13 = QPoint(center.x(),center.y());
    QPoint qPoint14 = QPoint(center.x()+30,center.y()+30);
    QPoint qPoint15 = QPoint(center.x(),center.y());
    _explosion << qPoint << qPoint1 << qPoint2 << qPoint3 << qPoint4 << qPoint5 << qPoint6 << qPoint7 << qPoint8 << qPoint9 << qPoint10 << qPoint11 << qPoint12 << qPoint13 << qPoint14 << qPoint15;
    //qDebug() << "BOOOOOMMMMMMM";
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

void MindStormGame::showEndofGame(QPainter &painter,QRect &rect)
{
    //Fill the background of the game board
    painter.fillRect(rect, QColor(0,0,0));
    //Set font
    QFont font=painter.font() ;
    font.setPointSize (32);
    painter.setFont(font);

    //Then draw it into the gameboard
    painter.drawText(QPoint((size().width()/3),(size().height()/2)),"GAME OVER");
}





void MindStormGame::disposeMines(QPainter &painter){
    //For each mines, drawing a point according
    //to its center
    for(auto i=0;i<_mines.size();++i){
        if((_mines.at(i)->getCenter()->y()) < (_EnnemyShip->getCenter().y())){
            QPointF point(_mines.at(i)->getCenter()->x(),_mines.at(i)->getCenter()->y());
            painter.drawPoint(point);
        }
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
            _userShip->destroy();
            QPoint centerShip = _userShip->getCenter();
            blastPolygon(centerShip);
            _mines.at(i)->destroy();
            //Construction center of the to blast mine
            QPoint centerMine = QPoint(_mines.at(i)->getCenter()->x(),_mines.at(i)->getCenter()->y());
            blastPolygon(centerMine);
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
    loopCounterHatchMines=0;
   _userShip=new Ship();
    //_userShip->initShip();
    buildMines();
}

void MindStormGame::initialize(){

resetPlace();
_EnnemyShip=new EnnemySpaceShip();
_lifecounter->setLifes(4);
_pointcounter->setPoint(0);

}
