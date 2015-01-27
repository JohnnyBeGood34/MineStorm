#include "pointscounter.h"
/**
 * @brief PointsCounter::PointsCounter constructor, points are initialize to 0
 */
PointsCounter::PointsCounter()
{
    _points = 0;
}

/**
 * @brief PointsCounter::increment, increment the points counter
 */
void PointsCounter::increment(){
    _points += 10;
}
