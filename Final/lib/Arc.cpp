#include "Point.h"
#include "Arc.h"

    Arc::Arc(){}
    
    Arc::Arc(uint8_t _pointId, uint8_t _pointSuivantId, uint8_t _poids){
        pointId = _pointId;
        pointSuivantId = _pointSuivantId;
        etat = 1;
        poids = _poids;
    }
    
    
    uint8_t Arc::getPointId() const {
        return pointId;
    }
    uint8_t Arc::getPointSuivantId() const {
        return pointSuivantId;
    }
    uint8_t Arc::getEtat() const {
        return etat;
    }
    uint8_t Arc::getPoids() const {
        return poids;
    }
    void Arc::setEtat(uint8_t _etat){
        etat = _etat;
    }