/*
 

    Nom des auteurs: Othmane  Azzam, Jordan Filion, Yanni Si-Hocine, Rami Medjdoubi, Nema Babah et Naji Bou-Aoun*
        Description du programme: Ce programme a pour objectif de contrôler les roues du robot,
        notamment leur vitesse et leur direction de rotation (vers l'avant ou vers l'arrière).
        Il offre la flexibilité d'utiliser deux timers, Timer0 et Timer2, pour gérer ces opérations.
        De plus, plusieurs fonctions de motricité de base ont été implémentés pour faciliter la commande
        du moteur. Par exemple, le robot peut avancer, reculer, tourner dans les deux sens ou s'arrêter.
        Identifications matérielles (Broches I/O):
        Si le TIMER0 est utilisé, PB5 et PB6 sont sollicités pour controller les roues.
        Si le TIMER2 est utilisé, PD4 et PD5 sont sollicités pour controller les roues.
    */


#ifndef MOTEUR_H
#define MOTEUR_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


enum class Direction { AVANCER, RECULER };

class Moteur {
public:
    Moteur();
    void initialisation();

    void initialiseDirectionAvance();
    void initialiseDirectionReculer();

    void roulerToutDroit(uint8_t ratio);
    void tournerGauche(uint8_t ratio);
    void tournerDroite(uint8_t ratio);

    void tourner180Gauche(uint8_t ratio);

    void arreterMoteur();
    void initialiseRatioPWM(uint8_t ratioA, uint8_t ratioB);

private:
    void initialiseDirectionMoteur(Direction directionRoueGauche , Direction directionRoueDroite);
    const uint8_t PWM_VALEUR_ARRET = 255;

    const uint8_t CORRECTION_ROUE_GAUCHE_AVANT = 0; // ADDITIONNER) Plus ou moins good
    const uint8_t CORRECTION_ROUE_DROITE_AVANT = 0; // SOUSTRAIRE)

    const uint8_t CORRECTION_ROUE_GAUCHE_TOURNER = 50; // ADDITIONNER) Pas good pcq mauvaise pile
    const uint8_t CORRECTION_ROUE_DROITE_TOURNER = 70; // Additionner

    const uint8_t CORRECTION_ROUE_GAUCHE_180 = 0; 
    const uint8_t CORRECTION_ROUE_DROITE_180 = 0;
};

#endif
