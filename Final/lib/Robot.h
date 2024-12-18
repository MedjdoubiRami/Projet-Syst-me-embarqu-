#ifndef ROBOT_H
#define ROBOT_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include "Led.h"
#include "Moteur.h"
#include "CapteurMakerLine.h"
#include "CapteurInfraRouge.h"
#include "Sonore.h"
#include "Minuterie.h"

// Objectif : Faciliter le control du robot en creant un objet robot. On va instancier des objets dans la class robot 
//            pour pouvoir configurer le robot au complet a partir d'une seule classe
//            on va affecter notre code sur un objet ROBOT dans la classe machine a etat finis 

enum class DirectionF {
    EST ,
    SUD ,
    OUEST,
    NORD
};

class Robot {
public:
    Robot();  
    ~Robot() = default; 
    void setDirection(uint8_t direction);

    // Fonctions Led 
    void allumeLedVert();
    void allumeLedRouge(); 
    void eteindreLed(); 
    void clignoteVert4hz();
    void eteindreClignotement4hz();
    uint8_t getEtatLedRobot(); 

    // Fonctions mouvement 
    void immobilisationRobot();
    void robotRoulerDroit(uint8_t ratio);
    void robotTourneGauche(uint8_t ratio);
    void robotTourneDroite(uint8_t ratio);
    void robotTourne180(uint8_t ratio);  

    void reactionAuxLignes(uint8_t direction, uint8_t ratio);
    bool recherchePoteau();

    // Fonctions TrouverCoin : 
    void collecteDonnee(uint8_t ratio);
    void identificationPosition();
    uint8_t getCombinaisonTrouvee(); 
    void incrementeCompteurTimer0();

    //Fonction Trajet
    void tournerGauche();
    void tournerDroite();
    void allerToutDroit();
    void faire180();
    void faireTrajet(uint8_t* pointsTrajet);

private:
    bool tournageDroiteEffectue = false;
    bool tournageGaucheEffectue = false;
    bool tournage180Effectue = true;
    DirectionF direction_;

    Led ledRobot_;
    Moteur moteurRobot_;
    CapteurMakerLine makerLineRobot_;
    CapteurInfraRouge infraRougeRobot_;
    Sonore sonoreRobot_; 
    Minuterie minuterieRobot_; 

    uint8_t directionRobot_; // 0 = gauche  / 1 = droite / 2 = avance / 3 = 180degre / 4 = 360degre / 5 = arret 
    volatile uint8_t etatLed_ = 0; // 0 = eteint , 1 = vert , 2 = rouge 

    // // Attributs pour TrouverCoin : 
    uint8_t nombreIntersectionGauche_ = 0;
    uint8_t nombreIntersectionDroite_ = 0; 
    uint8_t compteurIntersection_ = 0; 
    uint8_t combinaisonTrouvee_; // 1 == Coin(1,1),Est , 2 == Coin(1,1), Sud 3 == Coin(1,7) Sud, 4 == Coin(1,7) Ouest, 5 == Coin (4,1) Nord , 6 == Coin (4,1) Est , 7 == (4,7) Ouest , 8 == (4,7) Nord
    uint8_t tempsPremiereIntersection_;
    uint8_t tempsChemin_;
    volatile uint8_t compteurTimer0_; 

    const uint8_t TEMPS_INCREMENTATION_TIMER2 = 250; 
    const uint8_t TEMPS_75_POURCENT = 100; // pointA -> pointB + 1/2*point     ==> 100 est la valeur tester avec les mauvaise pile, donc a retester !!!  
    const uint8_t TEMPS_INCREMENTATION_TIMER0 = 255;

};
#endif