#include "Bouton.h"

Bouton::Bouton() {}

bool Bouton::debounce() {
    _delay_ms(25);
    return PIND & (1 << PD2);
}

bool Bouton::debounceSelection() {
    _delay_ms(29);
    if ((PIND & (1 << PD3)) == 0) {
        return true; 
    }
    else { return false; }
}

bool Bouton::debounceValidation() {
    _delay_ms(33);
    if ((PINB & (1 << PB2)) == 0) {
        return true; 
    }
    else { return false; }
}

void Bouton::initialisationInterruptionD2() {
    cli();
    DDRD &= ~(1 << PORTD2); // Mettez le bit correspondant à PD2 à 0 (entrée)
    EIMSK |= (1 << INT0); // Activation de l'interruption INT0 sur PD2
    EICRA |= (1 << ISC01) | (1 << ISC00); // Front montant (0 volts -> 5 volts)
    sei();
}

void Bouton::initialisationInterruptionSelection() { // Interruption sur PD3
    cli();
    DDRD &= ~(1 << PORTD3); // Mettez le bit correspondant à PD3 à 0 (entrée)
    EIMSK |= (1 << INT1); // Activation de l'interruption INT1 sur PD3
    EICRA |= (1 << ISC11) | (0 << ISC10); // Front descendant (5 volts -> 0 volts)
    sei();
}

void Bouton::initialisationInterruptionValidation() { // Interruption sur PB2
    cli();
    DDRB &= ~(1 << PORTB2); // Mettez le bit correspondant à PB2 à 0 (entrée)
    EIMSK |= (1 << INT2); // Activation de l'interruption INT2 sur PB2
    EICRA |= (1 << ISC21) | (0 << ISC20); // Front descendant (5 volts -> 0 volts)
    sei();
}