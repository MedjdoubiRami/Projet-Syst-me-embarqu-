#include "Sonore.h"


void Sonore::initialisation()
{
    //mode CTC, comparaison A :
    TCCR0A |= (1 << COM0A0)|(1 << WGM01);
    //prescaler de 1024 :
    TCCR0B |= (1 << CS02)  |(1 << CS00) ;
    //sorties :
    DDRB   |= (1 << DDB3)  |(1 << DDB2) ;
    //timer mis a 0 :
    TCNT0 = 0;
}
void Sonore::jouerNoteGrave()
{
        uint32_t valeurCompteur = ( F_CPU / PRESCALER_1024) / 110;
        //PWM actif sur OCR0A :
        OCR0A = valeurCompteur;
}
void Sonore::jouerNoteAigu()
{
        uint32_t valeurCompteur = ( F_CPU / PRESCALER_1024) / 440;
        //PWM actif sur OCR0A :
        OCR0A = valeurCompteur;
}

// Arrete le son en mettant le prescaler a 0
// Clear le prescaler fait arreter le son
void Sonore::arret()
{
    TCCR0B &= ~((1 << CS02)|(1 << CS01)|(1 << CS00));
}