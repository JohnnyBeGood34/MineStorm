#ifndef MINE_H
#define MINE_H

#include <QPolygon>

using namespace std;

class Mine
{
public:
    /**
     * @brief Mine Constructor
     * @param qPointRand an x,y random point
     * @param compteur, a loop counter
     */
    Mine(QPoint qPointRand,int &compteur);
    ~Mine();
    QPolygon getPolygon();
    /**
     * @brief hatch, make the mines hatchs
     */
    void hatch();
    void destroy();
    void move();
    int getType();
    QPoint* getCenter();
    void setCenter(QPoint center);
    string state;

QPoint _direction;
private:
    QPolygon _points;
    QPoint _center;
    QPoint _sommet;
    int _x;
    int _y;
    /**
     * @brief mineType, 1 : little, 2 : middle, 3 great
     */
    int mineType;
    /**
     * @brief The _mineType enum, mine type
     */
    enum _mineType {
        small,
        meduim,
        large,
        Num_Count
       };
    /**
     * @brief direction, direction of mine
     */
    int direction_x;
    int direction_y;
};

#endif // MINE_H
