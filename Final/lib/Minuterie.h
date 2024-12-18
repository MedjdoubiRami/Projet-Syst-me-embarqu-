/*
*Identification du matériel (Broches E/S) : PD7 - OC2A est la broches associee aux signal de que genere le registre de comparaison OCR2A
*/

#ifndef MINUTERIE_H
#define MINUTERIE_H

#include <avr/io.h>
#define F_CPU 8000000UL

class Minuterie 
{
public:
    Minuterie();
    ~Minuterie() = default; 

    void desactivationTimer2(); 
    void activerInterruptionTimer2();
    void desactiverInterruptionTimer2(); 
    void partirTimer2CTC(uint8_t valeur);

    void desactivationTimer0();
    void activerInterruptionTimer0();
    void desactiverInterruptionTimer0();
    void partirTimer0CTC(uint8_t valeur);
};
#endif 