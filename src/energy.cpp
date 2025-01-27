#include "energy.h"
#include <iostream>

typeEnergy stringToTypeEnergy(const std::string& type) {
    if (type == "COLORLESS") return COLORLESS;
    if (type == "GRASS") return GRASS;
    if (type == "FIRE") return FIRE;
    if (type == "WATER") return WATER;
    if (type == "LIGHTING") return LIGHTING;
    if (type == "PSYCHIC") return PSYCHIC;
    if (type == "FIGHTING") return FIGHTING;
    if (type == "DARKNESS") return DARKNESS;
    if (type == "METAL") return METAL;
    if (type == "DRAGON") return DRAGON;
    throw std::invalid_argument("Unknown type: " + type);
}

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

energyList::energyList(const typeEnergy &energy){
    _energy[energy]++;
}

std::string typeEnergyToString(const typeEnergy& type) {
    switch (type) {
        case COLORLESS: return "normale";
        case GRASS: return "plante";
        case FIRE: return "feu";
        case WATER: return "eau";
        case LIGHTING: return "électrique";
        case PSYCHIC: return "psy";
        case FIGHTING: return "combat";
        case DARKNESS: return "ténèbre";
        case METAL: return "métal";
        case DRAGON: return "dragon";
        default: return "inconnue";
    }
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

energyList energyList::coverWith(const energyList &cost) const{
    energyList coverage;
    for (auto const& x : cost._energy){
        if (x.first == COLORLESS) {
            unsigned int remaining = x.second;
            for (auto& y : _energy) {
                if (remaining == 0) break;
                if (y.second > 0) {
                    // Le nombre d'énergie qu'on va utliser pour cover les énergies normales
                    // Autant que possible 
                    unsigned int used = std::min(y.second, remaining);
                    coverage._energy[y.first] += used;
                    remaining -= used;
                }
            }
        } else {
            coverage._energy[x.first] = x.second;
        }
    }
    return coverage;
}

std::map<typeEnergy, unsigned int> energyList::energy() const{
    return _energy;
}

void energyList::print() const{
    for (auto const x : _energy){
        std::cout << " " << x.second << " énergies " << typeEnergyToString(x.first) << ",";
    }
}

// Mutateurs
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