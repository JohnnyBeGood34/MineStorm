#ifndef MINE_H
#define MINE_H

#include <QPolygon>

using namespace std;



class Mine
{
public:
    Mine(QPoint qPointRand);
    ~Mine();
    QPolygon getPolygon();
    void hatch();
    void destroy();
    void move();
    QPoint* getCenter();
    void setCenter(QPoint center);

private:
    QPolygon _points;
    QPoint _center;
    int _x;
    int _y;
    int _direction;
};

#endif // MINE_H