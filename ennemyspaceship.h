#ifndef ENNEMYSPACESHIP_H
#define ENNEMYSPACESHIP_H

#include <QPolygon>
#include <QPainter>

class EnnemySpaceShip
{
public:
    EnnemySpaceShip();
    ~EnnemySpaceShip();
    QPolygon getPolygon();
    /**
     * @brief fileMines va placer les mines ennemies sur le game board
     */
    void fileMines();
    void initShip();
    void move();
    QPoint getCenter();
    void destroy();
private:
    QPoint _centerEnnemySpaceShip;
    QPolygon _pointsEnnemySpaceShip;
};

#endif // ENNEMYSPACESHIP_H
