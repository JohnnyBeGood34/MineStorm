#ifndef LIFECOUNTER_H
#define LIFECOUNTER_H

class LifeCounter
{
public:
    LifeCounter();
    void decrement();
private:
    int lifes;
};

#endif // LIFECOUNTER_H
