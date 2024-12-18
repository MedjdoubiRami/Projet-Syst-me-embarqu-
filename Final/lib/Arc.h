#ifndef ARC_H
#define ARC_H

#include "Point.h"
class Arc {
    private:
        uint8_t pointId;
        uint8_t pointSuivantId;
        uint8_t etat;
        uint8_t poids;

    public:
        Arc();
        Arc(uint8_t pointId, uint8_t pointSuivantId, uint8_t poids);
        uint8_t getPointId() const ;
        uint8_t getPointSuivantId() const ;
        uint8_t getEtat() const ;
        uint8_t getPoids() const ;
        void setEtat(uint8_t _etat);
        
};
#endif 