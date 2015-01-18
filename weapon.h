#ifndef WEAPON_H
#define WEAPON_H
#include "shot.h"
#include "vector"
using namespace std;
/**
 * @brief The Weapon class est la classe représentant l'arme du vaisseau user
 */
class Weapon
{
public:
    Weapon();
    /**
     * @brief fire tire des missile
     */
    void fire();

private:
    int speed;
    vector<Shot> shots;
};

#endif // WEAPON_H
