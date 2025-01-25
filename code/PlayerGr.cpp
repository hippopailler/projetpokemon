#include "PlayerGr.h"

Player::Player(const std::string& name) : name(name) {}
Player::Player() : name("Default Player") {}
std::string Player::getName() const {
    return name;
}