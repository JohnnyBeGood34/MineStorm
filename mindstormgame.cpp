#include "mindstormgame.h"
#include <QPainter>
#include <QRect>
#include <QColor>

using namespace std;


MindStormGame::MindStormGame(const QSize &size,QObject *parent):Game(size,parent) {

    _userShip=new Ship();//initialisation du vaisseau

    for(auto i=0;i<30;++i){

        auto x = rand() %600;//remplacer par taille du jeu : size().width()
        auto y = rand() %600;
        _mines.push_back(QPoint(x,y));
        // _mines.push_back(new Mine(QPoint(x,y)));
    }


}



void MindStormGame::draw(QPainter &painter, QRect &rect){

     painter.fillRect(rect, QColor(0,0,0));
     QPen pen(Qt::blue, 2, Qt::SolidLine);
      painter.setPen(pen);
     /*TESTS VAISSEAU*/
     QPolygon polygon=_userShip->getPolygon();

     painter.drawPolygon(polygon);

    disposeMines(painter);


     //TESTS TIRS
   /* auto x=_userShip->getSommet().x();
      auto y=_userShip->getSommet().y();
     painter.drawLine(x,y,x,y-10);
*/
}




void MindStormGame::mousePressed( int x, int y){

}

void MindStormGame::keyPressed( int key ){

    int acceleration= 1;

    switch(key) {
    case Qt::Key_Up: _userShip->accelerate(acceleration);
        break;
    case Qt::Key_Down: _userShip->slowDown();
        break;
    case Qt::Key_Left: _userShip->rotate();
        break;
    case Qt::Key_Right: _userShip->rotate();
        break;
    case Qt::Key_Space:_userShip->getWeapon()->fire();//Tirs du vaisseau
        break;
    }
}

void MindStormGame::disposeMines(QPainter &painter){

   for(auto i=0;i<_mines.size();++i){
            //initialisation de la mine
             _computerMine=new Mine(_mines.at(i));
             QPolygon polygonMine=_computerMine->getPolygon();
             painter.drawPolygon(polygonMine);

         }


//version vecteur de Mines
    /*
for(auto i=0;i<_mines.size();++i){

  painter.drawPolygon(_mines.at(i)->getPolygon());
}
*/
}

void MindStormGame::keyReleased( int key ){

}

void MindStormGame::step(){
    //Fais bouger les mines dans des directions aléatoire mais un résultat pourris qui tremble .....

    const int min = -10;
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

//version vector de Mines
/*
    for(auto i=0;i<_mines.size();++i){

        QPoint* center=_mines.at(i)->getCenter();
                int x=center->x();
                      //_mines.at(i)->getCenter()->setX(x+1);
                      int y=center->y();
                        //   _mines.at(i)->getCenter()->setY(y+1);
                      _mines.at(i)->setCenter(QPoint(x,y));

    }
*/
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

}
