#ifndef CAPTEUR_INFRA_ROUGE_H
#define CAPTEUR_INFRA_ROUGE_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include "can.h"

// pour le poteau !! 
class CapteurInfraRouge {
public:
    CapteurInfraRouge() = default;
    CapteurInfraRouge(uint8_t placementPin);
    ~CapteurInfraRouge() = default;
    void lectureSignalInfraRouge(); 
    void uneLecture(); 
    bool poteauTrouve();
    void setPlacementPin(uint8_t placementPin);
    uint8_t getVoltageNumerique();

private:
    uint8_t voltageNumerique_; 
    uint8_t placementPin_;
    const uint8_t NB_LECTURES_ = 30;
    const uint8_t VOLTAGE_MAX_ = 2; 
    can convertisseurAN_; 
};
#endif 