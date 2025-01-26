#ifndef ENERGYMANAGER_H
#define ENERGYMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "../src/energy.h"

class EnergyManager {
public:

    struct Energy {
        sf::Sprite sprite;
        int index; //1 : carte active joueur, 2-4 : carte banc joueur, 5 : carte active ennemi, 4-8 : carte banc ennemi
        typeEnergy type;
    };

    static EnergyManager& getInstance() {
        static EnergyManager instance;
        return instance;
    }

    // Retourne une texture en fonction du nom de la carte
    const sf::Texture& getTexture(typeEnergy energie) {
        std::string cardName = typeEnergyToString(energie);
        if (textures.find(cardName) == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile("assets/energy/" + cardName + ".png")) {
                std::cerr << "Erreur: Impossible de charger " << cardName << ".png\n";
                textures[cardName] = sf::Texture(); // Texture vide par défaut
            } else {
                textures[cardName] = std::move(texture);
            }
        }
        return textures[cardName];
    }

    // Crée un sprite redimensionné à la taille standard
    Energy createEnergy(const typeEnergy energie, int index) {
        Energy energy;
        energy.sprite.setTexture(getTexture(energie));
        // Redimensionner pour s'assurer que toutes les cartes ont une taille uniforme
        const sf::Vector2u textureSize = energy.sprite.getTexture()->getSize();
        float scaleFactor = std::min(
            targetWidth / static_cast<float>(textureSize.x),
            targetHeight / static_cast<float>(textureSize.y)
        );
        energy.sprite.setScale(scaleFactor, scaleFactor);
        energy.type = energie;
        energy.index = index; 
        return energy;
    }

    // Définir la taille standard pour les cartes
    void setTargetSize(float width, float height) {
        targetWidth = width;
        targetHeight = height;
    }


    EnergyManager() : targetWidth(30.f), targetHeight(30.f) {} // Taille par défaut
    std::unordered_map<std::string, sf::Texture> textures;

    float targetWidth;  // Largeur cible pour les cartes
    float targetHeight; // Hauteur cible pour les cartes

    EnergyManager(const EnergyManager&) = delete;
    EnergyManager& operator=(const EnergyManager&) = delete;
    
};

#endif // ENERGYMANAGER_H