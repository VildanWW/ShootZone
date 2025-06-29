#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Weapons {
public:
    int ammo = 0;
    virtual void shoot(sf::RenderWindow& window, const sf::Vector2f& heroPos, const sf::FloatRect& heroBounds,
        sf::Sprite spriteBullet, std::vector<Bullet>& bullets, bool shootRight) = 0;
};

