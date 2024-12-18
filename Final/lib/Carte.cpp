#include "Carte.h"



Carte::Carte(){
    uint8_t pointId = 1;


    //Arc(uint8_t pointId, uint8_t pointSuivantId, uint8_t etat, uint8_t poids);
        uint8_t map[][4] = {{1,2,1,1},{1,8,1,1},{2,1,1,1},{2,3,1,1},{3,2,1,1},{3,4,1,1},{3,10,1,1},
                        {4,3,1,1},{4,11,1,1},{5,6,1,1},{6,5,1,1},{6,7,1,2},{6,13,1,2},{7,6,1,2},
                        {7,14,1,1},{8,9,1,5},{8,1,1,1},{9,8,1,5},{9,10,1,1},{9,16,1,1},{10,9,1,1},
                        {10,3,1,1},{10,17,1,5},{11,4,1,1},{11,12,1,2},{12,1,1,2},{12,13,1,1},
                        {12,19,1,5},{13,12,1,1},{13,6,1,2},{13,14,1,1},{13,20,1,1},{14,13,1,1},
                        {14,7,1,1},{14,21,1,1},{15,16,1,2},{15,22,1,5},{16,15,1,2},{16,9,1,1},
                        {16,17,1,1},{17,16,1,1},{17,10,1,5},{17,18,1,1},{17,24,1,1},{18,17,1,1},
                        {18,19,1,5},{18,25,1,1},{19,18,1,5},{19,12,1,5},{19,26,1,5},{20,13,1,1},
                        {20,27,1,1},{21,14,1,1},{21,28,1,1},{22,15,1,5},{22,23,1,1},{23,22,1,1},
                        {23,24,1,1},{24,23,1,1},{24,17,1,1},{25,26,1,2},{25,18,1,1},{26,25,1,2},
                        {26,19,1,5},{26,27,1,5},{27,26,1,5},{27,20,1,1},{27,28,1,1},{28,27,1,1},{28,21,1,1}};
        
    
        

        for(uint8_t i = 0 ; i < 4; i++){
            for(uint8_t j = 0 ; j < 7; j++){
                points_[pointId] = Point(pointId,i, j);
                pointId++;
            }
        }

        for(uint8_t i = 0 ; i < 70; i++){
           arcs_[i]= Arc(map[i][0], map[i][1],map[i][3]);
        }

}

uint8_t Carte::distanceMinimale(uint8_t pointCourant, uint8_t pointsNonVisites[], uint8_t distance[], uint8_t tailleTabNonVisites){
    uint8_t min = 150;
    uint8_t min_index = 0;

    for(uint8_t i = 0 ; i < tailleTabNonVisites; i++){
        for(uint8_t j = 1 ; j < 71; j++){
            if(arcs_[j].getPointId() == pointCourant && arcs_[j].getPointSuivantId() == pointsNonVisites[i] && arcs_[j].getEtat() == 1 && arcs_[j].getPoids() <= min){
                min = arcs_[j].getPoids();
                min_index = i+1;
            }
        }
    }
    distance[min_index-1] = min;
    return min_index;
}

// uint8_t Carte::getProche(bool pointsVisites[], uint8_t distance[]){
//     uint8_t min = 150;
//     uint8_t min_index = 0;

//     for(uint8_t i = 0 ; i < 28; i++){
//         if(!pointsVisites[i] && distance[i] < min){
//             min = distance[i];
//             min_index = i+1;
//         }
//     }
//     return min_index;
// }

void Carte::retirerPoint(uint8_t tableauPoints[], uint8_t& taille, uint8_t pointARetirer){
    for(uint8_t i = 0 ; i < taille; ++i){
            if(tableauPoints[i] == pointARetirer){
                for(uint8_t j = i ; j < taille - 1 ; ++j){
                    tableauPoints[j] = tableauPoints[j+1];
                }
                taille--;
                break;
            }
    }
}

// void Carte::initialisationTab(uint8_t distance[], uint8_t pointDepart, uint8_t pointsNonVisites[], uint8_t parent[]){
//     for (uint8_t i = 0; i < 28; ++i) {
//         distance[i] = 99;
//         pointsNonVisites[i] = i+1;
//         parent[i] = i+1;
//     }
//     distance[pointDepart - 1] = 0;
// }

// uint8_t* getTabPoints(){
//     return points_;
// }

uint8_t* Carte::dijkstra(uint8_t pointDepart, uint8_t pointFinal) {
    uint8_t distance[100];
    uint8_t tabCheminPlusCourt[28] = {0};
    uint8_t tailleTabChemin = 0;
    bool pointsVisites[100] = {0};
    uint8_t parent[28];
    
    // uint8_t poids_[9][9] = {{0,4,99,99,99,99,99,8,99},
    //                     {4,0,8,99,99,99,99,8,99},
    //                     {99,4,0,7,99,4,99,8,2},
    //                     {99,4,7,0,9,14,99,8,99},
    //                     {99,4,99,9,0,10,99,8,99},
    //                     {99,4,4,14,10,0,2,8,99},
    //                     {99,4,99,99,99,2,0,1,6},
    //                     {8,4,99,99,99,99,1,0,7},
    //                     {99,4,2,99,99,99,6,7,0}};
    
    uint8_t poids_[28][28] = {{0,1,99,99,99,99,99,1,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},  //1 done
                          {1,0,1,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},  //2 done
                          {99,1,0,1,99,99,99,99,99,1,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},   //3 done
                          {99,99,1,0,99,99,99,99,99,99,1,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},  //4 done
                          {99,99,99,99,0,1,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99}, //5 done
                          {99,99,99,99,1,0,2,99,99,99,99,99,2,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},   //6 done
                          {99,99,99,99,99,2,0,99,99,99,99,99,99,1,99,99,99,99,99,99,99,99,99,99,99,99,99,99},  //7 done
                          {1,99,99,99,99,99,99,0,5,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},  //8 done
                          {99,99,99,99,99,99,99,5,0,1,99,99,99,99,99,1,99,99,99,99,99,99,99,99,99,99,99,99},   //9 done
                          {99,99,1,99,99,99,99,99,1,0,99,99,99,99,99,99,5,99,99,99,99,99,99,99,99,99,99,99},    //10 done
                          {99,99,99,1,99,99,99,99,99,99,0,2,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99}, //11 done
                          {99,99,99,99,99,99,99,99,99,99,2,0,1,99,99,99,99,99,5,99,99,99,99,99,99,99,99,99}, //12 done
                          {99,99,99,99,99,2,99,99,99,99,99,1,0,1,99,99,99,99,99,1,99,99,99,99,99,99,99,99}, //13 done
                          {99,99,99,99,99,99,1,99,99,99,99,99,1,0,99,99,99,99,99,99,1,99,99,99,99,99,99,99}, //14 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,0,2,99,99,99,99,99,5,99,99,99,99,99,99}, //15 done
                          {99,99,99,99,99,99,99,99,1,99,99,99,99,99,2,0,1,99,99,99,99,99,99,99,99,99,99,99}, //16 done
                          {99,99,99,99,99,99,99,99,99,5,99,99,99,99,99,1,0,1,99,99,99,99,1,99,99,99,99,99}, //17 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,1,0,5,99,99,99,99,99,1,99,99,99}, //18 done
                          {99,99,99,99,99,99,99,99,99,99,99,5,99,99,99,99,99,5,0,99,99,99,99,99,99,5,99,99}, //19 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,1,99,99,99,99,99,99,0,99,99,99,99,99,99,1,99}, //20 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,1,99,99,99,99,99,99,0,99,99,99,99,99,99,1}, //21 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,5,99,99,99,99,99,99,0,1,99,99,99,99,99}, //22 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,1,0,1,99,99,99,99}, //23 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,1,99,99,99,99,99,1,0,99,99,99,99}, //24 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,1,99,99,99,99,99,99,0,2,99,99}, //25 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,5,99,99,99,99,99,2,0,5,99}, //26 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,1,99,99,99,99,99,5,0,1}, //27 done
                          {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,1,99,99,99,99,99,1,0}};//28 done

        // tabCheminPlusCourt[tailleTabChemin] = pointDepart;
        // tailleTabChemin++;
      
        //initialiser
        for (uint8_t i = 0; i < 28; ++i) {
            distance[i] = 99;
            parent[i] = i;
        }
        distance[pointDepart] = 0;
        
        // trouver le plus proche
        for (uint8_t i = 0; i < 28 ; i++){
            uint8_t min = 99;
            uint8_t min_index = 0;

            for(uint8_t j = 0 ; j < 28; j++){
                if(!pointsVisites[j] && distance[j] < min){
                    min = distance[j];
                    min_index = j;
                }
            }
   
            uint8_t proche = min_index;
            pointsVisites[proche] = true;
            
            for (uint8_t adj = 0; adj < 28 ; adj++){
                if(poids_[proche][adj] != 99 && distance[adj]>distance[proche]+poids_[proche][adj]){
                    distance[adj] = distance[proche] + poids_[proche][adj];
                    parent[adj] = proche;
                }
            }
            
            
            
        }
       
            tabCheminPlusCourt[tailleTabChemin] = pointFinal;
            tailleTabChemin++;
            uint8_t parnode = parent[pointFinal];
            while(parnode != pointDepart){
                tabCheminPlusCourt[tailleTabChemin] = parnode;
                tailleTabChemin++;
                parnode = parent[parnode];
                
            }
            tabCheminPlusCourt[tailleTabChemin] = pointDepart;
            tailleTabChemin++;
      
        uint8_t cheminFinal[tailleTabChemin]={0};
        uint8_t sizeTab = 0;
        
        for(uint8_t i = 0; i< tailleTabChemin; i++){
            cheminFinal[i] = tabCheminPlusCourt[tailleTabChemin-i-1];
        }
        
      
        
        // std::cout << "le chemin le plus court : ";
        // for(uint8_t i = 0; i< tailleTabChemin; i++){
        //     std::cout <<  cheminFinal[i] <<" " ;
        // }
        // std::cout << std::endl;
        
        return cheminFinal;
    }

    
        




 