#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Bouton.h"
#include "Robot.h"
#include "Minuterie.h"
#include "lcm_so1602dtr_m_fw.h"
#include <stdio.h>
#include <stdint.h>
#include "Carte.h"

volatile uint8_t compteur8Led = 0;
volatile uint8_t gActivationLed = 0;
volatile uint8_t boutonInterruption = 0;
volatile uint8_t boutonSelection = 0;
volatile uint8_t boutonValidation = 5;
volatile uint8_t ligne = 1;
volatile uint8_t colonne = 1;
volatile uint8_t validation = 0;
const char* stringLigne;
const char* stringColonne;

Robot robot;
Bouton bouton;
LCM afficheur(&DDRC, &PORTC);

ISR(TIMER2_COMPA_vect) { // LED 4HZ FONCTIONNE !!!
    compteur8Led++;
    if (compteur8Led % 8 == 0) {
        if (gActivationLed == 0) {
            gActivationLed = 1;
            robot.allumeLedVert();
        }
        else {
            gActivationLed = 0;
            robot.eteindreLed();
        }
    }
}

ISR(TIMER0_COMPA_vect) // On va incrémenter le Timer 0 à chaque fois que l'on va être rendu à 255 ce qui équivaut à 0.033 secondes.
{
    robot.incrementeCompteurTimer0();
}

ISR(INT0_vect)
{
    if (bouton.debounce()) {
        boutonInterruption = 1;
    }
}

ISR(INT1_vect)//gauche (Selection)
{
    if (bouton.debounceSelection()) {
        boutonSelection = 1;
    }
}
ISR(INT2_vect)//droite (Validation)
{
    if (bouton.debounceValidation()) {
        boutonValidation = 1;
    }
}

enum class Etat {
    ATTENTE_DE_MODE,
    IDENTIFICATION_COIN,
    SELECTION_TRAJET_LIGNE,
    SELECTION_TRAJET_COLONNE,
    CONFIRMATION_TRAJET,
    EXECUTION_TRAJET,
    RENCONTRE_OBSTACLE,
    FIN_TRAJET
};

void afficherCoin(uint8_t combinaisonTrouvee)
{
    afficheur.clear();
    afficheur.en_blink(false);
    switch (combinaisonTrouvee)
    {
    case 1:
        // TO DO : Afficher "(1,1) \n EST"
        afficheur.write("(1,1)", 0, true);
        afficheur.write("EST", 16, false);
        break;
    case 2:
        // TO DO : Afficher "(1,1) \n SUD"
        afficheur.write("(1,1)", 0, true);
        afficheur.write("SUD", 16, false);
        break;
    case 3:
        // TO DO :Afficher "(1,7) \n SUD"
        afficheur.write("(1,7)", 0, true);
        afficheur.write("SUD", 16, false);
        break;
    case 4:
        // TO DO :Afficher "(1,7) \n OUEST"
        afficheur.write("(1,7)", 0, true);
        afficheur.write("OUEST", 16, false);
        break;
    case 5:
        // TO DO : Afficher "(4,1) \n NORD"
        afficheur.write("(4,1)", 0, true);
        afficheur.write("NORD", 16, false);
        break;
    case 6:
        // TO DO : Afficher "(4,1) \n EST"
        afficheur.write("(4,1)", 0, true);
        afficheur.write("EST", 16, false);
        break;
    case 7:
        // TO DO : Afficher "(4,7) \n OUEST"
        afficheur.write("(4,7)", 0, true);
        afficheur.write("OUEST", 16, false);
        break;
    case 8:
        // TO DO : Afficher "(4,7) \n NORD"
        afficheur.write("(4,7)", 0, true);
        afficheur.write("NORD", 16, false);
        break;
    }
}

void selectionTrajetLigne(){
    if(ligne > 4){
        ligne = 1;
    }
    if(ligne == 1){
        afficheur.write("LIGNE", 0, true); // true -> efface tout sur lafficheur  , false -> maintient tout sur lafficheur, sauf cque tu rentre
        afficheur.write("1", 16, false);
        stringLigne = "1";
    }
    if(ligne == 2){
        afficheur.write("LIGNE", 0, true);
        afficheur.write("2", 16, false);
        stringLigne = "2";
    }
    if(ligne == 3){
        afficheur.write("LIGNE", 0, true);
        afficheur.write("3", 16, false);
        stringLigne = "3";
    }
    if(ligne == 4){
        afficheur.write("LIGNE", 0, true);
        afficheur.write("4", 16, false);
        stringLigne = "4";
    }

    ligne = ligne + 1;
}

void validationTrajet(){
    validation = validation + 1;
    if(validation > 2){
        validation = 1;
    }
    if(validation == 1){
        afficheur.write("(", 0, true);
        afficheur.write(stringLigne, 1, false);
        afficheur.write(",", 2, false);
        afficheur.write(stringColonne, 4, false);
        afficheur.write(") OK?", 5, false);
        afficheur.write("OUI", 16, false);
    }
    if(validation == 2){
        afficheur.write("(", 0, true);
        afficheur.write(stringLigne, 1, false);
        afficheur.write(",", 2, false);
        afficheur.write(stringColonne, 4, false);
        afficheur.write(") OK?", 5, false);
        afficheur.write("NON", 16, false);
    }
}

void selectionTrajetColonne(){
    if(colonne > 7){
        colonne = 1;
    }
    if(colonne == 1){
        afficheur.write("COLONNE", 0, true); // true -> efface tout sur lafficheur  , false -> maintient tout sur lafficheur, sauf cque tu rentre
        afficheur.write("1", 16, false);
        stringColonne = "1";
    }
    if(colonne == 2){
        afficheur.write("COLONNE", 0, true);
        afficheur.write("2", 16, false);
        stringColonne = "2";
    }
    if(colonne == 3){
        afficheur.write("COLONNE", 0, true);
        afficheur.write("3", 16, false);
        stringColonne = "3";
    }
    if(colonne == 4){
        afficheur.write("COLONNE", 0, true);
        afficheur.write("4", 16, false);
        stringColonne = "4";
    }
    if(colonne == 5){
        afficheur.write("COLONNE", 0, true);
        afficheur.write("5", 16, false);
        stringColonne = "5";
    }
    if(colonne == 6){
        afficheur.write("COLONNE", 0, true);
        afficheur.write("6", 16, false);
        stringColonne = "6";
    }
    if(colonne == 7){
        afficheur.write("COLONNE", 0, true);
        afficheur.write("7", 16, false);
        stringColonne = "7";
    }

    colonne = colonne + 1;
}


int main() {
    Carte carte;
    uint8_t pointDepart = 1;
    uint8_t pointDestination = 1;
    Etat etatCourante = Etat::ATTENTE_DE_MODE;
    bouton.initialisationInterruptionD2();
    bouton.initialisationInterruptionSelection();
    bouton.initialisationInterruptionValidation();

    while (true) {
         switch (etatCourante) {
             case Etat::ATTENTE_DE_MODE:
                 robot.allumeLedRouge();
                 if (boutonInterruption == 1) {
                     boutonInterruption = 0;
                     etatCourante = Etat::IDENTIFICATION_COIN;
                 }
                 if (boutonSelection == 1) {
                     boutonSelection = 0;
                     if (bouton.debounceSelection()) {
                         boutonSelection = 0;
                         etatCourante = Etat::SELECTION_TRAJET_LIGNE;
                         boutonValidation = 0;
                         selectionTrajetLigne();
                     }
                 }
                 break;

             case Etat::IDENTIFICATION_COIN:
                 robot.eteindreLed();
                 _delay_ms(2000);
                 //robot.clignoteVert4hz();
                 robot.collecteDonnee(125);
                 robot.identificationPosition();
                 _delay_ms(2000);
                 //robot.eteindreClignotement4hz();
                 //robot.allumeLedVert();
                 afficherCoin(robot.getCombinaisonTrouvee());
                 _delay_ms(10000);
                 afficheur.clear();
                 etatCourante = Etat::ATTENTE_DE_MODE;
                 break;

    //         case Etat::SELECTION_TRAJET_LIGNE:
    //             if (boutonSelection == 1) {
    //                 boutonSelection = 0;
    //                 if (bouton.debounceSelection()) {
    //                     boutonSelection = 0;
    //                     selectionTrajetLigne();
    //                 }
    //             }
    //             if (boutonValidation == 1) {
    //                 boutonValidation = 0;
    //                 if (bouton.debounceValidation()) {
    //                     boutonValidation = 0;
    //                     etatCourante = Etat::SELECTION_TRAJET_COLONNE;
    //                     selectionTrajetColonne();
    //                 }
    //             }
    //             break;

    //         case Etat::SELECTION_TRAJET_COLONNE:
    //             if (boutonSelection == 1) {
    //                 boutonSelection = 0;
    //                 if (bouton.debounceSelection()) {
    //                     boutonSelection = 0;
    //                     selectionTrajetColonne();
    //                 }
    //             }
    //             if (boutonValidation == 1) {
    //                 boutonValidation = 0;
    //                 if (bouton.debounceValidation()) {
    //                     boutonValidation = 0;
    //                     etatCourante = Etat::CONFIRMATION_TRAJET;
    //                     validationTrajet();
    //                 }
    //             }
    //             break;

    //         case Etat::CONFIRMATION_TRAJET:

    //             if (validation == 1) { robot.allumeLedRouge(); }
    //             if (validation == 2) { robot.allumeLedVert(); }

    //             if (boutonSelection == 1) {
    //                 boutonSelection = 0;
    //                 if (bouton.debounceSelection()) {
    //                     boutonSelection = 0;
    //                     validationTrajet();
    //                 }
    //             }
    //             if (boutonValidation == 1) {
    //                 boutonValidation = 0;
    //                 if (bouton.debounceValidation()) {
    //                     if (validation == 1) {
    //                         etatCourante = Etat::EXECUTION_TRAJET;
    //                     }
    //                     if (validation == 2) {
    //                         etatCourante = Etat::SELECTION_TRAJET_LIGNE;
    //                         ligne = 1;
    //                         colonne = 1;
    //                         selectionTrajetLigne();
    //                     }
    //                 }
    //             }
    //             break;

    //         case Etat::EXECUTION_TRAJET:
    //             robot.eteindreLed();
    //             afficheur.clear();
    //             // pointDestination = trouverIdPoint(ligne, colonne, carte);
    //             // uint8_t* pointsTrajet = carte.dijkstra(pointDepart, pointDestination);
    //             // robot.faireTrajet( pointsTrajet);
    //             break;

    //         // case Etat::RENCONTRE_OBSTACLE:
    //         //     break;

    //         // case Etat::FIN_TRAJET:
    //         //     break;
         }
    }
    //while(true){
    //_delay_ms(20);
    //robot.reactionAuxLignes(0 ,125); 
   // }
    

    // robot.collecteDonnee(125);
    // robot.allumeLedRouge();
    // uint8_t comb = robot.getCombinaisonTrouvee();
    // afficherCoin(comb);
    // if (robot.getcompteurTimer0_() > 50) {
    //     robot.allumeLedRouge();
    // }
}

// //-----------------------------------------------------------------------------------------------------------------------------------------------

// int main() {


    // Moteur mot;
    // mot.initialisation(); // 125 = bon ratio

    //test rouler en avant
    // mot.initialiseDirectionAvance();
    // mot.roulerToutDroit(125);
    // _delay_ms(5000);
    // mot.arreterMoteur();

    // //Test tourner droite
    // mot.tournerDroite(125);
    // _delay_ms(5000);
    // mot.arreterMoteur();

    // // test tourner gauche
    // mot.tournerGauche(125);
    // _delay_ms(5000);
    // mot.arreterMoteur();

    // //test tourner 180
    // _delay_ms(500);
    // mot.tourner180Gauche(125);
    // _delay_ms(4000);
    // mot.arreterMoteur();

    // // TEST LED CLIGNOTEMENT 4 HZ ---------------------------------------------------------------------------TODO
    // Robot bob;
    // Bouton bout;
    // bout.initialisationInterruptionD2();
    // bob.allumeLedRouge();
    // _delay_ms(1000);
    // bob.eteindreLed();

    // // FONCTION FINIT -> A GARDER !!
    // bob.clignoteVert4hz();
    // while (true) {
    //     if (gActivationLed == 0) {
    //         bob.allumeLedVert();
    //     }
    //     else {
    //         bob.eteindreLed();
    //     }
    // }

    // while (true) {
    //     if (gActivationLed == 0) {
    //         bob.eteindreLed();
    //     }
    //     else {
    //         bob.allumeLedVert();
    //     }
    //     if (compteur8Led >= 1) {
    //         bob.allumeLedRouge();
    //     }
    // }

    //---------------------------------------------------------------------------------------------------------

    // TEST MOTEUR ---------------------------------------------------------------------------------------------
    // Moteur moteur;
    // led1.allumerRouge();
    // _delay_ms(2000);
    // led1.eteindre();
    // moteur.initialisation();
    // moteur.tournerGauche();

    // while (true);


    //-----------------------------------------------------------------------------------------------------------


    // TEST CAPTEUR INFRA ROUGE-----------------------------------------------------------------------------DONE
    // while(true){
    //     capteur.lectureSignalInfraRouge();
    //     if (capteur.poteauTrouve()) {
    //         led1.allumerRouge();
    //         _delay_ms(500);
    //         led1.eteindre();
    //         _delay_ms(500);
    //     }
    // }
    // if (capteur.getVoltageNumerique() > 20) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 30) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 40) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 50) {     // quand ya rien on est ici tabarnak de criss
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 60) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 70) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 80) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 90) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 100) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 110) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 120) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 130) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 140) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 150) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 160) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 170) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 180) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 190) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 200) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 210) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 220) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 230) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }
    // if (capteur.getVoltageNumerique() > 240) {
    //     led1.allumerRouge();
    //     _delay_ms(500);
    //     led1.eteindre();
    //     _delay_ms(500);
    // }


    //------------------------------------------------------------------------------------------------------

    // TEST DES 3 BOUTONS POUSSOIR -------------------------------------------------------------------------TODO

    //-------------------------------------------------------------------------------------------------------

    // TEST MAKER LINE -------------------------------------------------------------------------------------DONE

    //------------------------------------------------------------------------------------------------------

    // TEST AFFICHEUR LCD -------------------------------------------------------------------------------------TODO
    // LCM afficheur(&DDRC, &PORTC);
    // afficheur.en_blink(true);
    // _delay_ms(2000);
    // afficheur.put('t').put('e').put('s').put('t');
    // _delay_ms(6000);
    // afficheur.clear();
    // _delay_ms(1000);

    // afficheur.write("Ligne1", 0, false);
    // _delay_ms(2000);
    // afficheur.write("1", 16, false);
    // _delay_ms(6000);

    //---------------------------------------------------------------------------------------------------------


//     return 0;
// }