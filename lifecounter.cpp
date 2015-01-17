#include "lifecounter.h"

LifeCounter::LifeCounter()
{
    _lifes = 4;
}

void LifeCounter::decrement(){
    if(_lifes > 0){
        --_lifes;
    }
}
