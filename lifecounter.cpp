#include "lifecounter.h"
/**
 * @brief LifeCounter::LifeCounter constructor, the life counter is initialize to 4
 */
LifeCounter::LifeCounter()
{
    _lifes = 4;
}
/**
 * @brief LifeCounter::decrement allow to decrement the counter
 */
void LifeCounter::decrement(){
    if(_lifes > 0){
        --_lifes;
    }
}
