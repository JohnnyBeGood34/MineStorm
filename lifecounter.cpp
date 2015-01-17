#include "lifecounter.h"

LifeCounter::LifeCounter()
{
    lifes = 4;
}

LifeCounter::decrement(){
    if(lifes > 0){
        --lifes;
    }
}
