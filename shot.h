#ifndef SHOT_H
#define SHOT_H
#include <QPoint>
#include <QPolygon>
/**
 * @brief The Shot class représente un tir
 */



class Shot:public QPolygon
{
public:
    Shot(QPoint start,QPoint end);
    void draw();
    QPoint getStart();
    QPoint getEnd();
    QPolygon* getPolygon();
    void setPainted(bool painted);
    bool getPainted();

private:
    QPoint _start;
    QPoint _end;
    QPolygon polygonShot;
    bool isPainted;
};

#endif // SHOT_H
