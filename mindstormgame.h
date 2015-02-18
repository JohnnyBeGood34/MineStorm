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
    /**
     * @brief hasCollision, detect collision between ship and mines
     * @param mine
     * @return
     */
    bool hasCollision(QPolygon mine);

private:
    void hatchMines(QPainter &painter);
    virtual void step();
    void initialize();
    void disposeMines(QPainter &painter);
    void disposeUserShip(QPainter &painter);
    void showEndofGame(QPainter &painter,QRect &rect);
    void resetPlace();
    void buildMines();
    void moveMines();
    /**
     * @brief blastPolygon used to blast the ship or a mine
     * @param polygon
     */
    void blastPolygon(QPoint center);
Ship *_userShip;
Mine *_computerMine;
//vector<QPoint> _mines;
vector<Mine*> _mines;
LifeCounter *_lifecounter;
PointsCounter *_pointcounter;
QPolygon _explosion;

int loopCounter;
QTimer *minesTimer;

private slots:
void test();
};

#endif // TESTGAME_H
