#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <string>

class Card {
public:
    Card(const std::string& texturePath);
    void draw(sf::RenderWindow& window, const sf::Vector2f& position);

private:
    sf::Texture cardTexture;
    sf::Sprite cardSprite;
};

#endif // CARD_H
