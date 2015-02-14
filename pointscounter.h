#ifndef POINTSCOUNTER_H
#define POINTSCOUNTER_H
#include <QPainter>
using namespace std;

class PointsCounter
{
public:
    PointsCounter();
    void increment();
    void drawPointsIntoGameBoard(QPainter &painter,const QSize &size);
private:
    int _points;
    //Attribut zone de texte ou autre?
};

#endif // POINTSCOUNTER_H
