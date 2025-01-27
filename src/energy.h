#ifndef ENERGY_H
#define ENERGY_H

#include <map>
#include <vector>
#include <string>

enum typeEnergy{
    COLORLESS = 0,
    GRASS,
    FIRE,
    WATER,
    LIGHTING,
    PSYCHIC,
    FIGHTING,
    DARKNESS,
    METAL,
    DRAGON //En soit il n'y a pas d'énergie dragon mais il y un type dragon soo
};

typeEnergy stringToTypeEnergy(const std::string& type);
std::string typeEnergyToString(const typeEnergy& type);

class energyList{
public:
    // Création
    energyList();
    energyList(const std::vector<typeEnergy> &energies);
    energyList(const typeEnergy &energy);

    // Accesseur
    int energyAmount() const;
    bool enoughEnergy(const energyList& cost);
    energyList coverWith(const energyList& cost) const;
    std::map<typeEnergy, unsigned int> energy() const;
    void print() const;

    // Mutateur
    void operator+=(const typeEnergy energy);
    void operator+=(const energyList &energy);
    void operator-=(const typeEnergy energy);
    void operator-=(const energyList &energy);


private:
    std::map<typeEnergy, unsigned int> _energy;
};

#endif