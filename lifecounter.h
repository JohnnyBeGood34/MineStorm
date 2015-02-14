#ifndef LIFECOUNTER_H
#define LIFECOUNTER_H
#include <QPainter>

using namespace std;

class LifeCounter
{
public:
    LifeCounter();
    /**
     * @brief decrement, decrement the total life number by 1
     */
    void decrement();
    /**
     * @brief drawLifeOnGameBoard used to display the user lifes
     * @param painter used to draw the text
     * @param size used to know where to put the text into the gameboard
     */
    void drawLifeOnGameBoard(QPainter &painter,const QSize &size);
    int getLifes();
    void setLifes(int nbLives);
private:
    int _lifes;
};

#endif // LIFECOUNTER_H
