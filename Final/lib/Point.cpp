#include <assert.h>
#include "math.h"
#include "Point.h"




Point::Point(){}

Point::Point(uint8_t _id, uint8_t _x, uint8_t _y){
    id = _id;
    x = _x;
    y = _y;
}

uint8_t Point::getX() const {
    return x;
}
uint8_t Point::getY() const {
    return y;
}
uint8_t Point::getId() const {
    return id;
}
// double Point::distatnce (const Point& point) const{
//     double dx = x - point.x,
//             dy = y - point.y;
//     return sqrt(dx*dx + dy*dy);
// }
  
// std::istream& operator >> (std::istream& is, Point& point){
//     char virgule,
//     if(is){
//         is >> point.id >> virgule >> point.x >> virgule >> point.y >> virgule >> point.est >> virgule >> point.sud >> virgule >> point.ouest >> virgule >> point.nord;
//         assert(virgule == ',');
//     }
//     return is;
// }