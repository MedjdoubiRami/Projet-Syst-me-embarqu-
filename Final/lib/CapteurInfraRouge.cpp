#include "CapteurInfraRouge.h"


// placementPin doit etre sur le PORTA0 ou PORTA1 ou PORTA2 
CapteurInfraRouge::CapteurInfraRouge(uint8_t placementPin) : placementPin_(placementPin) {
    DDRA &= (0 << placementPin);
}

void CapteurInfraRouge::setPlacementPin(uint8_t placementPin) {
    placementPin_ = placementPin; 
    DDRA &= (0 << placementPin);
}

void CapteurInfraRouge::lectureSignalInfraRouge() {
    uint16_t somme = 0;
    for (int i = 0; i < NB_LECTURES_; i++) {
        voltageNumerique_ = convertisseurAN_.lecture(placementPin_) >> 2;  
        somme += voltageNumerique_;
    }
    voltageNumerique_ = somme / NB_LECTURES_;
}

void CapteurInfraRouge::uneLecture() {
    voltageNumerique_ = convertisseurAN_.lecture(placementPin_) >> 2;
}

bool CapteurInfraRouge::poteauTrouve() {  // si robot est a 6 cm du poteau, return true 
    return voltageNumerique_ >= 180; // valeur bonne, mais a verifier plus tard 
}

uint8_t CapteurInfraRouge::getVoltageNumerique() {
    return voltageNumerique_; 
}