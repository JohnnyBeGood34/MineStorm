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
    Shot();
    void draw();
    QPoint getStart();
    QPoint getEnd();
private:
QPoint _start;
QPoint _end;
};

#endif // SHOT_H
