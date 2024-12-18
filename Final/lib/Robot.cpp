#include "Robot.h"

Robot::Robot() { 
    DDRB |= (1 << PORTB1) | (1 << PORTB0); // Configure les pins de la DEL en sortie
    ledRobot_.initialisation(&PORTB, 0, 1);  // a changer manuellement
    infraRougeRobot_.setPlacementPin(2); // a changer manuellement 
    moteurRobot_.initialisation();
}

// --------------------------------------------------- LED -----------------------------------
void Robot::clignoteVert4hz() {
    minuterieRobot_.activerInterruptionTimer2();
    minuterieRobot_.partirTimer2CTC(TEMPS_INCREMENTATION_TIMER2); //255
    // Dans le main -> ISR(TIMER2_COMP_vect) 
}

void Robot::eteindreClignotement4hz() {
    minuterieRobot_.desactiverInterruptionTimer2(); 
    minuterieRobot_.desactivationTimer2();
}

void Robot::allumeLedVert() { 
    etatLed_ = 1; 
    ledRobot_.allumerVert(); 
}

void Robot::allumeLedRouge() { 
    etatLed_ = 2; 
    ledRobot_.allumerRouge(); 
}

void Robot::eteindreLed() { 
    etatLed_ = 0; 
    ledRobot_.eteindre(); 
}

uint8_t Robot::getEtatLedRobot() { 
    return etatLed_;  
}

//-----------------------------------------RECHERCHE POTEAU---------------------------------------------- 
bool Robot::recherchePoteau() { 
    infraRougeRobot_.lectureSignalInfraRouge();
    if (infraRougeRobot_.poteauTrouve()) {
        return true;
    }
    else { return false; } 
}
// -----------------------------------------------------------------------------------------------------

// ----------------------------------------------MOVEMENT ROBOT-----------------------------
void Robot::immobilisationRobot() {
    moteurRobot_.arreterMoteur();
}

void Robot::robotRoulerDroit(uint8_t ratio) {
    moteurRobot_.initialiseDirectionAvance();
    moteurRobot_.roulerToutDroit(ratio); // ratio a ajuster
}

void Robot::robotTourneGauche(uint8_t ratio) {
    _delay_ms(1100);
    immobilisationRobot();
    _delay_ms(1000); // a tester 

    moteurRobot_.tournerGauche(ratio);
    while (true) {
        if (makerLineRobot_.DetecteRien()) {
            while (true) {
                if (makerLineRobot_.DetectionTournage()) { 
                    immobilisationRobot();
                    moteurRobot_.initialiseDirectionAvance(); 
                    _delay_ms(1500);
                    return; 
                }
            }
        }
    }
}

void Robot::robotTourneDroite(uint8_t ratio) {
    _delay_ms(1100);
    immobilisationRobot();
    _delay_ms(1000); // a tester 

    moteurRobot_.tournerDroite(ratio);
    while (true) {
        if (makerLineRobot_.DetecteRien()) {
            while (true) {
                if (makerLineRobot_.DetectionTournage()) { 
                    immobilisationRobot();
                    moteurRobot_.initialiseDirectionAvance(); 
                    _delay_ms(1500);
                    return; 
                }
            }
        }
    }
}

void Robot::robotTourne180(uint8_t ratio) {
    moteurRobot_.tourner180Gauche(ratio);
    _delay_ms(3000); // a verifier
    while (true) {
        if (makerLineRobot_.DetectionTournage()) { 
            immobilisationRobot();
            moteurRobot_.initialiseDirectionAvance(); 
            _delay_ms(1500);
            return; 
        }
    }
}

// ----------------------------------------------MOVEMENT ROBOT-----------------------------

// ---------------------------------------------REACTION AUX LIGNES-------------------------

void Robot::setDirection(uint8_t direction) {
    directionRobot_ = direction; 
} 

void Robot::reactionAuxLignes(uint8_t direction, uint8_t ratio) 
{
    directionRobot_ = direction; 
    if (makerLineRobot_.DetecteRien()) {
        immobilisationRobot(); // peut etre a changer 
    }

    else if (makerLineRobot_.IntersectionGauche()) { 
        if (directionRobot_ == 0) {
            robotTourneGauche(ratio);
        }
        else if (directionRobot_ == 2) {
            robotRoulerDroit(ratio);
        }
        else if (directionRobot_ == 3) {
            robotTourne180(ratio);
        }
    }

    else if (makerLineRobot_.IntersectionDroite()) {
        if (directionRobot_ == 1) {
            robotTourneDroite(ratio);
        }
        else if (directionRobot_ == 2) {
            robotRoulerDroit(ratio); 
        }
        else if (directionRobot_ == 3) {
            robotTourne180(ratio);
        }
    }

    else if (makerLineRobot_.CheminDroit()) {
        if (directionRobot_ == 3) {
            robotTourne180(ratio);
        }
        else { robotRoulerDroit(ratio); }
    }
 
    else if (makerLineRobot_.CheminDroitDroite()) { // si on tilte vers la droite
        moteurRobot_.initialiseDirectionAvance();
        uint8_t correcteurRoueDroite = ratio - 5;  // on veut qua laille plus vite
        uint8_t correcteurRoueGauche = ratio; 
        moteurRobot_.initialiseRatioPWM(correcteurRoueDroite, correcteurRoueGauche); 
        if (directionRobot_ == 3) {
            robotTourne180(ratio);
        }
    }

    else if (makerLineRobot_.CheminDroitGauche()) { // si on tilte vers la gauche
        moteurRobot_.initialiseDirectionAvance();
        uint8_t correcteurRoueDroite = ratio + 10;  
        uint8_t correcteurRoueGauche = ratio - 25;
        moteurRobot_.initialiseRatioPWM(correcteurRoueDroite, correcteurRoueGauche);
        if (directionRobot_ == 3) {
            robotTourne180(ratio);
        }
    }

    else if (makerLineRobot_.GrosseIntersection()) {
        if (directionRobot_ == 0) {
            robotTourneGauche(ratio);
        }
        else if (directionRobot_ == 1) {
            robotTourneDroite(ratio);
        }
        else if (directionRobot_ == 2) {
            robotRoulerDroit(ratio);
        }   
        else if (directionRobot_ == 3) {
            robotTourne180(ratio);
        }
    }
}
// // ---------------------------------------------REACTION AUX LIGNES-------------------------

// Cette fonction va être utilisée pour trouver les diverses informations dont a besoin qui sont
// le nombre d'intersections à droite, le nombre d'intersection à gauche, le temps pour atteindre la première
// intersection et le temps pour compléter le trajet (le moment où il n'y a plus de ligne avant de revenir à la position initiale)

uint8_t Robot::getCombinaisonTrouvee() {
    return combinaisonTrouvee_;    // 1 == Coin(1,1),Est , 2 == Coin(1,1), Sud 3 == Coin(1,7) Sud, 4 == Coin(1,7) Ouest,
}                                   // 5 == Coin (4,1) Nord , 6 == Coin (4,1) Est , 7 == (4,7) Ouest , 8 == (4,7) Nord

void Robot::incrementeCompteurTimer0() {
    compteurTimer0_++; 
}

void Robot::collecteDonnee(uint8_t ratio)
{
    minuterieRobot_.activerInterruptionTimer0();
    minuterieRobot_.partirTimer0CTC(TEMPS_INCREMENTATION_TIMER0);

    while (!(makerLineRobot_.DetecteRien()))
    {
        eteindreLed();
        reactionAuxLignes(2, ratio); 
        if ((makerLineRobot_.IntersectionDroite() || makerLineRobot_.IntersectionGauche()) && compteurIntersection_ != 1)
        {
            tempsPremiereIntersection_ = compteurTimer0_;
            compteurIntersection_ += 1;
        }
        if (makerLineRobot_.IntersectionDroite())
        {
            nombreIntersectionDroite_ += 1;
            allumeLedRouge();
            _delay_ms(300); // Necessaire pcq sinon on re-rentre dans la fonction x fois
        }
        if (makerLineRobot_.IntersectionGauche())
        {
            nombreIntersectionGauche_ += 1;
            allumeLedVert();
            _delay_ms(300); // Necessaire pcq sinon on re-rentre dans la fonction x fois
        }
        _delay_ms(10); // Necessaire ! 
    }
    eteindreLed();
    _delay_ms(600); // delai pour avancer un peu avant de 180
    immobilisationRobot();

    tempsChemin_ = compteurTimer0_;
    minuterieRobot_.desactiverInterruptionTimer0();
    minuterieRobot_.desactivationTimer0(); 
    _delay_ms(1000);
    robotTourne180(ratio);
    while (!(makerLineRobot_.DetecteRien()))
    {
        reactionAuxLignes(2, ratio);
        _delay_ms(40);
    }
    _delay_ms(800);  // delai pour avancer un peu avant de 180
    immobilisationRobot();
    _delay_ms(1000);
    robotTourne180(ratio); 
 
    if (nombreIntersectionDroite_ == 3) { allumeLedRouge(); }
    if (nombreIntersectionDroite_ == 2) { allumeLedVert(); }
    if (nombreIntersectionDroite_ == 1) { 
        allumeLedRouge();
        _delay_ms(1000);
        eteindreLed();
    }
    if (nombreIntersectionGauche_ == 3) { allumeLedRouge(); }
    if (nombreIntersectionGauche_ == 2) { allumeLedVert(); }
    if (nombreIntersectionGauche_ == 1) { 
        allumeLedRouge();
        _delay_ms(1000);
        eteindreLed();
    }
}

// Avec les informations trouvées dans la méthode collecteDonnee, on va pouvoir trouver le sens et les coordonnees
// du coin initial en regardant les caractéristiques propres à chaque coin.
void Robot::identificationPosition()
{
    if (nombreIntersectionDroite_ == 2 && tempsPremiereIntersection_ > TEMPS_75_POURCENT)
    {
        combinaisonTrouvee_ = 1; //ok
    }
    else if (nombreIntersectionGauche_ == 1 && tempsPremiereIntersection_ < TEMPS_75_POURCENT  && tempsChemin_ < TEMPS_75_POURCENT)
    {
        combinaisonTrouvee_ = 2; //ok
    }
    else if (nombreIntersectionDroite_ == 2 && tempsPremiereIntersection_ < TEMPS_75_POURCENT)
    {
        combinaisonTrouvee_ = 3; //ok
    }
    else if (nombreIntersectionGauche_ == 1 && tempsPremiereIntersection_ < TEMPS_75_POURCENT && tempsChemin_ > TEMPS_75_POURCENT) 
    {
        combinaisonTrouvee_ = 4; //ok
    }
    else if (nombreIntersectionDroite_ == 1)
    {
        combinaisonTrouvee_ = 5; //ok
    }
    else if (nombreIntersectionGauche_ == 1 && tempsPremiereIntersection_ > TEMPS_75_POURCENT && tempsChemin_ > TEMPS_75_POURCENT)
    {
        combinaisonTrouvee_ = 6; //ok
    }
    else if (nombreIntersectionDroite_ == 3)
    {
        combinaisonTrouvee_ = 7; //ok
    }
    else if (nombreIntersectionGauche_ == 2)
    {
        combinaisonTrouvee_ = 8; //ok
    }
    nombreIntersectionGauche_ = 0;
    nombreIntersectionDroite_ = 0;
    tempsPremiereIntersection_ = 0;
    compteurIntersection_ = 0; 
    tempsChemin_ = 0; 
    compteurTimer0_ = 0; 
}

void Robot::tournerGauche(){
    // if(sur le point d'intersection){
    //     robotTourneGauche();
    // }
    while(tournageGaucheEffectue == false){
        reactionAuxLignes(0, 125);
        _delay_ms(20); 
    }
    tournageGaucheEffectue = false;
}

void Robot::tournerDroite(){
    // if(sur le point d'intersection){
    //     robotTourneDroite();
    // }
    while(tournageDroiteEffectue == false){
        reactionAuxLignes(1, 125);
        _delay_ms(20); 
    }
    tournageDroiteEffectue = false;
}

void Robot::allerToutDroit(){
    while(true){
        reactionAuxLignes(2, 125);
        _delay_ms(20); 
    }
}

void Robot::faireTrajet(uint8_t* pointsTrajet){
    uint8_t pointActuel ;
    uint8_t pointProchain ;
    uint8_t i = 0;

    while( pointsTrajet[i] != 0){
        pointActuel = pointsTrajet[i];
        pointProchain = pointsTrajet[i+1];
        uint8_t difference = pointProchain - pointActuel;
        switch (direction_)

        {

        case DirectionF::EST:
            if(difference == 1){
                // aller tout droit
                allerToutDroit();
                direction_ = DirectionF::EST;
            }else if(difference == 7){
                // tourne a droite
                // aller tout droit
                tournerDroite();
                allerToutDroit();
                direction_ = DirectionF::SUD;
            }else if(difference == -1){
                // faire 180 degree
                // aller tout droit
                robotTourne180(125);
                allerToutDroit();
                direction_ = DirectionF::OUEST;
            }else if(difference == -7){
                // tourne a gauche
                // aller tout droit
                tournerGauche();
                allerToutDroit();
                direction_ = DirectionF::NORD;
            }
            break; //done
        case DirectionF::SUD:
       // }else if(pointProchain - pointActuel == 7){
            if(difference == 1){
                //tourner a gauche
                // aller tout droit
                tournerGauche();
                allerToutDroit();
                direction_ = DirectionF::EST;
            }else if(difference == 7){
                // aller tout droit
                allerToutDroit();
                direction_ = DirectionF::SUD;
            }else if(difference == -1){
                // tourner a droite
                // aller tout droit
                tournerDroite();
                allerToutDroit();
                direction_ = DirectionF::OUEST;
            }else if(difference == -7){
                // faire 180
                // aller tout droit
                robotTourne180(125);
                allerToutDroit();
                direction_ = DirectionF::NORD;
            }
            break; // done
        case DirectionF::OUEST:
      //  }else if(pointActuel - pointProchain == -1){
            if(difference == 1){
                // faire 180
                // aller tout droit
                robotTourne180(125);
                allerToutDroit();
                direction_ = DirectionF::EST;
            }else if(difference == 7){
                // tourne a gauche
                // aller tout droit
                tournerGauche();
                allerToutDroit();
                direction_ = DirectionF::SUD;
            }else if(difference == -1){
                // aller tout droit
                allerToutDroit();
                direction_ = DirectionF::OUEST;
            }else if(difference == -7){
                // tourne a droite
                // aller tout droit
                tournerDroite();
                allerToutDroit();
                direction_ = DirectionF::NORD;
            }
            break; // done
        case DirectionF::NORD:
       // }else if(pointProchain - pointActuel == -7){
            if(difference == 1){
                // tourner a droite
                // aller tout droit
                tournerDroite();
                allerToutDroit();
                direction_ = DirectionF::EST;
            }else if(difference == 7){
                // faire 180
                // aller tout droit
                robotTourne180(125);
                allerToutDroit();
                direction_ = DirectionF::SUD;
            }else if(difference == -1){
                // tourner a gauche
                // aller tout droit
                tournerGauche();
                allerToutDroit();
                direction_ = DirectionF::OUEST;
            }else if(difference == -7){
                // aller tout droit
                allerToutDroit();
                direction_ = DirectionF::NORD;
            }
            break;
        }
        i++;
        
    }
}

