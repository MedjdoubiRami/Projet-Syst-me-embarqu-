#ifndef POINT_H
#define POINT_H

#include <avr/io.h>
//#include "memoire_24.h"
#define F_CPU 8000000UL

class Point {
    public:
        Point();
        Point(uint8_t _id, uint8_t _x, uint8_t _y);
        uint8_t getX() const ;
        uint8_t getY() const ;
        uint8_t getId() const ;
    private:
        uint8_t id;
        uint8_t x;
        uint8_t y; 
};
#endif 