// - Selon chaque pin et sorti du capteur faire des if avec le signal par scrutation (HIGH LOW)

// Branchements du MakerLine :
//      PORTA3 -> S5    (fil blanc)
//      PORTA4 -> S4    (fil blanc)
//      PORTA5 -> S3    (fil mauve)
//      PORTA6 -> S2    (fil bleu)
//      PORTA7 -> S1    (fil vert)
//      PORTA VCC -> fil rouge
//      PORTA GND -> fil rouge

#include "CapteurMakerLine.h"

CapteurMakerLine::CapteurMakerLine() {
    DDRA &= ~((1 << PORTA3) | (1 << PORTA4) | (1 << PORTA5) | (1 << PORTA6) | (1 << PORTA7));
}

bool CapteurMakerLine::IntersectionGauche() {
    uint8_t mask1 = (1 << PINA5) | (1 << PINA6) | (1 << PINA7); // les pins a 1
    uint8_t mask1B = (1 << PINA3) | (1 << PINA4); // les pins a 0

    uint8_t mask2 = (1 << PINA4)| (1 << PINA5) | (1 << PINA6) | (1 << PINA7); // les pins a 1
    uint8_t mask2B = (1 << PINA3); // les pins a 0

    if ((((PINA & mask1) == mask1) && ((PINA & mask1B) == 0)) ||
        (((PINA & mask2) == mask2) && ((PINA & mask2B) == 0))) {
        return true;
    }
    return false;
 }

bool CapteurMakerLine::IntersectionDroite() { // DONE
    uint8_t mask1 = (1 << PINA3) | (1 << PINA4) | (1 << PINA5); // les pins a 1
    uint8_t mask1B = (1 << PINA6) | (1 << PINA7); // les pins a 0

    uint8_t mask2 = (1 << PINA3) | (1 << PINA4) | (1 << PINA5) | (1 << PINA6); // les pins a 1
    uint8_t mask2B = (1 << PINA7); // les pins a 0

    if ((((PINA & mask1) == mask1) && ((PINA & mask1B) == 0)) ||
        (((PINA & mask2) == mask2) && ((PINA & mask2B) == 0))) {
        return true;
    }
    return false;
}

 bool CapteurMakerLine::CheminDroit() {
    uint8_t mask1 = (1 << PINA5); // les pins a 1
    uint8_t mask1B = (1 << PINA3) | (1 << PINA4) | (1 << PINA6) | (1 << PINA7); // les pins a 0

    uint8_t mask2 = (1 << PINA4) | (1 << PINA5) | (1 << PINA6); // les pins a 1
    uint8_t mask2B = (1 << PINA3) | (1 << PINA7); // les pins a 0 

    if ((((PINA & mask1) == mask1) && ((PINA & mask1B) == 0)) ||
        (((PINA & mask2) == mask2) && ((PINA & mask2B) == 0))) {
        return true;
    }
    return false;
 }

bool CapteurMakerLine::CheminDroitDroite() {
    uint8_t mask1 = (1 << PINA5) | (1 << PINA6); // les pins a 1
    uint8_t mask1B = (1 << PINA3) | (1 << PINA4) | (1 << PINA7); // les pins a 0

    uint8_t mask2 = (1 << PINA6); // les pins a 1
    uint8_t mask2B = (1 << PINA3) | (1 << PINA4) | (1 << PINA5) | (1 << PINA7); // les pins a 0

    if ((((PINA & mask1) == mask1) && ((PINA & mask1B) == 0)) ||
        (((PINA & mask2) == mask2) && ((PINA & mask2B) == 0))) {
        return true;
    }
    return false;
}

bool CapteurMakerLine::CheminDroitGauche() {
    uint8_t mask1 = (1 << PINA4) | (1 << PINA5); // les pins a 1
    uint8_t mask1B = (1 << PINA3) | (1 << PINA6) | (1 << PINA7); // les pins a 0

    uint8_t mask2 = (1 << PINA4); // les pins a 1
    uint8_t mask2B = (1 << PINA3) | (1 << PINA5) | (1 << PINA6) | (1 << PINA7); // les pins a 0

    if ((((PINA & mask1) == mask1) && ((PINA & mask1B) == 0)) ||
        (((PINA & mask2) == mask2) && ((PINA & mask2B) == 0))) {
        return true;
    }
    return false;
}

bool CapteurMakerLine::GrosseIntersection() {
    uint8_t mask = (1 << PINA3) | (1 << PINA4) | (1 << PINA5) | (1 << PINA6) | (1 << PINA7); // les pins a 1 

    if ((PINA & mask) == mask) {
        return true;
    }
    return false; 
}

bool CapteurMakerLine::DetecteRien() {
    uint8_t mask = (1 << PINA3) | (1 << PINA4) | (1 << PINA5) | (1 << PINA6) | (1 << PINA7); // les pins a 0 

    if ((PINA & mask) == 0) {
        return true;
    }
    return false; 
}
 
bool CapteurMakerLine::DetectionTournage() {
    // Quand on tourne a droite
    uint8_t mask1 = (1 << PINA5) | (1 << PINA4); // les pins a 1
    uint8_t mask1B = (1 << PINA3) | (1 << PINA6) | (1 << PINA7); // les pins a 0

    // Quand on tourne a gauche
    uint8_t mask2 = (1 << PINA6) | (1 << PINA5); // les pins a 1
    uint8_t mask2B = (1 << PINA3) | (1 << PINA4) | (1 << PINA7); // les pins a 0

    if ((((PINA & mask1) == mask1) && ((PINA & mask1B) == 0)) ||
        (((PINA & mask2) == mask2) && ((PINA & mask2B) == 0))) {
        return true;
    }
    return false;
}


