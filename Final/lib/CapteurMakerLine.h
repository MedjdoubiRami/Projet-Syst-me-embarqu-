// // Branchements du MakerLine :
// //      PORTA3 -> S5    (fil blanc)
// //      PORTA4 -> S4    (fil blanc)
// //      PORTA5 -> S3    (fil mauve)
// //      PORTA6 -> S2    (fil bleu)
// //      PORTA7 -> S1    (fil vert)
// //      PORTA VCC -> fil rouge
// //      PORTA GND -> fil rouge 


#ifndef CAPTEUR_MAKER_LINE_H
#define CAPTEUR_MAKER_LINE_H

#define F_CPU 8000000UL
#include <avr/io.h>

class CapteurMakerLine {
public:
    CapteurMakerLine();
    ~CapteurMakerLine() = default;

    bool IntersectionGauche();
    bool IntersectionDroite();
    bool CheminDroit();
    bool GrosseIntersection();
    bool DetecteRien();

    bool CheminDroitDroite();
    bool CheminDroitGauche();
    bool DetectionTournage();

    private:

};
#endif