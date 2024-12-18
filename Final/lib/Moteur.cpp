/*
Nom des auteurs: Othmane  Azzam, Jordan Filion, Yanni Si-Hocine, Rami Medjdoubi, Nema Babah et Naji Bou-Aoun*

Description du programme: Ce programme a pour objectif de contrôler les roues du robot,
notamment leur vitesse et leur direction de rotation (vers l'avant ou vers l'arrière).
Il offre la flexibilité d'utiliser deux timers, Timer0 et Timer2, pour gérer ces opérations.
De plus, plusieurs fonctions de motricité de base ont été implémentés pour faciliter la commande
du moteur. Par exemple, le robot peut avancer, reculer, tourner dans les deux sens ou s'arrêter.

Identifications matérielles (Broches I/O):
Si le TIMER1 est utilisé, PD4 et PD5 sont sollicités pour controller les roues.
PD7 est la direction de la roue gauche, PD6 est la direction de la roue droite
*/

#include <util/delay.h> 
#include "Moteur.h"

Moteur::Moteur() {}

void Moteur::initialiseDirectionMoteur(Direction directionRoueGauche , Direction directionRoueDroite) {
    if((directionRoueGauche == Direction::AVANCER) && (directionRoueDroite == Direction::AVANCER)) 
    {
        PORTD &= ~((1 << PD6) | (1 << PD7)); 
    }
    else if((directionRoueGauche == Direction::RECULER) && (directionRoueDroite == Direction::RECULER)) 
    {
        PORTD |= (1 << PD6) | (1 << PD7); 
    }
    else if((directionRoueGauche == Direction::AVANCER) && (directionRoueDroite == Direction::RECULER)) 
    {
        PORTD |= (1 << PD6);
        PORTD &= ~(1 << PD7); 
    }
    else if((directionRoueGauche == Direction::RECULER) && (directionRoueDroite == Direction::AVANCER)) 
    {
        PORTD |= (1 << PD7);
        PORTD &= ~(1 << PD6); 
    }
}

void Moteur::initialisation() {
    DDRD |= (1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7);
    TCCR1A |= (1 << COM1A1) | (1<< COM1A0) | (1<< COM1B1) | (1<< COM1B0)| (1 << WGM10);
    TCCR1B |=(1 << CS11) ;
    TCCR1C = 0;
    OCR1A = 255;
    OCR1B = 255;
}

void Moteur::initialiseRatioPWM(uint8_t ratioA, uint8_t ratioB) {
    OCR1A = ratioA;
    OCR1B = ratioB;
}

void Moteur::initialiseDirectionAvance() {
    initialiseDirectionMoteur(Direction::AVANCER, Direction::AVANCER);
}

void Moteur::initialiseDirectionReculer() {
    initialiseDirectionMoteur(Direction::RECULER, Direction::RECULER);
}


void Moteur::roulerToutDroit(uint8_t ratio) {
    initialiseRatioPWM(80, 80);
    _delay_ms(100);
    uint8_t correcteurRoueDroite = ratio + 7;  // on veut qua laille plus vite
    uint8_t correcteurRoueGauche = ratio;   // on veut qua laille moins vite
    initialiseRatioPWM(correcteurRoueDroite, correcteurRoueGauche);
}

void Moteur::tournerGauche(uint8_t ratio) { 
    initialiseDirectionMoteur(Direction::AVANCER, Direction::RECULER);
    initialiseRatioPWM(80, 80);
    _delay_ms(200);
    uint8_t correcteurRoueDroite = ratio + 27;  // on veut qua laille plus vite
    uint8_t correcteurRoueGauche = ratio + 18; 
    initialiseRatioPWM(correcteurRoueDroite, correcteurRoueGauche);
}

void Moteur::tournerDroite(uint8_t ratio) { 
    initialiseDirectionMoteur(Direction::RECULER, Direction::AVANCER);
    initialiseRatioPWM(80, 80);
    _delay_ms(200);
    uint8_t correcteurRoueDroite = ratio + 27;  
    uint8_t correcteurRoueGauche = ratio + 12;   
    initialiseRatioPWM(correcteurRoueDroite, correcteurRoueGauche);
}

void Moteur::tourner180Gauche(uint8_t ratio) {
    initialiseDirectionMoteur(Direction::AVANCER, Direction::RECULER);
    initialiseRatioPWM(80, 80);
    _delay_ms(200);
    uint8_t correcteurRoueDroite = ratio + 27;  // on veut qua laille plus vite
    uint8_t correcteurRoueGauche = ratio + 12;   // on veut qua laille moins vite
    initialiseRatioPWM(correcteurRoueDroite, correcteurRoueGauche);
}

void Moteur::arreterMoteur() { // mettre valeur que le robot bouge plus 
    OCR1A = PWM_VALEUR_ARRET;
    OCR1B = PWM_VALEUR_ARRET;
} 