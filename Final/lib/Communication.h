/*
 * Nom des auteurs: Othmane Azzam, Jordan Filion, Yanni Si-Hocine, Rami Medjdoubi, Nema Babah et Naji Bou-Aoun
 *
 * Description du programme: Cette bibliothèque facilite la communication entre un robot et un ordinateur via le protocole RS232.
 * 
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <avr/io.h>
#include "memoire_24.h"
#define F_CPU 8000000UL

class Communication {
public:
    Communication();
    ~Communication();
    void transmissionUART(uint8_t phrase[], uint8_t longueur);
    void transmissionUART(uint8_t donnees);
    unsigned char recevoirUART();
    void ecritureEEPROM();
    void stockageDonnees();
private:
    Memoire24CXXX memoire_;
    const uint16_t ADRESSE_MEMOIRE = 0x0000;
    const uint8_t NOMBRE_DONNEES = 250; // a changer tout dependant du fichier
    uint8_t tableau_[250];
};
#endif 