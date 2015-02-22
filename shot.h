#ifndef SHOT_H
#define SHOT_H
#include <QPolygon>
/**
 * @brief The Shot class représente un tir
 */

using namespace std;

class Shot
{
public:
    Shot(QPoint shotPoint,QPoint centerShip);
    ~Shot();
    void hatch();
    QPoint* getShot();
    void reDrawShot();
    QPolygon getPolygon();
private:
    QPolygon _shotPoint;
    QPoint _centerShot;
    QPoint _centerShip;
};

#endif // SHOT_H
