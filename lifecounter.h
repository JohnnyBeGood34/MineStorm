#ifndef LIFECOUNTER_H
#define LIFECOUNTER_H


using namespace std;

class LifeCounter
{
public:
    LifeCounter();
    void decrement();
private:
    int _lifes;
};

#endif // LIFECOUNTER_H
