#include "shot.h"

Shot::Shot(QPoint start,QPoint end):_start(start),_end(_end)
{       
    polygonShot << start << end;
    this->isPainted = false;
}
void Shot::draw(){

}

QPolygon* Shot::getPolygon(){
    return &this->polygonShot;
}

QPoint Shot::getStart(){
    return _start;
}

QPoint Shot::getEnd(){
    return _end;
}

void Shot::setPainted(bool painted){
    this->isPainted = painted;
}

bool Shot::getPainted(){
    return this->isPainted;
}
