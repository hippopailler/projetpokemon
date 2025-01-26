#ifndef CARDMANAGERGR_H
#define CARDMANAGERGR_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>
#include "EnergyManagerGr.h"

class CardManager {
public:

    struct Card {
        sf::Sprite sprite;
        //int hp;
        int index; //1 : carte active joueur, 2-4 : carte banc joueur, 5 : carte active ennemi, 4-8 : carte banc ennemi, 10- pour la main
        std::vector<EnergyManager::Energy> energystock;
    };


    static CardManager& getInstance() {
        static CardManager instance;
        return instance;
    }

    // Retourne une texture en fonction du nom de la carte
    const sf::Texture& getTexture(const std::string& cardID) {
        if (textures.find(cardID) == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile("assets/cards/" + cardID + ".png")) {
                std::cerr << "Erreur: Impossible de charger " << cardID << ".png\n";
                textures[cardID] = sf::Texture(); // Texture vide par défaut
            } else {
                textures[cardID] = std::move(texture);
            }
        }
        return textures[cardID];
    }

    // Crée une carte avec des points de vie
    Card createCard(const std::string& cardID) {
        Card card;
        card.sprite.setTexture(getTexture(cardID));

        // Redimensionner pour s'assurer que toutes les cartes ont une taille uniforme
        const sf::Vector2u textureSize = card.sprite.getTexture()->getSize();
        float scaleFactor = std::min(
            targetWidth / static_cast<float>(textureSize.x),
            targetHeight / static_cast<float>(textureSize.y)
        );
        card.sprite.setScale(scaleFactor, scaleFactor);

        return card;
    }

    // Définir la taille standard pour les cartes
    void setTargetSize(float width, float height) {
        targetWidth = width;
        targetHeight = height;
    }


    CardManager() : targetWidth(200.f), targetHeight(300.f) {} // Taille par défaut
    std::unordered_map<std::string, sf::Texture> textures;

    float targetWidth;  // Largeur cible pour les cartes
    float targetHeight; // Hauteur cible pour les cartes

    CardManager(const CardManager&) = delete;
    CardManager& operator=(const CardManager&) = delete;
    



    // Pour les cartes du joueur adverse on n'affiche de que le dos de la carte
    sf::Sprite createBackSprite() {
    sf::Sprite sprite;

    // Charger la texture du dos de la carte
    if (!textures.count("BackCard")) {
        sf::Texture backTexture;
        if (!backTexture.loadFromFile("assets/BackCard.png")) {
            std::cerr << "Erreur: Impossible de charger le dos des cartes.\n";
            exit(EXIT_FAILURE);
        }
        textures["BackCard"] = backTexture;
    }

    sprite.setTexture(textures["BackCard"]);

    // Ajuster la taille pour correspondre au format des cartes
    const sf::Vector2u textureSize = sprite.getTexture()->getSize();
    float scaleFactor = std::min(
        targetWidth / static_cast<float>(textureSize.x),
        targetHeight / static_cast<float>(textureSize.y)
    );
    sprite.setScale(scaleFactor, scaleFactor);

    return sprite;
}

};

#endif
