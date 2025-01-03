#ifndef ENERGYMANAGER_H
#define ENERGYMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class EnergyManager {
public:
    static EnergyManager& getInstance() {
        static EnergyManager instance;
        return instance;
    }

    // Retourne une texture en fonction du nom de la carte
    const sf::Texture& getTexture(const std::string& cardName) {
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
    sf::Sprite createEnergySprite(const std::string& cardName) {
        sf::Sprite sprite;
        sprite.setTexture(getTexture(cardName));
        // Redimensionner pour s'assurer que toutes les cartes ont une taille uniforme
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        float scaleFactor = std::min(
            targetWidth / static_cast<float>(textureSize.x),
            targetHeight / static_cast<float>(textureSize.y)
        );
        sprite.setScale(scaleFactor, scaleFactor);
       
        return sprite;
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