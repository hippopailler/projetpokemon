#ifndef STATUSMANAGERGR_H
#define STATUSMANAGERGR_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class StatusManager {
public:

    struct Status {
        sf::Sprite sprite;
        std::string type;
        int index;

    };

    static StatusManager& getInstance() {
        static StatusManager instance;
        return instance;
    }

    // Retourne une texture en fonction du nom de la carte
    const sf::Texture& getTexture(const std::string& cardName) {
        if (textures.find(cardName) == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile("assets/status/" + cardName + ".png")) {
                std::cerr << "Erreur: Impossible de charger " << cardName << ".png\n";
                textures[cardName] = sf::Texture(); // Texture vide par défaut
            } else {
                textures[cardName] = std::move(texture);
            }
        }
        return textures[cardName];
    }

    // Crée un sprite redimensionné à la taille standard
    Status createStatus(const std::string& cardName,const std::string& type, int player) {
        Status status;
        status.sprite.setTexture(getTexture(cardName));
        // Redimensionner pour s'assurer que toutes les cartes ont une taille uniforme
        const sf::Vector2u textureSize = status.sprite.getTexture()->getSize();
        float scaleFactor = std::min(
            targetWidth / static_cast<float>(textureSize.x),
            targetHeight / static_cast<float>(textureSize.y)
        );
        status.sprite.setScale(scaleFactor, scaleFactor);
        status.type = type;
        status.index = player;
        return status;
    }

    // Définir la taille standard pour les cartes
    void setTargetSize(float width, float height) {
        targetWidth = width;
        targetHeight = height;
    }


    StatusManager() : targetWidth(30.f), targetHeight(30.f) {} // Taille par défaut
    std::unordered_map<std::string, sf::Texture> textures;

    float targetWidth;  // Largeur cible pour les cartes
    float targetHeight; // Hauteur cible pour les cartes

    StatusManager(const StatusManager&) = delete;
    StatusManager& operator=(const StatusManager&) = delete;
    
};

#endif // STATUSMANAGERGR_H