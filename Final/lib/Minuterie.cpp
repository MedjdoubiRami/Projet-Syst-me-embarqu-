#include <Minuterie.h>

Minuterie::Minuterie() {} 

// ---------------------------------------------------------------TIMER2
void Minuterie::activerInterruptionTimer2() { 
    TIMSK2 |= (1 << OCIE2A); 
}

void Minuterie::desactiverInterruptionTimer2() { 
    TIMSK2 &= ~(1 << OCIE2A); 
}

void Minuterie::partirTimer2CTC(uint8_t valeur) {
    TCNT2 = 0;
    OCR2A = valeur;
    TCCR2A |= (1 << WGM21);
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
}

void Minuterie::desactivationTimer2() {
    TCCR2A &= ~(1 << WGM21);
    TCCR2B &= ~(1 << CS22) | ~(1 << CS21)| ~(1 << CS20);
    OCR2A = 0;  
}

// ---------------------------------------------------------------TIMER0
void Minuterie::activerInterruptionTimer0() {
    TIMSK0 |= (1 << OCIE0A);
}

void Minuterie::desactiverInterruptionTimer0() {
    TIMSK0 &= ~(1 << OCIE0A);
}


void Minuterie::partirTimer0CTC(uint8_t valeur) {
    TCNT0 = 0;
    OCR0A = valeur;
    TCCR0A |= (1 << WGM01);
    TCCR0B |= (1 << CS02) | (1 << CS00);
}

void Minuterie::desactivationTimer0()
{
    TCCR0A &= ~(1 << WGM01);
    TCCR0B &= ~(1 << CS02) | ~(1 << CS00);
    OCR0A = 0;
}

