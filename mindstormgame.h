#ifndef TESTGAME_H
#define TESTGAME_H
#include "mine.h"
#include "game.h"
#include "ship.h"
#include "vector"
#include "lifecounter.h"
#include "pointscounter.h"
#include "memory"
#include <QPaintEvent>
#include <QTimer>

using namespace std;

class MindStormGame:public Game
{

public:
    MindStormGame(const QSize &size,QObject *parent = nullptr);
    virtual void draw(QPainter &painter, QRect &rect);
    void mousePressed( int x, int y);
    void keyPressed( int key );
    void keyReleased( QKeyEvent * event);
    bool collision(int x, int y);

private:
    void hatchMines(QPainter &painter);
    virtual void step();
    void initialize();
    void disposeMines(QPainter &painter);
    void disposeUserShip(QPainter &painter);
Ship *_userShip;
Mine *_computerMine;
//vector<QPoint> _mines;
vector<Mine*> _mines;
LifeCounter *_lifecounter;
PointsCounter *_pointcounter;

int loopCounter;

};

#endif // TESTGAME_H
