#include "Card.h"

Card::Card(const std::string& texturePath) {
    if (!cardTexture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load card texture");
    }
    cardSprite.setTexture(cardTexture);
    //cardSprite.setScale(0.5f, 0.5f); // Réduit la taille des cartes
}

void Card::draw(sf::RenderWindow& window, const sf::Vector2f& position) {
    cardSprite.setPosition(position);
    window.draw(cardSprite);
}
