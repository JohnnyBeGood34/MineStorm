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
                painter.drawPoint(_mines.at(i));
     }
}


void MindStormGame::mousePressed( int x, int y){

}

void MindStormGame::keyPressed( int key ){

}

void MindStormGame::keyReleased( int key ){

}

void MindStormGame::step(){
//Ici => pour toutes les mines les faire bouger aléatoirement
    //appliquer un QTransform ?
    for(auto i=0;i<_mines.size();++i){
        int x=_mines.at(i).x();

              _mines.at(i).setX(x+10);
    }
}

void MindStormGame::initialize(){

}
