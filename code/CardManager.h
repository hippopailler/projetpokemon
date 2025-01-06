#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class CardManager {
public:

    struct Card {
        sf::Sprite sprite;
        int hp;
    };


    static CardManager& getInstance() {
        static CardManager instance;
        return instance;
    }

    // Retourne une texture en fonction du nom de la carte
    const sf::Texture& getTexture(const std::string& cardName) {
        if (textures.find(cardName) == textures.end()) {
            sf::Texture texture;
            if (!texture.loadFromFile("assets/pokemon/" + cardName + ".png")) {
                std::cerr << "Erreur: Impossible de charger " << cardName << ".png\n";
                textures[cardName] = sf::Texture(); // Texture vide par défaut
            } else {
                textures[cardName] = std::move(texture);
            }
        }
        return textures[cardName];
    }

    // Crée une carte avec des points de vie
    Card createCard(const std::string& cardName, int hp) {
        Card card;
        card.sprite.setTexture(getTexture(cardName));
        card.hp = hp;

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
