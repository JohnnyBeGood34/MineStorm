#include "mindstormgame.h"
#include <QPainter>
#include <QRect>
#include <QColor>

using namespace std;


MindStormGame::MindStormGame(const QSize &size,QObject *parent):Game(size,parent) {

    _userShip=new Ship();//initialisation du vaisseau

    for(auto i=0;i<30;++i){
        auto x = rand() %400;//remplacer par taille du jeu : size().width()
        auto y = rand() %400;
        _mines.push_back(QPoint(x,y));
    }

}

void MindStormGame::draw(QPainter &painter, QRect &rect){
     painter.fillRect(rect, QColor(0,0,0));
     /*TESTS VAISSEAU*/
     QPolygon polygon=_userShip->getPolygon();
     painter.drawPolygon(polygon);

     //Marche pas ... voir comment appliquer un changement
     //QTransform transform= QTransform().rotate(90).scale(0.5,2);
     //polygon=transform.map(polygon);

     //Affichage de toutes les mines
     for(auto i=0;i<_mines.size();++i){
        //initialisation de la mine
         _conputerMine=new Mine(_mines.at(i));
         QPolygon polygonMine=_conputerMine->getPolygon();
         painter.drawPolygon(polygonMine);
     }

}


void MindStormGame::mousePressed( int x, int y){

}

void MindStormGame::keyPressed( int key ){

}

void MindStormGame::keyReleased( int key ){

}

void MindStormGame::step(){
    //Fais bouger les mines dans des directions aléatoire mais un résultat pourris qui tremble .....

    const int min = -10;
    const int max = 10;
    for(auto i=0;i<_mines.size();++i){
        int direction = min + (rand()%(max-min));
        int x=_mines.at(i).x();
              _mines.at(i).setX(x+direction);
              int y=_mines.at(i).y();
                    _mines.at(i).setY(y+direction);
    }
}

void MindStormGame::initialize(){

}
