#ifndef TESTGAME_H
#define TESTGAME_H
#include "game.h"
#include "ship.h"
#include "vector"
#include "lifecounter.h"
#include "pointscounter.h"
#include "memory"
using namespace std;

class MindStormGame:public Game
{

public:
    MindStormGame(const QSize &size,QObject *parent = nullptr);
    virtual void draw(QPainter &painter, QRect &rect);
    void mousePressed( int x, int y);
    void keyPressed( int key );
    void keyReleased( int key );

private:
    virtual void step();
    void initialize();
Ship *_userShip;
//vector<unique_ptr<QPoint>> _mines;
vector<QPoint> _mines;
LifeCounter *_lifecounter;
PointsCounter *_pointcounter;

};

#endif // TESTGAME_H
