#ifndef SHIP_H
#define SHIP_H

#include <QPolygon>

using namespace std;

class Ship
{

public:

    Ship();
    ~Ship();
    QPolygon getPolygon();
    void accelerate();
    void rotate();
    void destroy();
    void slowDown();

private:
QPolygon _points;
int _speed;
};

#endif // SHIP_H
