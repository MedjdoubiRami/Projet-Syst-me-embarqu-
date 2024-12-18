#ifndef MACHINE_A_ETAT
#define CAPTEUR_INFRA_ROUGE_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include "Robot.h"


// ETAT ATTENTE_DE_MODE ->  led allume rouge 
//     CHANGE ETAT :     
//     etat SELECTION_COIN (pese sur le bouton interrupteur D2)
//     etat SELECTION_TRAJET_LIGNE (pese sur Bouton Selection)

// ETAT IDENTIFICATION_COIN -> led eteint - attends 2000ms - 
//                             le robot bouge sur la map pour trouver le coin et orientation. Pendant, il clignote vert a 4Hz 
//                             une fois trouver, le robot fait son aigu + led allume vert + repositionne au coin 
//                             affiche les infos du coin sur la LCD (L, C) Orientation 
//      CHANGE ETAT :
//      etat ATTENTE_DE_MODE (changement automatic lorsque le coin est trouver)
//      etat SELECTION_TRAJET_LIGNE (pese sur bouton Selection) **important si on trouve pas le coin, safe exit 

// ETAT SELECTION_TRAJET_LIGNE -> l'ecran affiche Ligne 1
//                                quand on pese sur le bouton selection -> incremente de 1, sauf quand on est a 4 on retourne a 1 
//                                bouton validation => enregistre ligne, et changement etat
//      CHANGE ETAT :
//      etat SELECTION_TRAJET_COLONNE (pese sur le bouton validation)

// ETAT SELECTION_TRAJET_COLONNE -> l'ecran affiche Ligne 1
//                                  quand on pese sur le bouton selection -> incremente de 1, sauf quand on est a 7 on retourne a 1 
//      CHANGE ETAT :
//      etat CONFIRMATION_TRAJET (pese sur Bouton Validation)

// ETAT CONFIRMATION_TRAJET -> l'ecran affiche (L, C) OK?   OUI 
//                             pese bouton Selection => alterne entre OUI / NON
//      CHANGE ETAT :
//      etat SELECTION_TRAJET_LIGNE (bouton Valiation + NON)
//      etat EXECUTION_TRAJET (bouton Validation + OUI)

// ETAT EXECUTION_TRAJET -> if (premier Trajet) { pointDepart = (1,1) }
//                          calcul trajet le plus court (appel dijkstra)
//                          pause 2000ms
//                          commence le trajet 
//      CHANGE ETAT : 
//      etat RENCONTRE_OBSTACLE (interruption Capteur Infrarouge)
//      etat FIN_TRAJET (arriver a destination)
//      etat SELECTION_TRAJET_LIGNE (pese sur Bouton Selection) *Si on reussit pas le trajet on peut recommencer au point (1,1) * Safe exit

// ETAT RENCONTRE_OBSTACLE -> robot s'arrete + emet un song grave pendant 2000ms
//                            elimine le point du poteau de la MAP
//      CHANGE ETAT : 
//      etat EXECUTION_TRAJET      

// ETAT FIN_TRAJET -> boucle ( 1 son aigu 200ms + delai 100ms) repete boucle 5 fois total 
//                    Update point Depart = destination du Trajet Courant
//      CHANGE ETAT :
//      etat SELECTION_TRAJET_LIGNE (changement automatic)

enum Etat {
    ATTENTE_DE_MODE,
    SELECTION_COIN,
    IDENTIFICATION_COIN,
    SELECTION_TRAJET_LIGNE,
    SELECTION_TRAJET_COLONNE,
    CONFIRMATION_TRAJET,
    EXECUTION_TRAJET,
    RENCONTRE_OBSACLE,
    FIN_TRAJET
};

Etat etatCourante = Etat::ATTENTE_DE_MODE; 

ISR(INT0_vect) 
{
    // deounce
    etatCourante = Etat::IDENTIFICATION_COIN; 
}

ISR(INT1_vect)
{
    if ((etatCourante == Etat::ATTENTE_DE_MODE) || (etatCourante == Etat::IDENTIFICATION_COIN) || (etatCourante == Etat::EXECUTION_TRAJET) ) 
    {

    }
}

switch(etatCourante) 
{
    case Etat::ATTENTE_DE_MODE :

        break;
    
    case Etat::SELECTION_COIN :

        break;

    case Etat::IDENTIFICATION_COIN :

        break;

    case Etat::SELECTION_TRAJET_LIGNE :

        break;

    case Etat::SELECTION_TRAJET_COLONNE :

        break;

    case Etat::CONFIRMATION_TRAJET :

        break;

    case Etat::EXECUTION_TRAJET :

        break;

    case Etat::RENCONTRE_OBSTACLE :

        break;

    case Etat::FIN_TRAJET :

        break;
}