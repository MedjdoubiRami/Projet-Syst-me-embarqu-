/*
  Nom des auteurs: Othmane  Azzam, Jordan Filion, Yanni Si-Hocine, Rami Medjdoubi, Nema Babah et Naji Bou-Aoun
 
  Description du programme: Ce logiciel facilite la communication entre un robot et un ordinateur en utilisant le protocole RS232.
  
 */
#include <util/delay.h> 
#include "Communication.h"

Communication::Communication() {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0;
    UCSR0B |= ( 1<< TXEN0) | ( 1 << RXEN0);   
    UCSR0C = (1 << UCSZ01)  | (1 << UCSZ00);
}
Communication::~Communication() = default;

void Communication::transmissionUART(uint8_t phrase[], uint8_t longueur) {
    for (uint8_t i = 0; i < longueur; i += 1){
        transmissionUART(phrase[i]);
    }
}
void Communication::transmissionUART(uint8_t donnees) {
    while (!(UCSR0A & (1 << UDRE0))) {
        // Attente de la disponibilité du registre de transmission
    }
    UDR0 = donnees;
}
uint8_t Communication::recevoirUART() {
    while (!(UCSR0A & (1 << RXC0))) {
        // Attente de la réception de données
    }
    return UDR0;
}

void Communication::ecritureEEPROM() {
    for (uint8_t j = 0; j < NOMBRE_DONNEES; j++) {
        memoire_.ecriture(ADRESSE_MEMOIRE+j, tableau_[j]);
        _delay_ms(5);
    }
}

void Communication::stockageDonnees() {
    uint8_t compteur = 0;
    uint8_t donnee;
    while (compteur < NOMBRE_DONNEES) {
        donnee = recevoirUART();
        tableau_[compteur] = donnee;
        compteur++;
        _delay_ms(5);
    }
}



