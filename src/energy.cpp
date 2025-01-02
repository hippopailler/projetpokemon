#include "energy.h"
#include <iostream>

// Création
energyList::energyList() : _energy() {} // là je sais pas trop comment gérer si c'est vide

// Conversion d'un vecteur d'énergie en une energyList
// Je pense que ce sera plus simple d'implémenter les moves avec des vecteurs donc voilà
// _energy[e]++ incrémente de 1 _energy[e] si existence, sinon initialise à 0 puis incrémente
// attention, à priori il n'y a pas tous les types dans le dico
energyList::energyList(const std::vector<typeEnergy> &energies){
    for(const typeEnergy &e : energies) 
        _energy[e]++;
}

// Accesseur
// Renvoie le nombre total d'énergie
int energyList::energyAmount() const{
    int total = 0;
    for(auto const x : _energy){
        total += x.second;
    }
    return total;
}

// Etant donné une energyList (d'une atk par ex), vérifie si on a assez d'énergie
bool energyList::enoughEnergy(const energyList &cost){
    // On vérifie si le nombre d'énergie est suffisant
    if (energyAmount() < cost.energyAmount()){
        return false;
    }
    // On vérifie si on a les énergies spécifiques nécessaires
    for (auto const x : cost._energy){
        if (x.first != COLORLESS && _energy[x.first] < x.second){
            return(false);
        }
    }

    return(true);
}

// Mutateur
// ajout d'une énergie
void energyList::operator+=(const typeEnergy energy){
    _energy[energy]++;
}

// ajout de plusieurs énergies
void energyList::operator+=(const energyList &energies){
    for (auto const x : energies._energy){
        _energy[x.first] += x.second;
    }
}

void energyList::operator-=(const typeEnergy energy){
    if(_energy[energy] < 1){
        std::cout << "Impossible d'avoir un nombre négatif d'énergies\n";
        return;
    }
    _energy[energy]--;
}

void energyList::operator-=(const energyList &energies){
    for (auto const x : energies._energy){
        if(_energy[x.first] < x.second){
            std::cout << "Impossible d'avoir un nombre négatif d'énergies\n";
            return;
        }
    }

    for (auto const x : energies._energy){
        _energy[x.first] -= x.second;
    }
}