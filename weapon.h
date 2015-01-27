#ifndef WEAPON_H
#define WEAPON_H
#include "shot.h"
#include "vector"
using namespace std;
/**
 *
 */
class Weapon
{
public:
    Weapon();
    /**
     *
     */
    void fire();

private:
    int speed;
    vector<Shot> shots;
};

#endif // WEAPON_H
