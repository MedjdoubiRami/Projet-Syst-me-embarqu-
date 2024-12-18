#ifndef CARTE_H
#define CARTE_H

#include "Point.h"
#include "Arc.h"



#define F_CPU 8000000UL


class Carte {
    private:
       // Point points_[28];
        Arc arcs_[70];
     //   int poids_[28][28] ;
    public:
        Carte();
        uint8_t* dijkstra(uint8_t pointDepart, uint8_t pointFinal);
        void retirerPoint(uint8_t tableauPoints[], uint8_t& taille, uint8_t pointARetirer);
        uint8_t distanceMinimale(uint8_t pointCourant, uint8_t pointsNonVisites[], uint8_t distance[], uint8_t tailleTabNonVisites);
        void initialisationTab(uint8_t distances[], uint8_t pointDepart, uint8_t pointsNonVisites[], uint8_t parent[]);
        uint8_t getProche(bool pointsVisites[], uint8_t distance[]);
        void inverserTableau(uint8_t tableau[], uint8_t taille);
     //   uint8_t* getTabPoints();

        Point points_[28];
};
#endif 