#ifndef SOUND_H
#define SOUND_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

class Sonore
{
public:
    Sonore() = default;
    ~Sonore() = default;
    void jouerNoteGrave();
    void jouerNoteAigu();
    void initialisation();
    void arret();

private:
    const uint16_t PRESCALER_1024 = 1024; 
};

#endif