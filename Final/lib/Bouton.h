#ifndef UNTITLED3_BOUTON_H
#define UNTITLED3_BOUTON_H
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL


class Bouton {
public:
    Bouton();

    bool debounce();
    bool debounceSelection();
    bool debounceValidation();

    void initialisationInterruptionD2(); 
    void initialisationInterruptionSelection();
    void initialisationInterruptionValidation();

private:
    const uint8_t DELAI_10MS = 10;
};
#endif //UNTITLED3_BOUTON_H
