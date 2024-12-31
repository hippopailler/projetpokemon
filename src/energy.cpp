#include "energy.h"

// Création
energyList::energyList() {} // là je sais pas trop comment gérer si c'est vide

// Conversion d'un vecteur d'énergie en une energyList
// Je pense que ce sera plus simple d'implémenter les moves avec des vecteurs donc voilà
// _energy[e]++ incrémente de 1 _energy[e] si existence, sinon initialise à 0 puis incrémente
// attention, à priori il n'y a pas tous les types dans le dico
energyList::energyList(const std::vector<type> &energies){
    for(const type &e : energies) 
        _energy[e]++;
}

// Accesseur
bool energyList::enoughEnergy(energyList cost){
    return(true);
}

// Mutateur
void energyList::operator+=(const type energy){

}

void energyList::operator+=(const energyList &energy){

}

void energyList::operator-=(const type energy){

}

void energyList::operator-=(const energyList &energy){

}