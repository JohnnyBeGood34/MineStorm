#include "mindstormgame.h"
#include <QPainter>
#include <QRect>
#include <QColor>
#include <QDebug>

using namespace std;


MindStormGame::MindStormGame(const QSize &size,QObject *parent):Game(size,parent) {

    _userShip=new Ship();//initialisation du vaisseau

    for(auto i=0;i<30;++i){

        auto x = rand() %600;//remplacer par taille du jeu : size().width()
        auto y = rand() %600;
        //_mines.push_back(QPoint(x,y));
        _mines.push_back(new Mine(QPoint(x,y)));
    }
_timerMines.start(1000);
 QObject::connect(&_timerMines,SIGNAL(timeout()),this,SLOT(test()));
}

void MindStormGame::test(){
    qDebug() << "test connect ....";
}

void MindStormGame::draw(QPainter &painter, QRect &rect){
     //TESTS TIRS
if(_userShip->_isShooting){
        auto xSommet=_userShip->getSommet()->x();
       auto ySommet=_userShip->getSommet()->y();
       auto center=_userShip->getCenter();
      painter.drawLine(xSommet,ySommet,xSommet+(xSommet-center.x()),ySommet+(ySommet-center.y()));
       qDebug() << "Shooting...";
       qDebug() << "x Center :"<< center.x() << "  y Center : " <<center.y();
}

}


void MindStormGame::disposeUserShip(QPainter &painter){

    QPen pen(Qt::blue, 2, Qt::SolidLine);

    painter.setPen(pen);

    QPolygon polygon=_userShip->getPolygon();

    painter.drawPolygon(polygon);

}


void MindStormGame::mousePressed( int x, int y){

}

void MindStormGame::keyPressed( int key ){

    switch(key) {
    case Qt::Key_Up: _userShip->accelerate();
        break;
    case Qt::Key_Down: _userShip->slowDown();
        break;
    case Qt::Key_Left: _userShip->rotate("left");
        break;
    case Qt::Key_Right: _userShip->rotate("right");
        break;
    case Qt::Key_Space:_userShip->_isShooting=true;//Tirs du vaisseau
        break;
    }

}

void MindStormGame::disposeMines(QPainter &painter){
/*
>>>>>>> 364b8a3109a2a707289fde8411f97748bbff803b
   for(auto i=0;i<_mines.size();++i){
            //initialisation de la mine
             _computerMine=new Mine(_mines.at(i));
             QPolygon polygonMine=_computerMine->getPolygon();
             painter.drawPolygon(polygonMine);
         }
*/

    //version vecteur de Mines

    for(auto i=0;i<_mines.size();++i){

        painter.drawPolygon(_mines.at(i)->getPolygon());
    }

}


void MindStormGame::keyReleased( int key ){


    switch(key) {

    case Qt::Key_Space:_userShip->_isShooting=false;//Tirs du vaisseau
        break;
    }
}

void MindStormGame::step(){
    //Fais bouger les mines dans des directions aléatoire mais un résultat pourris qui tremble .....

    const int min = -10;
    const int max = 10;

    /*   for(auto i=0;i<_mines.size();++i){

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
    QTransform transform;

    for(auto i=0;i<_mines.size();++i){
        int xD=_mines.at(i)->_direction.x();
        int yD=_mines.at(i)->_direction.y();

        //transform.translate(x,y);
        QPolygon poly=_mines.at(i)->getPolygon();
        for(auto j=0;j<poly.size();++j){
            int x=poly.at(j).x();
            int y=poly.at(j).y();
            _mines.at(i)->getPolygon().setPoint(j,x+xD,y+yD);
        }
    }
}

bool MindStormGame::collision(int x, int y)
{
    bool retour = false;
    //Test Collision entre vaisseau et mines
    if(_userShip->getPolygon().containsPoint(QPoint(x,y),Qt::OddEvenFill)){
        _userShip->destroy();//pour l'instant disparition du vaisseau
        //Rajouter la destruction de la mine

        retour = true;
    }
    return retour;
}




void MindStormGame::initialize(){
    _mines.clear();
    _userShip->destroy();

}
