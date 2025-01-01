#ifndef ENERGY_H
#define ENERGY_H

#include <map>
#include <vector>

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

class energyList{
public:
    // Création
    energyList();
    energyList(const std::vector<typeEnergy> &energies);

    // Accesseur
    int energyAmount() const;
    bool enoughEnergy(const energyList& cost);

    // Mutateur
    void operator+=(const typeEnergy energy);
    void operator+=(const energyList &energy);
    void operator-=(const typeEnergy energy);
    void operator-=(const energyList &energy);


private:
    std::map<typeEnergy, unsigned int> _energy;
};

#endif