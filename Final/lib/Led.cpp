/*
 * Nom des auteurs: Othmane Azzam, Jordan Filion, Yanni Si-Hocine, Rami Medjdoubi, Nema Babah et Naji Bou-Aoun
 *
 * Description du programme: Cette classe permet de creer un objet Led avec les caracteristiques suivantes : PORT, pair de broches. 
 *                           La classe contient des methodes pour allumer en rouge, vert, ambre et on peut eteindre la Led. 
 * 
 * Identifications matérielles (Broches I/O): Le choix du PORT est celui de l'utilisateur entre PORTD, PORTC, PORTB, PORTA
 *                                            Pour entrer un port dans le main, il faut l'ecrire comme ceci : (&PORTX)
 *                                            Le choix des broches du PORT est celui de l'utilisateur (0,1), (2,3), (4,5), (6,7)
 *                                            positionPinNegative_ doit etre connecter au cathode(-) des broches de la DEL libre
 *                                            positionPinPositive_ doit etre connecter a l'anode(+) des broches de la DEL libre
 */
#include "Led.h"

Led::Led(volatile uint8_t* port, uint8_t positionPinNegatif, uint8_t positionPinPositif) 
    : port_(port), positionPinNegatif_(positionPinNegatif), positionPinPositif_(positionPinPositif) 
    {}
                    
void Led::eteindre()
{
    *port_ &= ~(1 << positionPinNegatif_);
    *port_ &= ~(1 << positionPinPositif_);
}

void Led::initialisation(volatile uint8_t* port, uint8_t positionPinNegatif, uint8_t positionPinPositif) {
    port_ = port;
    positionPinNegatif_ = positionPinNegatif;
    positionPinPositif_ = positionPinPositif; 
}

void Led::allumerVert()
{
    *port_ |= (1 << positionPinNegatif_);
    *port_ &= ~(1 << positionPinPositif_);
}

void Led::allumerRouge()
{
    *port_ &= ~(1 << positionPinNegatif_);
    *port_ |= (1 << positionPinPositif_);
}

void Led::allumerAmbre(uint16_t durerAllumageMS) 
{
    const uint8_t DELAI_MS_ENTRE_CHANGEMENT_COULEUR = 20;
    uint16_t nbIteration = durerAllumageMS / (DELAI_MS_ENTRE_CHANGEMENT_COULEUR*2); 

    for(uint16_t i = 0; i < nbIteration ; i++)
    {
        allumerVert();
        _delay_ms(DELAI_MS_ENTRE_CHANGEMENT_COULEUR);
        allumerRouge();
        _delay_ms(DELAI_MS_ENTRE_CHANGEMENT_COULEUR);
    }
    eteindre();
}
