#ifndef SHOT_H
#define SHOT_H
#include <QPoint>

/**
 * @brief The Shot class représente un tir
 */



class Shot:public QPoint
{
public:
    Shot();
    void draw();
private:

};

#endif // SHOT_H
