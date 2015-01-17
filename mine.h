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


private:
    QPolygon _points;
    int _x;
    int _y;
    int _direction;
};

#endif // MINE_H
