/*
 * Nom des auteurs: Othmane Azzam, Jordan Filion, Yanni Si-Hocine, Rami Medjdoubi, Nema Babah et Naji Bou-Aoun
 *
 * Description du programme: Cette classe permet de creer un objet Led avec les caracteristiques suivantes : PORT, pair de broches. 
 *                           La classe contient des methodes pour allumer en rouge, vert, ambre et on peut eteindre la Led. 
 * 
 * Identifications matérielles (Broches I/O): Le choix du PORT est celui de l'utilisateur entre PORTD, PORTC, PORTB, PORTA
 *                                            Le choix des broches du PORT est celui de l'utilisateur (0,1), (2,3), (4,5), (6,7)
 *                                            positionPinNegative_ doit etre connecter au cathode(-) des broches de la DEL libre
 *                                            positionPinPositive_ doit etre connecter a l'anode(+) des broches de la DEL libre
 */
#ifndef LED_H
#define LED_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

class Led 
{
public:
    Led(volatile uint8_t* port, uint8_t positionPinNegatif, uint8_t positionPinPositif);
    Led() = default;
    ~Led() = default;  

    void initialisation(volatile uint8_t* port, uint8_t positionPinNegatif, uint8_t positionPinPositif);
    void allumerRouge();
    void allumerVert();
    void allumerAmbre(uint16_t durerAllumageMS);
    void eteindre();

private:
    volatile uint8_t* port_;
    uint8_t positionPinNegatif_;
    uint8_t positionPinPositif_; 
};

#endif